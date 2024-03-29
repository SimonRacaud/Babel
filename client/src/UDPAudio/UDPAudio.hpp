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
#include "Audio.hpp"
#include "Network.hpp"
#include "UserRaw.hpp"
#include "AsioConnectionUDP.hpp"
#include "Audio/InputAudioManager/InputAudioManager.hpp"
#include "Audio/OutputAudioManager/OutputAudioManager.hpp"

class UDPAudio
{
    using NetworkComponent = Network::AsioConnectionUDP<Network::BUFFER_SIZE>;
    public:
        UDPAudio(size_t port);
        UDPAudio(size_t port, const std::vector<UserRaw> &list);
        ~UDPAudio();
        void addUser(const UserRaw &user);
        void removeUser(const UserRaw &user);
        void streamAudio();

        /**
         * Update _list? and call this->addUser()
         * @param list
         */
        void updateConnections(std::vector<UserRaw> &list);
        /**
         * Get _list?
         * @return vector of User
         */
        std::vector<UserRaw> getConnections() const;

        void closeConnections();

    private:
        void sendingData();
        void receivingData();
        bool correctPacket(size_t &lastTimestamp, const Network::UDPTram_t &tram);
        void audioManagerPtr();

    private:
        std::size_t _port;
        std::unique_ptr<Audio::InputAudioManager> _input;
        std::unique_ptr<Audio::OutputAudioManager> _output;
        std::unique_ptr<NetworkComponent> _network;
        std::vector<std::tuple<UserRaw, size_t>> _list;
};

#endif