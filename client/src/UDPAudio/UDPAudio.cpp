/*
** PERSONAL PROJECT, 2021
** UDPAudio
** File description:
** UDPAudio.cpp
*/

#include "UDPAudio.hpp"
#include "tools/tramFactory.hpp"

UDPAudio::UDPAudio(size_t portIn, size_t portOut) :
_input(std::make_unique<Audio::InputAudioManager>()),
_output(std::make_unique<Audio::OutputAudioManager>()),
_networkIn(std::make_unique<NetworkIn>(portIn)),
_networkOut(std::make_unique<NetworkOut>(portOut))
{
    if (sizeof(Network::UDPTram_t) != Network::BUFFER_SIZE)
        throw std::invalid_argument("Invalid UDP tram");
}

UDPAudio::UDPAudio(size_t portIn, size_t portOut, const std::vector<UserRaw> &list) :
_input(std::make_unique<Audio::InputAudioManager>()),
_output(std::make_unique<Audio::OutputAudioManager>()),
_networkIn(std::make_unique<NetworkIn>(portIn)),
_networkOut(std::make_unique<NetworkOut>(portOut))
{
    if (sizeof(Network::UDPTram_t) != Network::BUFFER_SIZE)
        throw std::invalid_argument("Invalid UDP tram");
    for (auto &it : list)
        this->addUser(it);
}

UDPAudio::~UDPAudio()
{
    this->_list.clear();
    this->_networkIn.reset();
    this->_networkOut.reset();
    if (this->_input)
        this->_input.reset();
    if (this->_output)
        this->_output.reset();
}

void UDPAudio::addUser(const UserRaw &user)
{
    this->_networkIn->connect(user.ip, user.port);
    this->_networkOut->connect(user.ip, user.port);
    this->_list.push_back(std::tuple<UserRaw, size_t>(user, 0));
}

void UDPAudio::removeUser(const UserRaw &user)
{
    this->_networkIn->disconnect(user.ip, user.port);
    this->_networkOut->disconnect(user.ip, user.port);
    for (size_t i = 0; i < this->_list.size(); i++) {
        if (std::get<0>(this->_list[i]) == user) {
            this->_list.erase(this->_list.begin() + i);
        }
    }
}

void UDPAudio::streamAudio()
{
    this->receivingData();
    this->sendingData();
}

void UDPAudio::sendingData()
{
    std::queue<Audio::compressFrameBuffer> frameBuffer = this->_input->getFrameBuffer();

    while (frameBuffer.size()) {
        auto it = frameBuffer.front();
        /*
        ** tram
        */
        Network::UDPTram_t tram;
        if ((long unsigned int) it.encodedBit > Network::DATA_SIZE - sizeof(int))
            throw std::invalid_argument("Invalid data size: resize is necessary");
        std::memcpy(tram.data, it.data.data(), it.encodedBit);
        std::memcpy(tram.data + (Network::DATA_SIZE - sizeof(int)), &it.encodedBit, sizeof(int));
        this->_networkOut->sendAll(tramFactory<Network::UDPTram_t>::makeTram(tram));
        frameBuffer.pop();
    }
}

void UDPAudio::receivingData()
{
    Audio::compressFrameBuffer tmp;
    std::queue<Audio::compressFrameBuffer> frameBuffer;

    for (auto &it : this->_list) {
        auto data = this->_networkIn->receive(std::get<0>(it).ip, std::get<0>(it).port);
        if (data.second == Network::BUFFER_SIZE) {
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
                this->_output->setFrameBuffer(frameBuffer);
                while (frameBuffer.size())
                    frameBuffer.pop();
            }
        }
    }
}

bool UDPAudio::correctPacket(size_t &lastTimestamp, const Network::UDPTram_t &tram)
{
    bool magicNumber = tram.magicNumber == Network::MAGIC_NUMBER;
    bool timestamp = lastTimestamp < tram.timestamp;

    timestamp = tram.timestamp;
    return magicNumber && timestamp;
}