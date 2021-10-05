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
                        std::move(*i);
        }

        virtual void disconnectAll()
        {
            AAsioConnection<PACKETSIZE>::disconnectAll();
            _socketConnections.clear();
        }

        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> receiveAny() override
        {
            std::pair<std::array<char, PACKETSIZE>, std::size_t> buf;

            //            std::cout << "before receive loop" << std::endl;
            for (const auto &connection : AAsioConnection<PACKETSIZE>::_connections) {
                buf = receive(connection.first, connection.second);

                if (buf.second != 0) {
                    std::cout << "received in receiveAny" << std::endl;
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
                if (recvData.first.first == "127.0.0.1" && port == recvData.first.second) {
                    return true;
                }
                if (recvData.first.first == "0.0.0.0" && port == recvData.first.second) {
                    return true;
                }
                std::cout << "about to show information" << std::endl;
                std::cout << "ip : " << recvData.first.first << std::endl;
                std::cout << "port : " << recvData.first.second << std::endl;
                return false;
            }));
            //            std::cout << "received in receive" << std::endl;
            if (my_recvData != _recvData.end()) {
                std::cout << "received in receive" << std::endl;
                buf = std::make_pair(my_recvData->second.first, my_recvData->second.second);
                //                _recvData.erase(my_recvData);
                _recvData.extract(my_recvData);
                std::cout.write(buf.first.data(), buf.second);
                std::cout << std::endl;
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

        void run()
        {
            AAsioConnection<PACKETSIZE>::_ioContext.run_one();
        }
        /**
         * @brief Create a thread, which will launch asynchronous actions, if one is done, thread is over
         */
        void runOneAction()
        {
            if (_activeThread)
                return;
            std::cout << "hello" << std::endl;
            /**
             * @brief Allows io_context.run_one for connection and receiving successively and independently
             */
            std::thread my_thread(&AsioConnectionTCP<PACKETSIZE>::realRunOneAction, this); // todo handle sigabort
            std::cout << " world " << std::endl;
            // TODO why this function is called 4 times at the begining of the program

            //            my_thread.detach(); // todo not shure if this allows thread to modify the boolean _activeThread
            // todo why the thread cant be ran without .detach() ?
            // todo find a way to not use detach but still run the thread

            std::cout << "goodbye" << std::endl;
        }

      protected:
        /**
         * @brief loop through awaiting asynchronous actions and stop if one is done
         *  to be called every time a connection or data is to be received
         */
        void realRunOneAction()
        {
            std::cout << "real run" << std::endl;
            _activeThread = true;
            AAsioConnection<PACKETSIZE>::_ioContext.run_one();
            _activeThread = false;
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
            std::cout << "initialized" << std::endl;
            connection->async_receive(asio::buffer(_recvBuf.data(), _recvBuf.size()),
                std::bind(
                    &AsioConnectionTCP<PACKETSIZE>::asyncReceiving, this, std::placeholders::_1, std::placeholders::_2, connection));
        }

        void asyncReceiving(const asio::error_code &err, const std::size_t &lenRecvBuf, std::shared_ptr<tcp::socket> &connection)
        {
            std::cout << "checking error" << std::endl;
            sleep(1);
            if (err) {
                if (err.value() == asio::error::misc_errors::eof) {
                    return;
                }
            }
            std::cout << "checking length" << std::endl;
            sleep(1);

            if (!lenRecvBuf) {
                return;
            }
            std::cout << "checking data" << std::endl;
            sleep(1);

            if (!_recvBuf.data()) {
                return;
            }
            std::cout << lenRecvBuf << std::endl;
            sleep(1);
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

        bool _activeThread{false};
        std::array<char, PACKETSIZE> _recvBuf{0};
    };

} // namespace Network

#endif // BABEL_ASIOCONNECTIONTCP_HPP