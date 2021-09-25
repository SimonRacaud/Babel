/*
** EPITECH PROJECT, 2021
** ANetwork.hpp
** File description:
** Network Abstract class
*/
#ifndef BABEL_ANETWORK_HPP
#define BABEL_ANETWORK_HPP

#include "INetwork.hpp"

namespace network
{
    template <std::size_t PACKETSIZE> class AAsioConnection : public IConnection<PACKETSIZE> {
      public:
        AAsioConnection(const bool server = false)
            : _ioContext(), _server(server){

                            };
        virtual void connect(const std::string &ip, const std::size_t port) override
        {
            AAsioConnection<PACKETSIZE>::_connections.push_front(std::make_pair(ip, port));
        };

        virtual void disconnect(const std::string &ip, const std::size_t port) override
        {
            const auto disconnection(std::find_if(AAsioConnection<PACKETSIZE>::_connections.begin(),
                AAsioConnection<PACKETSIZE>::_connections.end(),
                [ip, port](const auto &connection) {
                    return ip == connection.first && port == connection.second;
                }));
            // todo find solution
            //            if (disconnection
            //                !=
            //                AAsioConnection<PACKETSIZE>::_connections.end())
            //                AAsioConnection<PACKETSIZE>::_connections.erase(disconnection);
            //                std::erase(disconnection);
        };
        virtual void disconnectAll() override
        {
            AAsioConnection<PACKETSIZE>::_connections.clear();
        };

        virtual std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() = 0;

        virtual std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(const std::string &ip, const std::size_t port) = 0;

        virtual void sendAll(std::array<char, PACKETSIZE> buf) = 0;

        virtual void send(std::array<char, PACKETSIZE> buf, const std::string &ip, const std::size_t port) = 0;

        bool isConnected(const std::string &ip, const std::size_t port) const override
        {
            if (!AAsioConnection<PACKETSIZE>::_connections.empty()
                && std::find_if(_connections.begin(),
                       _connections.end(),
                       [=](const auto &connection) {
                           return ip == connection.first && port == connection.second;
                       })
                    != AAsioConnection<PACKETSIZE>::_connections.end())
                return true;
            return false;
        }

      protected:
        asio::io_context _ioContext; // todo static ?
        asio::error_code _error;

        enum protocol _type;
        std::deque<std::pair<const std::string &, const std::size_t>> _connections;

        bool _server;
    };
} // namespace network

#endif // BABEL_ANETWORK_HPP