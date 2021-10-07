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
    std::vector<UserRaw> list;
    UserRaw userRaw;

    for (const ContactRaw &contact : contacts) {
        std::cout << "GET CONTACT: " << contact << std::endl;
        const std::vector<User> &result = this->_databaseManager.getContacts(contact.username);

        if (result.size() * sizeof(UserRaw) > PACKETSIZE)
            throw std::out_of_range("Response size > PACKETSIZE(" + myToString(PACKETSIZE) + ")");
        for (size_t i = 0; i < result.size(); i++) {
            bzero(&userRaw, sizeof(UserRaw));
            std::strcpy(userRaw.username, result[i].username.c_str());
            std::strcpy(userRaw.ip, result[i].ip.c_str());
            userRaw.port = result[i].port;

            list.push_back(userRaw);
        }
    }

    TCPTram tram(tramExtract.getAction(), tramExtract.getType());
    tram.setUserList(list);
    this->_send(tram, ip, port);
}

template <size_t PACKETSIZE>
void ContactInterpreter<PACKETSIZE>::POST(const TCPTramExtract<PACKETSIZE> &tramExtract, const string &ip, const size_t &port)
{
    const auto &contacts = tramExtract.template getListOf<ContactRaw>();

    for (const ContactRaw &contact : contacts) {
        std::cout << "POST CONTACT: " << contact << std::endl;
        this->_databaseManager.newContact(contact.username, contact.contactName);
    }
    this->GET(tramExtract, ip, port);
}

template <size_t PACKETSIZE>
void ContactInterpreter<PACKETSIZE>::DELETE(const TCPTramExtract<PACKETSIZE> &tramExtract, const string &ip, const size_t &port)
{
    const auto &contacts = tramExtract.template getListOf<ContactRaw>();

    for (const ContactRaw &contact : contacts) {
        std::cout << "DELETE CONTACT: " << contact << std::endl;
        this->_databaseManager.removeContact(contact.username, contact.contactName);
    }

    TCPTram tram(tramExtract.getAction(), tramExtract.getType());
    tram.setContactList(contacts);
    this->_send(tram, ip, port);
}

template <size_t PACKETSIZE> void ContactInterpreter<PACKETSIZE>::_send(const TCPTram &tram, const string &ip, const size_t &port)
{
    if (ip == "" && port == 0)
        this->_network.sendAll(tram.template getBuffer<PACKETSIZE>());
    else
        this->_network.send(tram.template getBuffer<PACKETSIZE>(), ip, port);
}

template class ContactInterpreter<Network::BUFFER_SIZE>;