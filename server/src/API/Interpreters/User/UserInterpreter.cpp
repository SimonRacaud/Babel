/*
 * EPITECH PROJECT, 2021
 * User
 * File description:
 * UserInterpreter.cpp - Created: 27/09/2021
 */

#include <stdexcept>

#include "UserInterpreter.hpp"
#include "UserRaw.hpp"

using namespace Network;

template <size_t PACKETSIZE>
UserInterpreter<PACKETSIZE>::UserInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager)
    : _databaseManager(databaseManager), _network(network)
{
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::GET(const TCPTramExtract<PACKETSIZE> &tramExtract, const string &ip, const size_t &port)
{
    std::cout << "in GET() : " << std::endl;

    const auto &users = tramExtract.template getListOf<UserRaw>();
    std::cout << "users[0].username : " << users[0].username << std::endl;
    //
    const User &result = this->_databaseManager.getUser(users[0].username);
    //
    std::vector<UserRaw> list;
    UserRaw resultRaw;
    std::strcpy(resultRaw.username, result.username.c_str());
    std::cout << "resultRaw.username : " << resultRaw.username << std::endl;
    std::strcpy(resultRaw.ip, result.ip.c_str());

    resultRaw.port = result.port;
    list.push_back(resultRaw);
    for (const auto &item : list) {
        std::cout << "item.username : " << item.username << std::endl;
        std::cout << "item.ip : " << item.ip << std::endl;
        std::cout << "item.port : " << item.port << std::endl;
    }
    TCPTram tram(tramExtract.getAction(), tramExtract.getType());
    tram.setUserList(list);
    std::cout << "get buffer : " << std::endl;
    std::cout.write(tram.getBuffer<PACKETSIZE>().data(), PACKETSIZE);
    std::cout << " | end of buffer" << std::endl;
    this->_send(tram, ip, port);
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::POST(const TCPTramExtract<PACKETSIZE> &tramExtract, const string &ip, const size_t &port)
{
    const auto &users = tramExtract.template getListOf<UserRaw>();

    std::cout << "POST()" << std::endl;
    std::cout << " users[0].username : " << users[0].username << std::endl;
    std::cout << " users[0].ip : " << users[0].ip << std::endl;
    std::cout << " users[0].port : " << users[0].port << std::endl;
    this->_databaseManager.setUser(users[0].username, users[0].ip, users[0].port);
    this->GET(tramExtract, ip, port);
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::DELETE(
    UNUSED const TCPTramExtract<PACKETSIZE> &tramExtract, UNUSED const string &ip, UNUSED const size_t &port)
{
    throw std::runtime_error("Method not override");
}

template <size_t PACKETSIZE> void UserInterpreter<PACKETSIZE>::_send(const TCPTram &tram, const string &ip, const size_t &port)
{
    if (ip == "" && port == 0)
        this->_network.sendAll(tram.getBuffer<PACKETSIZE>());
    else
        this->_network.send(tram.getBuffer<PACKETSIZE>(), ip, port);
}

template class UserInterpreter<Network::BUFFER_SIZE>;