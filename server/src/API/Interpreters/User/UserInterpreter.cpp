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
void UserInterpreter<PACKETSIZE>::GET(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port)
{
    const auto &users = tram.template getListOf<UserRaw>();
    const User &result = this->_databaseManager.getUser(users[0].username);
    UserRaw resultRaw;
    std::strcpy(resultRaw.username, result.username.c_str());
    std::strcpy(resultRaw.ip, result.ip.c_str());
    resultRaw.port = result.port;

    std::array<char, PACKETSIZE> response;

    std::memcpy(response.data(), &resultRaw, sizeof(UserRaw));
    this->_send(response, ip, port);
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::POST(const TCPTramExtract<PACKETSIZE> &tram, UNUSED const string &ip, UNUSED const size_t &port)
{
    const auto &users = tram.template getListOf<UserRaw>();

    this->_databaseManager.setUser(users[0].username, users[0].ip, users[0].port);
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::DELETE(
    UNUSED const TCPTramExtract<PACKETSIZE> &tram, UNUSED const string &ip, UNUSED const size_t &port)
{
    throw std::runtime_error("Method not override");
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::_send(const std::array<char, PACKETSIZE> &data, const string &ip, const size_t &port)
{
    if (ip == "" && port == 0)
        this->_network.sendAll(data);
    else
        this->_network.send(data, ip, port);
}

template class UserInterpreter<T_PACKETSIZE>;