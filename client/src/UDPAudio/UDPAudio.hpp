/*
** PERSONAL PROJECT, 2021
** UDPAudio
** File description:
** UDPAudio.hpp
*/

#ifndef UDPAUDIO_HPP
#define UDPAUDIO_HPP

#include <vector>
#include <memory>
#include "Network.hpp"
#include "UserRaw.hpp"
#include "AsioConnectionUDP.hpp"
#include "Audio/InputAudioManager/InputAudioManager.hpp"
#include "Audio/OutputAudioManager/OutputAudioManager.hpp"

class UDPAudio
{
    using NetworkIn = Network::AsioConnectionUDP<Network::BUFFER_SIZE>;
    using NetworkOut = Network::AsioConnectionUDP<Network::BUFFER_SIZE>;
    public:
        UDPAudio(size_t portIn, size_t portOut);
        UDPAudio(size_t portIn, size_t portOut, const std::vector<UserRaw> &list);
        ~UDPAudio();
        void addUser(const UserRaw &user);
        void removeUser(const UserRaw &user);
        void streamAudio();

    private:
        void sendingData();
        void receivingData();
        bool correctPacket(size_t &lastTimestamp, const Network::UDPTram_t &tram);

    private:
        std::unique_ptr<Audio::InputAudioManager> _input;
        std::unique_ptr<NetworkIn> _networkIn;
        std::unique_ptr<NetworkOut> _networkOut;
        std::vector<std::tuple<UserRaw, std::unique_ptr<Audio::OutputAudioManager>, size_t>> _list;
};

#endif