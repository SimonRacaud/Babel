/*
** EPITECH PROJECT, 2021
** AsioClientTCP.hpp
** File description:
** Implementation of Client for TCP protocol
*/
#ifndef BABEL_ASIOCLIENTTCP_HPP
#define BABEL_ASIOCLIENTTCP_HPP

#include "AsioConnectionTCP.hpp"

namespace Network
{
    template <std::size_t PACKETSIZE> class AsioClientTCP : public AsioConnectionTCP<PACKETSIZE> {
      public:
        AsioClientTCP() = default;

        void connect(const std::string &ip, const std::size_t port) override
        {
            tcp::endpoint serverEndpoint(asio::ip::make_address(ip), port);
            auto newConnection(std::make_shared<tcp::socket>(AAsioConnection<PACKETSIZE>::_ioContext));

            try {
                newConnection->connect(serverEndpoint);
            } catch (const std::system_error &) {
                /**
                 * @brief server is not active
                 */
                return;
            }
            AsioConnectionTCP<PACKETSIZE>::addConnection(newConnection);
        }
    };

} // namespace Network

#endif // BABEL_ASIOCLIENTTCP_HPP