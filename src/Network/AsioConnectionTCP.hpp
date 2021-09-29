/*
** EPITECH PROJECT, 2021
** AsioConnectionTCP.hpp
** File description:
** Network TCP implementation with Asio lib, according to IConnection interface
*/

#ifndef BABEL_ASIOCONNECTIONTCP_HPP
#define BABEL_ASIOCONNECTIONTCP_HPP

#include <functional>
#include <iostream> // todo remove after test
#include <memory>

#include "ANetwork.hpp"

namespace network
{
    using asio::ip::tcp;

    template <std::size_t PACKETSIZE> class AsioConnectionTCP : public AAsioConnection<PACKETSIZE> {
        virtual void connect(const std::string &ip, const std::size_t port)
        {
            _socketConnections.push_back(newConnection);
        }

        void disconnect(const std::string &ip, const std::size_t port)
        {
            auto socketConnection(std::find_if(_socketConnections.begin(),
                _socketConnections.end(),
                std::bind(&AsioServerTCP::isConnection, this, std::placeholders::_1, ip, port)));

            if (socketConnection == _socketConnections.end())
                return;
            auto connectionEndpoint((*socketConnection)->remote_endpoint());
            //            _socketConnections.erase(socketConnection); // todo fix problem (also in AAsioConnection::disconnect)
            AAsioConnection<PACKETSIZE>::disconnect(connectionEndpoint.address().to_string(), connectionEndpoint.port());
        }

        void disconnectAll()
        {
            _socketConnections.clear();
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() override
        {
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf;

            for (const auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                buf = receive(connection.first, connection.second);

                if (buf.second != 0)
                    return std::make_tuple(buf.first, buf.second, connection.first, connection.second);
                // std::cout.write(buf.data(), len);
                //  to write the good amount of data
            }

            return std::make_tuple(std::array<char, PACKETSIZE>(), 0, "", 0);
        }

        std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(const std::string &ip, const std::size_t port) override
        {
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf;
            auto connection(getConnection(ip, port));

            if (!connection)
                return buf;
            asio::async_read(*connection,
                             asio::buffer(buf.first),
                             [](const asio::error_code &, std::size_t){}
                /*std::bind(
                    [&](const asio::error_code &error, tcp::endpoint endpoint, const std::size_t bytesTransferred) {
                        buf.second = bytesTransferred;
                        return;
                    },
                    this, // todo useless ?
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3)*/);

            // todo test if received well here
            return buf;
        }

        void sendAll(const std::array<char, PACKETSIZE> &buf) override
        {
            for (const auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                send(buf, connection.first, connection.second);
            }
        }

        void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port) override
        {
            auto connection(getConnection(ip, port));

            if (!connection)
                return; // todo connect() ??

            asio::async_write(*connection,
                              asio::buffer(buf),
                              [](const asio::error_code &, std::size_t){}
                /*
                std::bind(
                    [&](const asio::error_code &error, tcp::endpoint endpoint, const std::size_t bytesTransferred) {
                        if (error)
                            std::cout << "error" << std::endl; // todo do something ?
                        return;
                    },
                    this, // todo useless ?
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3)*/);
        }

      protected:
        bool isConnection(
            const std::shared_ptr<tcp::socket> &connection, const std::string &otherIp, const std::size_t otherPort) const
        {
            auto endpoint(connection->remote_endpoint());

            if (endpoint.address().to_string() == otherIp && endpoint.port() == otherPort) // todo incompatible types ?
                return true;
            return false;
        }

        std::shared_ptr<tcp::socket> getConnection(const std::string &ip, const std::size_t port)
        {
            for (auto socketConnection(_socketConnections.begin()); socketConnection != _socketConnections.end(); socketConnection++) {
                if (isConnection(*socketConnection, ip, port))
                    return *socketConnection; // todo doubt
            }
            return nullptr;
        }

        std::deque<std::shared_ptr<tcp::socket>> _socketConnections;
    };
} // namespace network

#endif // BABEL_ASIOCONNECTIONTCP_HPP