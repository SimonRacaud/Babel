/*
** PERSONAL PROJECT, 2021
** UDPAudio
** File description:
** UDPAudio.cpp
*/

#include "UDPAudio.hpp"
#include "tools/tramFactory.hpp"

UDPAudio::UDPAudio(size_t port) : _port(port), _input(nullptr), _output(nullptr), _network(std::make_unique<NetworkComponent>(port))
{
    //    this->_network->runAsync();
    if (sizeof(Network::UDPTram_t) != Network::BUFFER_SIZE)
        throw std::invalid_argument("Invalid UDP tram");
}

UDPAudio::UDPAudio(size_t port, const std::vector<UserRaw> &list)
    : _input(nullptr), _output(nullptr), _network(std::make_unique<NetworkComponent>(port))
{
    //    this->_network->runAsync();
    if (sizeof(Network::UDPTram_t) != Network::BUFFER_SIZE)
        throw std::invalid_argument("Invalid UDP tram");
    for (auto &it : list)
        this->addUser(it);
    this->audioManagerPtr();
}

UDPAudio::~UDPAudio()
{
    this->_network->stopRunAsync();
    this->_list.clear();
    this->_network.reset();
    if (this->_input)
        this->_input.reset();
    if (this->_output)
        this->_output.reset();
}

void UDPAudio::addUser(const UserRaw &user)
{
    this->_network->connect(user.ip, Network::PORT_UDP_RECEIVE);
    this->_list.push_back(std::tuple<UserRaw, size_t>(user, 0));
    this->audioManagerPtr();
}

void UDPAudio::removeUser(const UserRaw &user)
{
    this->_network->disconnect(user.ip, user.port);
    for (size_t i = 0; i < this->_list.size(); i++) {
        if (std::get<0>(this->_list[i]) == user) {
            this->_list.erase(this->_list.begin() + i);
        }
    }
    this->audioManagerPtr();
}

void UDPAudio::closeConnections()
{
    this->_network->disconnectAll();
    this->_list.clear();
    this->audioManagerPtr();
}

void UDPAudio::streamAudio()
{
    if (this->_list.size() && _input && _output) {
        this->sendingData();
        this->receivingData();
    }
}

void UDPAudio::sendingData()
{
    std::queue<Audio::compressFrameBuffer> frameBuffer = this->_input->getFrameBuffer();

    while (frameBuffer.size()) {
        auto it = frameBuffer.front();
        Network::UDPTram_t tram;
        if ((long unsigned int) it.encodedBit > Network::DATA_SIZE - sizeof(int))
            throw std::invalid_argument("Invalid data size: resize is necessary");
        std::memcpy(tram.data, it.data.data(), it.encodedBit);
        std::memcpy(tram.data + (Network::DATA_SIZE - sizeof(int)), &it.encodedBit, sizeof(int));
        this->_network->sendAll(tramFactory<Network::UDPTram_t>::makeTram(tram));
        frameBuffer.pop();
    }
}

void UDPAudio::receivingData()
{
    bool continu = true;
    Audio::compressFrameBuffer tmp;
    std::queue<Audio::compressFrameBuffer> frameBuffer;

    for (size_t i = 0; continu && i < 100; i++) {
        continu = false;
        for (auto &it : this->_list) {
            auto data = this->_network->receive(std::get<0>(it).ip, Network::PORT_UDP_RECEIVE);
            if (data.second == Network::BUFFER_SIZE) {
                continu = true;
                /*
                ** tram
                */
                Network::UDPTram_t tram = tramFactory<Network::UDPTram_t>::getTram(data.first.data());
                if (this->correctPacket(std::get<1>(it), tram)) {
                    tmp.data = std::vector<unsigned char>(Network::DATA_SIZE);
                    std::memset(tmp.data.data(), 0, Network::DATA_SIZE);
                    std::memcpy(tmp.data.data(), tram.data, Network::DATA_SIZE - sizeof(int));
                    std::memcpy(&tmp.encodedBit, tram.data + (Network::DATA_SIZE - sizeof(int)), sizeof(int));
                    tmp.data.resize(tmp.encodedBit);
                    frameBuffer.push(tmp);
                    /*
                    **
                    ** this->_output->setFrameBuffer(frameBuffer);
                    ** while (frameBuffer.size())
                    **     frameBuffer.pop();
                    **
                    */
                }
            }
        }
    }
    this->_output->setFrameBuffer(frameBuffer);
}

bool UDPAudio::correctPacket(size_t &lastTimestamp, const Network::UDPTram_t &tram)
{
    bool magicNumber = tram.magicNumber == Network::MAGIC_NUMBER;
    bool timestamp = true;//lastTimestamp <= tram.timestamp || !Audio::DEFAULT_CHECKED_TIMESTAMP;

    (void) lastTimestamp;
    timestamp = tram.timestamp;
    return magicNumber && timestamp;
}

std::vector<UserRaw> UDPAudio::getConnections() const
{
    std::vector<UserRaw> output;

    for (auto const &it : this->_list)
        output.push_back(std::get<0>(it));
    return output;
}

void UDPAudio::updateConnections(std::vector<UserRaw> &list)
{
    for (auto const &it : list) {
        bool inList = std::find_if(this->_list.begin(), this->_list.end(), [it](auto const &pair) {
            return std::get<0>(pair) == it;
        }) != this->_list.end();

        if (!inList)
            this->addUser(it);
    }
    for (auto const &it : this->_list) {
        bool inList = std::find_if(list.begin(), list.end(), [it](auto const &user) {
            return user == std::get<0>(it);
        }) != list.end();

        if (!inList)
            this->removeUser(std::get<0>(it));
    }
    this->audioManagerPtr();
    this->_network->runAsync();
}

void UDPAudio::audioManagerPtr()
{
    if (this->_list.size()) {
        if (!this->_input) {
            this->_input = std::make_unique<Audio::InputAudioManager>();
        }
        if (!this->_output) {
            this->_output = std::make_unique<Audio::OutputAudioManager>();
        }
    } else {
        if (this->_input) {
            this->_input.reset();
            this->_input = nullptr;
        }
        if (this->_output) {
            this->_output.reset();
            this->_output = nullptr;
        }
    }
}