/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include "Network/AsioConnectionUDP.hpp"

#define PACKETSIZE 123

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
            my_connection.send(my_dataToSend, ip, portOther);
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
            receivedData = my_connection.receive(ip, port);
            std::cout << "dataLength : " << receivedData.second << std::endl;
            std::cout.write(receivedData.first.data(), receivedData.second);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}