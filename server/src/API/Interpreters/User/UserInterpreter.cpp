/*
 * EPITECH PROJECT, 2021
 * User
 * File description:
 * UserInterpreter.cpp - Created: 27/09/2021
 */

#include <stdexcept>

#include "User.hpp"
#include "UserInterpreter.hpp"

using namespace Network;

template <size_t PACKETSIZE>
UserInterpreter<PACKETSIZE>::UserInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager)
    : _network(network), _databaseManager(databaseManager)
{
}

template <size_t PACKETSIZE> void UserInterpreter<PACKETSIZE>::GET(const TramTCP &tram, const string &ip, const size_t &port)
{
    const UserRaw user = static_cast<UserRaw>(tram.list);
    const User &result = this->_databaseManager.getUser(user.username);
    const UserRaw response = {
        result.username.c_str(),
        result.ip.c_str(),
        result.port,
    };

    this->_send(response, ip, port);
}

template <size_t PACKETSIZE> void UserInterpreter<PACKETSIZE>::POST(const TramTCP &tram, const string &ip, const size_t &port)
{
    const UserRaw user = static_cast<UserRaw>(tram.list);

    this->_databaseManager.setUser(user.username, user.ip, user.port);
}

template <size_t PACKETSIZE>
void UserInterpreter<PACKETSIZE>::DELETE(UNUSED const TramTCP &tram, UNUSED const string &ip, UNUSED const size_t &port)
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