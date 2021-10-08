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
    std::vector<ContactRaw> list;
    ContactRaw buffer;

    for (const ContactRaw &contact : contacts) {
        std::cout << "GET CONTACT: " << contact << std::endl;
        const std::vector<User> &result = this->_databaseManager.getContacts(contact.username);

        if (result.size() * sizeof(UserRaw) > PACKETSIZE)
            throw std::out_of_range("Response size > PACKETSIZE(" + myToString(PACKETSIZE) + ")");
        for (size_t i = 0; i < result.size(); i++) {
            bzero(&buffer, sizeof(ContactRaw));
            std::strcpy(buffer.username, contact.username);
            std::strcpy(buffer.contactName, result[i].username.c_str());
            list.push_back(buffer);
        }
    }
    TCPTram tram(tramExtract.getAction(), tramExtract.getType());
    tram.setContactList(list);
    this->_send(tram, ip, port);
}

template <size_t PACKETSIZE>
void ContactInterpreter<PACKETSIZE>::POST(const TCPTramExtract<PACKETSIZE> &tramExtract, const string &ip, const size_t &port)
{
    const std::vector<ContactRaw> &contacts = tramExtract.template getListOf<ContactRaw>();

    for (const ContactRaw &contact : contacts) {
        if (std::string(contact.username) == std::string(contact.contactName)) {
            continue; // An user cannot be connected with himself
        }
        std::cout << "POST CONTACT: " << contact << std::endl;
        try {
            this->_databaseManager.newContact(contact.username, contact.contactName);
        } catch (std::exception const &e) {
            TCPTram tram(tramExtract.getAction(), tramExtract.getType());
            tram.setErrorMessage("The user " + std::string(contact.contactName) + " doesn't exist.");
            this->_send(tram, ip, port);
            return; // abort
        }
    }
    TCPTram tram(tramExtract.getAction(), tramExtract.getType());
    tram.setContactList(contacts);
    this->_send(tram, ip, port);
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