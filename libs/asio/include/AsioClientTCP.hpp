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

        void connect(const std::string &ip, const std::size_t port)
        {
            tcp::endpoint serverEndpoint(asio::ip::make_address(ip), port);
            auto newConnection(std::make_shared<tcp::socket>(AAsioConnection<PACKETSIZE>::_ioContext));

            try {
                newConnection->connect(serverEndpoint);
                // todo does not work if server is not active
                //      change for async_connect ?
                //      its ok because the server is always active (just try catch) ?
            } catch (const std::system_error &) {
                // todo remove that
                std::cout << "caught" << std::endl;
                return;
            }
            AsioConnectionTCP<PACKETSIZE>::addConnection(newConnection);
        }

      private:
        void handleConnect(const asio::error_code &err, tcp::resolver::iterator endpoint_iterator)
        {
        }
    };

} // namespace Network

#endif // BABEL_ASIOCLIENTTCP_HPP