/*
** EPITECH PROJECT, 2021
** AsioConnectionTCP.hpp
** File description:
** Network TCP implementation with Asio lib, according to IConnection interface
*/

#ifndef BABEL_ASIOCONNECTIONTCP_HPP
#define BABEL_ASIOCONNECTIONTCP_HPP

#include <functional>
#include <unordered_map>

#include <asio/error.hpp>
#include <thread>
#include "ANetwork.hpp"

struct hash_pair {
    std::size_t operator()(const std::pair<std::string, std::size_t> &pair) const
    {
        std::size_t h1 = std::hash<std::string>{}(pair.first);
        std::size_t h2 = std::hash<std::size_t>{}(pair.second);

        return h1 ^ h2;
    }
};

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
            auto first(_socketConnections.begin());
            auto last(_socketConnections.end());
            auto connection(getConnection(ip, port));

            if (!connection)
                return;
            first = std::find(first, last, connection);
            AAsioConnection<PACKETSIZE>::disconnect(
                connection->remote_endpoint().address().to_string(), connection->remote_endpoint().port());
            if (first != last)
                for (auto i = first; ++i != last;)
                    if (!(*i == connection))
                        (void) std::move(*i);
        }

        virtual void disconnectAll()
        {
            AAsioConnection<PACKETSIZE>::disconnectAll();
            _socketConnections.clear();
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() override
        {
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf;

            for (const auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                buf = receive(connection.first, connection.second);

                if (buf.second != 0) {
                    return std::make_tuple(buf.first, buf.second, connection.first, connection.second);
                }
                /**
                 * @brief Write the good amount of data :
                 *  std::cout.write(recvBuf.data(), len);
                 */
            }

            return std::make_tuple(std::array<char, PACKETSIZE>(), 0, "", 0);
        }

        std::pair<std::array<char, PACKETSIZE>, std::size_t> receive(const std::string &ip, const std::size_t port) override
        {
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf({0}, 0);
            auto connection(getConnection(ip, port));

            auto my_recvData(std::find_if(_recvData.begin(), _recvData.end(), [&](const auto &recvData) {
                if (ip == recvData.first.first && port == recvData.first.second) {
                    return true;
                }
                return false;
            }));
            if (my_recvData != _recvData.end()) {
                buf = std::make_pair(my_recvData->second.first, my_recvData->second.second);
                _recvData.erase(my_recvData);
                return buf;
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

        /**
         * @brief Blocks until one asynchronous action is performed (connection or data receive)
         */
        void runOneAction()
        {
            AAsioConnection<PACKETSIZE>::_ioContext.run_one();
        }
        /**
         * @brief Create a thread, which will execute asynchronous actions on network (accept connections and receive data)
         */
        void runAsync()
        {
            if (_activeThread)
                return;
            _thread = std::thread(&AsioConnectionTCP<PACKETSIZE>::realRunAsync, this);
            _thread.detach();
        }

        void stopRunAsync()
        {
            _activeThread = false;
            if (!AAsioConnection<PACKETSIZE>::_ioContext.stopped())
                AAsioConnection<PACKETSIZE>::_ioContext.stop();
        }

      protected:
        /**
         * @brief loop through awaiting asynchronous actions and stop if one is done
         *  to be called every time a connection or data is to be received
         */
        void realRunAsync()
        {
            _activeThread = true;
            while (_activeThread)
                AAsioConnection<PACKETSIZE>::_ioContext.run();
        }
        void send(const std::array<char, PACKETSIZE> &buf, std::shared_ptr<tcp::socket> &connection)
        {
            if (!connection) {
                return;
            }
            connection->send(asio::buffer(std::string(buf.data(), buf.size())));
        }

        bool isConnection(
            const std::shared_ptr<tcp::socket> &connection, const std::string &otherIp, const std::size_t otherPort) const
        {
            if (!connection)
                return false;
            auto endpoint(connection->remote_endpoint());

            if (endpoint.address().to_string() == otherIp && endpoint.port() == otherPort)
                return true;
            return false;
        }

        std::shared_ptr<tcp::socket> getConnection(const std::string &ip, const std::size_t port)
        {
            for (auto socketConnection : _socketConnections) {
                if (isConnection(socketConnection, ip, port)) {
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
                if (err.value() == asio::error::misc_errors::eof) {
                    return;
                }
            }
            if (!lenRecvBuf) {
                return;
            }
            if (!_recvBuf.data()) {
                return;
            }
            _recvData.emplace(
                std::make_pair(connection->remote_endpoint().address().to_string(), connection->remote_endpoint().port()),
                std::make_pair(_recvBuf, lenRecvBuf));
            asyncReceive(connection);
        }

        /**
         * @brief deque of connected sockets
         */
        std::deque<std::shared_ptr<tcp::socket>> _socketConnections;

        /**
         * @brief deque containing data, received from connections through asynchronous operations
         */
        std::unordered_map<std::pair<const std::string, const std::size_t>,
            std::pair<std::array<char, PACKETSIZE>, std::size_t>,
            hash_pair>
            _recvData;

        std::thread _thread;
        bool _activeThread{false};
        std::array<char, PACKETSIZE> _recvBuf{0};
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONTCP_HPP