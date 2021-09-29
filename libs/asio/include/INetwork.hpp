/*
** EPITECH PROJECT, 2021
** INetwork.hpp
** File description:
** Network interface
*/

#ifndef BABEL_NETWORK_HPP
#define BABEL_NETWORK_HPP

#include <array>
#include <cstddef>
#include <queue>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "asio.hpp"

namespace Network
{
    enum protocol
    {
        TCP,
        UDP
    };

    template <std::size_t PACKETSIZE>
    class IConnection
    /* TODO do a template with the container that contains the data (that
     * would replace arrays) ?? if yes, constrained with concepts ?? */
    {
      public:
        /**
         * @brief Connect to a remote INetwork class
         * @param ip The ip of the targeted machine
         */
        virtual void connect(const std::string &ip, const std::size_t port) = 0;

        /**
         * @brief Disconnect from a particular machine
         * @param ip The machine's ip address
         */
        virtual void disconnect(const std::string &ip, const std::size_t port) = 0;
        /**
         * @brief Disconnect from every connected machine
         */
        virtual void disconnectAll() = 0;

        /**
         * @brief Receive data from any machine connected
         * @return The first data caught, its length, and infos about the
         * sender (ip and port)
         */
        virtual std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() = 0;
        /**
         * @brief Receive data from a particular machine
         * @param ip The machine's ip address
         * @return The data received, '\0's if nothing received
         */
        virtual std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(const std::string &ip, const std::size_t port) = 0;

        /**
         * @brief Send data to every machine connected
         * @param buf The data in a binary form
         */
        virtual void sendAll(const std::array<char, PACKETSIZE> &buf) = 0;

        /**
         * @brief Send data to a particular machine
         * @param buf The data sent
         * @param ip The machine's ip address
         */
        virtual void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port) = 0;

        /**
         * @brief Check if a machine is connected
         * @param ip The machine's ip address
         * @return True if connected, false otherwise
         */
        virtual bool isConnected(const std::string &ip, const std::size_t port) const = 0;
    };

} // namespace Network

#endif // BABEL_NETWORK_HPP