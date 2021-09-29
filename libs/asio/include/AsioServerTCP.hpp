/*
** EPITECH PROJECT, 2021
** AsioServerTCP.hpp
** File description:
** Implementation of Server for TCP protocol
*/
#ifndef BABEL_ASIOSERVERTCP_HPP
#define BABEL_ASIOSERVERTCP_HPP

#include "AsioConnectionTCP.hpp"

namespace network
{
    template <std::size_t PACKETSIZE> class AsioServerTCP : public AsioConnectionTCP<PACKETSIZE> {
      public:
        /**
         * @brief
         * @param port The port to open on this machine
         */
        AsioServerTCP(const std::size_t port)
            : AAsioConnection<PACKETSIZE>(true), _acceptor(AAsioConnection<PACKETSIZE>::_ioContext, tcp::endpoint(tcp::v4(), port))
        {
            startAccept();
        }

      private:
        void startAccept()
        {
            std::shared_ptr<tcp::socket> newConnection(std::make_shared<tcp::socket>(AAsioConnection<PACKETSIZE>::_ioContext));

            _acceptor.async_accept(*newConnection, std::bind(&AsioServerTCP::connect, this, newConnection, std::placeholders::_1));
        }

        void connect(std::shared_ptr<tcp::socket> newConnection, const asio::error_code &error)
        {
            if (error)
                return; // todo check errors
            auto my_newConnection(newConnection->remote_endpoint());

            // todo add AsioConnectionTCP<PACKETSIZE>::connect() ?
            AAsioConnection<PACKETSIZE>::connect(my_newConnection.address().to_string(), my_newConnection.port());

            startAccept();
        }

      private:
        tcp::acceptor _acceptor;
        tcp::endpoint _endpoint;
    };

} // namespace network

#endif // BABEL_ASIOSERVERTCP_HPP