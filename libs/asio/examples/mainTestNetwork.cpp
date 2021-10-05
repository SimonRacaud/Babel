/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioConnectionUDP.hpp"

static const std::size_t PACKETSIZE = 123;
/*

int main(__attribute__((unused)) const int ac, const char *av[])
{
    std::string ip;
    std::size_t port = 0;
    std::stringstream stream(av[2]);
    std::stringstream streamOther(av[3]);

    ip = std::string(av[1]);
    stream >> port;
    std::size_t portOther;
    streamOther >> portOther;
    asio::io_context _ioContext;
    //    asio::ip::udp::endpoint _endpoint(asio::ip::udp::v4(), port);
    //    asio::ip::udp::socket _socket(_ioContext, _endpoint);

    std::array<char, PACKETSIZE> my_dataToSend{"hello world"};
    //    std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string,
    //        std::size_t>
    //        receivedData;
    std::pair<std::array<char, PACKETSIZE>, std::size_t> receivedData;
    std::array<char, PACKETSIZE> data;
    std::size_t dataLength;
    std::string ipSender;
    std::size_t portSender;

    try {
        network::AsioConnectionUDP<PACKETSIZE> my_connection(port);
        if (std::string(av[4]) == "send") {
            std::cout << "sending to "
                      << " ip :" << ip << " port :" << portOther << std::endl;
            //            my_connection.connect(ip, port);
            size_t tmp = 0;
            while (1) {
                std::string str("hello world: " + std::to_string(tmp++) + "\n");
                std::memset(my_dataToSend.data(), 0, PACKETSIZE);
                std::memcpy(my_dataToSend.data(), str.c_str(), str.size());
                my_connection.send(my_dataToSend, ip, portOther);
                sleep(1);
            }
            //my_connection.send(my_dataToSend, ip, portOther);
        } else {
            sleep(2);
            std::cout << "receiving from "
                      << " ip :" << ip << " port :" << port << std::endl;
            //            my_connection.connect(ip, port);
            //            receivedData = my_connection.receiveAny();
            //            std::tie(data, dataLength, ipSender, portSender) =
            //            receivedData; std::cout << "dataLength : " <<
            //            dataLength << std::endl; std::cout.write(data.data(),
            //            dataLength);
            while (1) {
                receivedData = my_connection.receive(ip, port);
                std::cout.write(receivedData.first.data(), receivedData.second);
                sleep(1);
            }
            //receivedData = my_connection.receive(ip, port);
            //std::cout << "dataLength : " << receivedData.second << std::endl;
            //std::cout.write(receivedData.first.data(), receivedData.second);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}*/

#include "AsioClientTCP.hpp"
#include "AsioServerTCP.hpp"

using namespace Network;

int main(const int ac, __attribute__((unused)) const char *av[])
{
    if (ac == 1) { // server
        std::array<char, PACKETSIZE> sendBuf{"hello my_dude"};

        AsioClientTCP<PACKETSIZE> client;
        client.connect("0.0.0.0", 8080);
        //        client.sendAll(sendBuf);

        client.send(sendBuf, "127.0.0.1", 8080);
        std::cout << "client sent" << std::endl;
        //        client.disconnectAll();
        client.disconnect("0.0.0.0", 8080);
    } else /* client */ {
        // todo tcp server throws when already opened in same port and ip
        std::tuple<std::array<char, PACKETSIZE>, std::size_t, std::string, std::size_t> recvData;

        std::array<char, PACKETSIZE> recvBuf;
        std::size_t lenBuf;
        std::string ipSender;
        std::size_t portSender;

        AsioServerTCP<PACKETSIZE> server(8080);

        server.runAsync();
        while (1) {
            recvData = server.receiveAny();
            std::tie(recvBuf, lenBuf, ipSender, portSender) = recvData;
            if (lenBuf) {
                std::cout << "! server received !" << std::endl;
                std::cout.write(recvBuf.data(), lenBuf);
                std::cout << std::endl;
            }
            //            server.runOneAction();
        }
    }
    return 0;
}