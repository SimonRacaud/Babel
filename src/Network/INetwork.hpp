/*
** EPITECH PROJECT, 2021
** INetwork.hpp
** File description:
** Network interface
*/

#ifndef BABEL_NETWORK_HPP
#define BABEL_NETWORK_HPP

#include <array>
#include <queue>
#include <string>

#include <concepts>
#include <utility>
#include "asio.hpp"

namespace network
{
    enum protocol { TCP, UDP };

    template <typename PACKETSIZE>
    requires unsigned_integral<PACKETSIZE>
    class IConnection
    /* TODO do a template with the container that contains the data (that
     * would replace arrays) ?? if yes, constrained with concepts ?? */
    {
      public:
        /**
         * @brief Connect to a remote INetwork class
         * @param ip The ip of the targeted machine
         * @param port The port on which the socket is open
         */
        virtual void connect(std::string ip, unsigned int port) = 0;

        /**
         * @brief Disconnect from a particular machine
         * @param ip The machine's ip address
         * @param port The machine's socket port that was connected
         */
        virtual void disconnect(std::string ip, unsigned int port) = 0;
        /**
         * @brief Disconnect from every connected machine
         */
        virtual void disconnectAll() = 0;

        /**
         * @brief Receive data from every machine connected
         * @return The first data caught, and infos about the sender
         */
        virtual std::pair<std::pair<std::array<char, PACKETSIZE> buf>,
            std::array<char, PACKETSIZE>>
        receiveAny() = 0;
        /**
         * @brief Receive data from a particular machine
         * @param ip The machine's ip address
         * @param port The machine's connected socket port
         * @return The data received, '\0's if nothing received
         */
        virtual std::array<char, PACKETSIZE> receive(
            std::string ip, unsigned int port) = 0;

        /**
         * @brief Send data to every machine connected
         * @param buf The data in a binary form
         */
        virtual void sendAll(std::array<char, PACKETSIZE> buf) = 0;

        /**
         * @brief Send data to a particular machine
         * @param buf The data sent
         * @param ip The machine's ip address
         * @param port The machine's connected socket port
         */
        virtual void send(std::array<char, PACKETSIZE> buf, std::string ip,
            unsigned int port) = 0;

        /**
         * @brief Check if a machine is connected
         * @param ip The machine's ip address
         * @param port The machine's supposedly connected socket port
         * @return True if connected, false otherwise
         */
        virtual bool isConnected(std::string ip, unsigned int port) const = 0;
        // TODO put in abstract class ?
    };

} // namespace network

#endif // BABEL_NETWORK_HPP