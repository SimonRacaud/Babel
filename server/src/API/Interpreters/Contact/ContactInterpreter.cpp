/*
 * EPITECH PROJECT, 2021
 * Contact
 * File description:
 * ContactInterpreter.cpp - Created: 27/09/2021
 */

#include <cstring>
#include <strings.h>

#include "ContactInterpreter.hpp"
#include "ContactRaw.hpp"
#include "UserRaw.hpp"

using namespace Network;

template <size_t PACKETSIZE>
ContactInterpreter<PACKETSIZE>::ContactInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager)
    : _databaseManager(databaseManager), _network(network)
{
}

template <size_t PACKETSIZE>
void ContactInterpreter<PACKETSIZE>::GET(const TCPTramExtract<PACKETSIZE> &tramExtract, const string &ip, const size_t &port)
{
    const auto &contacts = tramExtract.template getListOf<ContactRaw>();
    const std::vector<User> &result = this->_databaseManager.getContacts(contacts[0].username);
    std::vector<UserRaw> list;
    UserRaw userRaw;

    if (result.size() * sizeof(User) > PACKETSIZE)
        throw std::out_of_range("Response size > PACKETSIZE(" + myToString(PACKETSIZE) + ")");
    for (size_t i = 0; i < result.size(); i++) {
        bzero(&userRaw, sizeof(UserRaw));
        std::strcpy(userRaw.username, result[i].username.c_str());
        std::strcpy(userRaw.ip, result[i].ip.c_str());
        userRaw.port = result[i].port;

        list.push_back(userRaw);
    }

    TCPTram tram(TramAction::GET, TramType::CONTACT);
    tram.setUserList(list);
    this->_send(tram, ip, port);
}

template <size_t PACKETSIZE>
void ContactInterpreter<PACKETSIZE>::POST(
    const TCPTramExtract<PACKETSIZE> &tramExtract, UNUSED const string &ip, UNUSED const size_t &port)
{
    const auto &contacts = tramExtract.template getListOf<ContactRaw>();

    this->_databaseManager.newContact(contacts[0].username, contacts[0].contactName);
}

template <size_t PACKETSIZE>
void ContactInterpreter<PACKETSIZE>::DELETE(
    const TCPTramExtract<PACKETSIZE> &tramExtract, UNUSED const string &ip, UNUSED const size_t &port)
{
    const auto &contacts = tramExtract.template getListOf<ContactRaw>();

    this->_databaseManager.removeContact(contacts[0].username, contacts[0].contactName);
}

template <size_t PACKETSIZE> void ContactInterpreter<PACKETSIZE>::_send(const TCPTram &tram, const string &ip, const size_t &port)
{
    if (ip == "" && port == 0)
        this->_network.sendAll(*tram.template getBuffer<PACKETSIZE>());
    else
        this->_network.send(*tram.template getBuffer<PACKETSIZE>(), ip, port);
}

template class ContactInterpreter<Network::BUFFER_SIZE>;