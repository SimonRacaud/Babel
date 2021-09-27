/*
** EPITECH PROJECT, 2021
** AsioUdpServer.hpp
** File description:
** Network UDP implementation whith Asio lib, according to IConnection interface
*/
#ifndef BABEL_ASIOCONNECTIONUDP_HPP
#define BABEL_ASIOCONNECTIONUDP_HPP

#include <algorithm>
#include <iostream>
#include "ANetwork.hpp"

namespace network
{
    using asio::ip::udp;

    template <std::size_t PACKETSIZE> class AsioConnectionUDP : public AAsioConnection<PACKETSIZE> {
      public:
        /**
         * @brief
         * @param port The port to open on this machine
         */
        AsioConnectionUDP(const std::size_t port)
            : AAsioConnection<PACKETSIZE>(true),
              _endpoint(udp::v4(), port), _socket{AAsioConnection<PACKETSIZE>::_ioContext, _endpoint}
        {
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() override
        {
            std::array<char, PACKETSIZE> recvBuf;
            udp::endpoint senderEndpoint;
            size_t len = _socket.receive_from(asio::buffer(recvBuf), senderEndpoint);

            return std::make_tuple(recvBuf, len, senderEndpoint.address().to_string(), senderEndpoint.port());
            // std::cout.write(recvBuf.data(), len);
            //  to write the good amount of data
        }

        std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(const std::string &ip, const std::size_t port) override
        {
            std::array<char, PACKETSIZE> recvBuf;
    std::cout << "recv 1" << std::endl;
            asio::ip::udp::endpoint senderEndpoint(asio::ip::make_address(ip), port);
    std::cout << "recv 2" << std::endl;
            size_t len = _socket.receive_from(asio::buffer(recvBuf), senderEndpoint);
    std::cout << "recv 3" << std::endl;

            return std::make_pair(recvBuf, len);
        }

        void sendAll(const std::array<char, PACKETSIZE> &buf) override
        {
            for (const auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                send(buf, connection.first, connection.second);
            }
        }

        void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port) override
        {
            udp::endpoint remoteEndpoint(asio::ip::make_address(ip), port);

            _socket.send_to(asio::buffer(buf), remoteEndpoint, 0, AAsioConnection<PACKETSIZE>::_error);
        }

      private:
        udp::endpoint _endpoint;
        udp::socket _socket;
    };

} // namespace network

#endif // BABEL_ASIOCONNECTIONUDP_HPP