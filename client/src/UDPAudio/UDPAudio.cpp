/*
** PERSONAL PROJECT, 2021
** UDPAudio
** File description:
** UDPAudio.cpp
*/

#include "UDPAudio.hpp"

UDPAudio::UDPAudio(size_t portIn, size_t portOut) :
_input(std::make_unique<Audio::InputAudioManager>()),
_networkIn(std::make_unique<NetworkIn>(portIn)),
_networkOut(std::make_unique<NetworkOut>(portOut))
{
}

UDPAudio::UDPAudio(size_t portIn, size_t portOut, const std::vector<UserRaw> &list) :
_input(std::make_unique<Audio::InputAudioManager>()),
_networkIn(std::make_unique<NetworkIn>(portIn)),
_networkOut(std::make_unique<NetworkOut>(portOut))
{
    for (auto &it : list)
        this->addUser(it);
}

UDPAudio::~UDPAudio()
{
    for (size_t i = 0; i < this->_list.size(); i++)
        this->_list[i].second.reset();
    this->_list.clear();
    this->_networkIn.reset();
    this->_networkOut.reset();
    if (this->_input)
        this->_input.reset();
}

void UDPAudio::addUser(const UserRaw &user)
{
    this->_networkIn->connect(user.ip, user.port);
    this->_networkOut->connect(user.ip, user.port);
    this->_list.push_back(std::pair<UserRaw, std::unique_ptr<Audio::OutputAudioManager>>(user, std::make_unique<Audio::OutputAudioManager>()));
}

void UDPAudio::removeUser(const UserRaw &user)
{
    this->_networkIn->disconnect(user.ip, user.port);
    this->_networkOut->disconnect(user.ip, user.port);
    for (size_t i = 0; i < this->_list.size(); i++) {
        if (this->_list[i].first == user) {
            this->_list[i].second.reset();
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
    std::array<char, Network::BUFFER_SIZE> buff;
    std::queue<Audio::compressFrameBuffer> frameBuffer = this->_input->getFrameBuffer();

    while (frameBuffer.size()) {
        auto it = frameBuffer.front();

        std::memset(buff.data(), 0, Network::BUFFER_SIZE);
        std::memcpy(buff.data(), it.data.data(), it.encodedBit);
        std::memcpy(buff.data() + (Network::BUFFER_SIZE - sizeof(int)), &it.encodedBit, sizeof(int));
        
        this->_networkOut->sendAll(buff);
        frameBuffer.pop();
    }
}

void UDPAudio::receivingData()
{
    Audio::compressFrameBuffer tmp;
    std::queue<Audio::compressFrameBuffer> frameBuffer;

    for (auto const &it : this->_list) {
        auto data = this->_networkIn->receive(it.first.ip, it.first.port);
        if (data.second == Network::BUFFER_SIZE) {
            tmp.data = std::vector<unsigned char>(Network::BUFFER_SIZE);
            std::memset(tmp.data.data(), 0, Network::BUFFER_SIZE);
            std::memcpy(tmp.data.data(), data.first.data(), Network::BUFFER_SIZE - sizeof(int));
            std::memcpy(&tmp.encodedBit, data.first.data() + (Network::BUFFER_SIZE - sizeof(int)), sizeof(int));
            tmp.data.resize(tmp.encodedBit);
            frameBuffer.push(tmp);
            it.second->setFrameBuffer(frameBuffer);
            while (frameBuffer.size())
                frameBuffer.pop();
        }
    }
}