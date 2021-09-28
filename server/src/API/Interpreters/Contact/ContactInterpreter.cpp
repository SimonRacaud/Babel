/*
 * EPITECH PROJECT, 2021
 * Contact
 * File description:
 * ContactInterpreter.cpp - Created: 27/09/2021
 */

#include "ContactInterpreter.hpp"
#include "Contact.hpp"

using namespace Network;

template <size_t PACKETSIZE>
ContactInterpreter<PACKETSIZE>::ContactInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager)
    : _network(network), _databaseManager(databaseManager)
{
}

template <size_t PACKETSIZE> void ContactInterpreter<PACKETSIZE>::GET(const TramTCP &tram, const string &ip, const size_t &port)
{
    const ContactRaw contact = static_cast<ContactRaw>(tram.list);
    const auto &result = this->_databaseManager.getContacts(contact.username);

    this->_send(result, ip, port);
}

template <size_t PACKETSIZE> void ContactInterpreter<PACKETSIZE>::POST(const TramTCP &tram, const string &ip, const size_t &port)
{
    const ContactRaw contact = static_cast<ContactRaw>(tram.list);

    this->_databaseManager.newContact(contact.username, contact.contactName);
}

template <size_t PACKETSIZE> void ContactInterpreter<PACKETSIZE>::DELETE(const TramTCP &tram, const string &ip, const size_t &port)
{
    const ContactRaw contact = static_cast<ContactRaw>(tram.list);

    this->_databaseManager.removeContact(contact.username, contact.contactName);
}

template <size_t PACKETSIZE>
void ContactInterpreter<PACKETSIZE>::_send(const std::array<char, PACKETSIZE> &data, const string &ip, const size_t &port)
{
    if (ip == "" && port == 0)
        this->_network.sendAll(data);
    else
        this->_network.send(data, ip, port);
}