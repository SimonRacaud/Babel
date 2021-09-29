/*
** EPITECH PROJECT, 2021
** AsioClientTCP.hpp
** File description:
** Implementation of Client for TCP protocol
*/
#ifndef BABEL_ASIOCLIENTTCP_HPP
#define BABEL_ASIOCLIENTTCP_HPP

namespace network
{
    template <std::size_t PACKETSIZE> class AsioClientTCP : public AsioConnectionTCP<PACKETSIZE> {
      public:
        AsioClientTCP() : _resolver(AAsioConnection<PACKETSIZE>::_ioContext)
        {
        }

        void connect(const std::string &ip, const std::size_t port)
        {
            // auto _endpoints = resolver.async_resolve(ip); // todo instead of ip, create endpoint and send in parameter

            auto socketConnection(getConnection(ip, port));
            // todo ensure that AsioConnectionTCP<PACKETSIZE>::connect() fills the array

            if (!socketConnection)
                return;

            asio::connect(socketConnection, _endpoints);
        }

      private:
        tcp::resolver _resolver;
        tcp::socket _socket;
    };

} // namespace network

#endif // BABEL_ASIOCLIENTTCP_HPP