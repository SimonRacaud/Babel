/*
** EPITECH PROJECT, 2021
** AsioUdpServer.hpp
** File description:
** TODO: add description
*/
#ifndef BABEL_ASIOUDPSERVER_HPP
#define BABEL_ASIOUDPSERVER_HPP

#include <algorithm>
#include <iostream>
#include "Network/ANetwork.hpp"

namespace network
{
    using asio::ip::udp;

    template <std::size_t PACKETSIZE>
    class AsioConnectionUDP : public AAsioConnection<PACKETSIZE> {
      public:
        /**
         * @brief
         * @param port The port to open on this machine
         */
        AsioConnectionUDP(const std::size_t port)
            : AAsioConnection<PACKETSIZE>(true), _endpoint(udp::v4(), port),
              _socket{AAsioConnection<PACKETSIZE>::_ioContext, _endpoint} {};

        void connect(const std::string &ip, const std::size_t port) override
        // TODO add override keyword
        {
            AAsioConnection<PACKETSIZE>::_connections.push_front(
                std::make_pair(ip, port));
        }

        void disconnect(const std::string &ip, const std::size_t port) override
        {
            const auto disconnection(std::find_if(
                AAsioConnection<PACKETSIZE>::_connections.begin(),
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
        }

        void disconnectAll() override
        {
            AAsioConnection<PACKETSIZE>::_connections.clear();
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string,
            std::size_t>
        receiveAny() override
        {
            std::array<char, PACKETSIZE> recvBuf;
            udp::endpoint senderEndpoint;
            size_t len =
                _socket.receive_from(asio::buffer(recvBuf), senderEndpoint);

            return std::make_tuple(recvBuf, len,
                senderEndpoint.address().to_string(), senderEndpoint.port());
            // std::cout.write(recvBuf.data(), len);
            //  to write the good amount of data
        }

        std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(
            const std::string &ip, const std::size_t port) override
        {
            std::array<char, PACKETSIZE> recvBuf;
            asio::ip::udp::endpoint senderEndpoint(
                asio::ip::make_address(ip), port);
            size_t len =
                _socket.receive_from(asio::buffer(recvBuf), senderEndpoint);

            return std::make_pair(recvBuf, len);
        }

        void sendAll(std::array<char, PACKETSIZE> buf) override
        {
            for (const auto &connection :
                AAsioConnection<PACKETSIZE>::_connections) {
                send(buf, connection.first, connection.second);
            }
        }

        void send(std::array<char, PACKETSIZE> buf, const std::string &ip,
            const std::size_t port) override
        {
            udp::endpoint remoteEndpoint(asio::ip::make_address(ip), port);

            _socket.send_to(asio::buffer(buf), remoteEndpoint, 0,
                AAsioConnection<PACKETSIZE>::_error);
        }

      private:
        udp::endpoint _endpoint;
        udp::socket _socket;
    };

} // namespace network

#endif // BABEL_ASIOUDPSERVER_HPP