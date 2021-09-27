/*
** EPITECH PROJECT, 2021
** AsioClientTCP.hpp
** File description:
** TODO: add description
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
            //            asio::connect(_socket, _endpoints);
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny()
        {
        }

        std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(const std::string &ip, const std::size_t port)
        {
        }

        void sendAll(const std::array<char, PACKETSIZE> &buf)
        {
        }

        void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port)
        {
        }

      private:
        tcp::resolver _resolver;
        tcp::resolver::results_type _endpoints;
        tcp::socket _socket;
    };

} // namespace network

#endif // BABEL_ASIOCLIENTTCP_HPP