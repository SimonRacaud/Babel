/*
** EPITECH PROJECT, 2021
** AsioConnectionTCP.hpp
** File description:
** Network TCP implementation with Asio lib, according to IConnection interface
*/

#ifndef BABEL_ASIOCONNECTIONTCP_HPP
#define BABEL_ASIOCONNECTIONTCP_HPP

#include <functional>
#include <memory>

#include "ANetwork.hpp"

namespace Network
{
    using asio::ip::tcp;

    template <std::size_t PACKETSIZE> class AsioConnectionTCP : public AAsioConnection<PACKETSIZE> {
      public:
        AsioConnectionTCP(const bool server = false) : AAsioConnection<PACKETSIZE>(server)
        {
        }

        void disconnect(const std::string &ip, const std::size_t port)
        {
            auto socketConnection(std::find_if(_socketConnections.begin(),
                _socketConnections.end(),
                std::bind(&AsioConnectionTCP::isConnection, this, std::placeholders::_1, ip, port)));

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
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf({0}, 0);
            auto connection(getConnection(ip, port));

            auto my_recvData(std::find_if(_recvData.begin(),
                _recvData.end(),
                [&](std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> &recvData) {
                    if (ip == std::get<2>(recvData) && port == std::get<3>(recvData)) {
                        return true;
                    }
                    return false;
                }));
            if (my_recvData != _recvData.end()) {
                _recvData.erase(my_recvData);
                return std::make_pair(std::get<0>(*my_recvData), std::get<1>(*my_recvData));
            }
            return std::pair<std::array<char, PACKETSIZE>, std::size_t>({}, 0);
        }

        void sendAll(const std::array<char, PACKETSIZE> &buf) override
        {
            for (auto &connection : _socketConnections) {
                send(buf, connection);
            }
        }

        void send(const std::array<char, PACKETSIZE> &buf, const std::string &ip, const std::size_t port) override
        {
            auto connection(getConnection(ip, port));

            send(buf, connection);
        }

      protected:
        void send(const std::array<char, PACKETSIZE> &buf, std::shared_ptr<tcp::socket> &connection) // todo put in private ?
        {
            if (!connection) {
                return; // todo connect() ??
            }
            //            asio::async_write(*connection, asio::buffer(buf), [](const asio::error_code &, std::size_t) {
            //            connection->async_send(asio::buffer(buf), [](const asio::error_code &, std::size_t) {
            connection->send(asio::buffer(std::string(buf.data(), buf.size())));
        }

        bool isConnection(
            const std::shared_ptr<tcp::socket> &connection, const std::string &otherIp, const std::size_t otherPort) const
        {
            auto endpoint(connection->remote_endpoint());

            std::cout << endpoint.address().to_string() << std::endl;
            std::cout << otherIp << std::endl;
            std::cout << endpoint.port() << std::endl;
            std::cout << otherPort << std::endl;
            if (endpoint.address().to_string() == otherIp && endpoint.port() == otherPort) // todo incompatible types ?
                return true;
            return false;
        }

        std::shared_ptr<tcp::socket> getConnection(const std::string &ip, const std::size_t port)
        {
            for (auto socketConnection : _socketConnections) {
                std::cout << "hello" << std::endl;
                if (isConnection(socketConnection, ip, port)) { // todo probably a problem here
                    return socketConnection;
                }
            }
            return nullptr;
        }

        /**
         * @brief Record a connection and be ready to receive data from it
         * @param newConnection The connection to record
         */
        void addConnection(std::shared_ptr<tcp::socket> newConnection)
        {
            if (!newConnection)
                return;
            AAsioConnection<PACKETSIZE>::connect(
                newConnection->remote_endpoint().address().to_string(), newConnection->remote_endpoint().port());
            _socketConnections.push_back(newConnection);

            asyncReceive(newConnection);
        }

        /**
         * @brief Initialize asynchronous data acceptance from every connection
         */
        void asyncReceiveAny()
        {
            for (auto &connection : _socketConnections) {
                asyncReceive(connection);
            }
        }

        /**
         * @brief Initialize asynchronous data acceptance from this connection
         * @param connection The socket, where the data can come from
         */
        void asyncReceive(std::shared_ptr<tcp::socket> &connection)
        {
            if (!connection)
                return;
            connection->async_receive(asio::buffer(_recvBuf.data(), _recvBuf.size()),
                std::bind(
                    &AsioConnectionTCP<PACKETSIZE>::asyncReceiving, this, std::placeholders::_1, std::placeholders::_2, connection));
        }

        void asyncReceiving(const asio::error_code &err, const std::size_t &lenRecvBuf, std::shared_ptr<tcp::socket> &connection)
        {
            if (err) {
                std::cerr << "todo remove from connectinos" << std::endl;
                // todo remove from connection if err == deconnected
            }
            if (!lenRecvBuf)
                return;
            if (!_recvBuf.data())
                return;

            //                _recvData.push_back(std::make_tuple(_recvBuf,
            //                    lenRecvBuf,
            //                    connection->remote_endpoint().address().to_string(),
            //                    connection->remote_endpoint().port()));
            //            _recvData.emplace_back(_recvBuf.data(),
            //                lenRecvBuf,
            //                connection->remote_endpoint().address().to_string(),
            //                connection->remote_endpoint().port());
            std::cout.write(_recvBuf.data(), lenRecvBuf);
            std::cout << std::endl;
            asyncReceive(connection);
        }

        /**
         * @brief deque of connected sockets
         */
        std::deque<std::shared_ptr<tcp::socket>> _socketConnections;

        /**
         * @brief deque containing data, received from connections through asynchronous operations
         */
        std::deque<std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t>> _recvData;

        std::array<char, PACKETSIZE> _recvBuf{0};
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONTCP_HPP