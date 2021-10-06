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
    const auto &users = tramExtract.template getListOf<UserRaw>();
    const User &result = this->_databaseManager.getUser(users[0].username);
    std::vector<UserRaw> list;
    UserRaw resultRaw;
    std::strcpy(resultRaw.username, result.username.c_str());
    std::strcpy(resultRaw.ip, result.ip.c_str());
    resultRaw.port = result.port;

    list.push_back(resultRaw);
    TCPTram tram(tramExtract.getAction(), tramExtract.getType());
    tram.setUserList(list);
    this->_send(tram, ip, port);
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::POST(const TCPTramExtract<PACKETSIZE> &tramExtract, const string &ip, const size_t &port)
{
    const auto &users = tramExtract.template getListOf<UserRaw>();

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