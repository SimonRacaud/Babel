/*
 * EPITECH PROJECT, 2021
 * Contact
 * File description:
 * ContactInterpreter.cpp - Created: 27/09/2021
 */

#include <cstring>

#include "Contact.hpp"
#include "ContactInterpreter.hpp"

using namespace Network;

template <size_t PACKETSIZE>
ContactInterpreter<PACKETSIZE>::ContactInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager)
    : _network(network), _databaseManager(databaseManager)
{
}

template <size_t PACKETSIZE> void ContactInterpreter<PACKETSIZE>::GET(const TramTCP &tram, const string &ip, const size_t &port)
{
    const ContactRaw contact = static_cast<ContactRaw>(tram.list);
    const std::vector<User> &result = this->_databaseManager.getContacts(contact.username);
    std::array<char, PACKETSIZE> response;
    UserRaw userRaw;

    if (result.size() * sizeof(User) > PACKETSIZE)
        throw std::out_of_range("Response size > PACKETSIZE(" + toString(PACKETSIZE) + ")");
    for (size_t i = 0; i < result.size(); i++) {
        userRaw = {
            result[i].username.c_str(),
            result[i].ip.c_str(),
            result[i].port,
        };
        std::memcpy(response[i * sizeof(UserRaw)], &userRaw, sizeof(UserRaw))
    }

    this->_send(response, ip, port);
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