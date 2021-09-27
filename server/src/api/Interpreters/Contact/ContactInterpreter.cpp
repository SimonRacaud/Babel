/*
 * EPITECH PROJECT, 2021
 * Contact
 * File description:
 * ContactInterpreter.cpp - Created: 27/09/2021
 */

#include "ContactInterpreter.hpp"
#include "Contact.hpp"

using namespace network;

ContactInterpreter::ContactInterpreter(DatabaseManager &databaseManager) : _databaseManager(databaseManager)
{
}

void ContactInterpreter::GET(const TramTCP &tram)
{
    const ContactRaw contact = static_cast<ContactRaw>(tram.list);

    this->_databaseManager.getContacts(contact.username);
}

void ContactInterpreter::POST(const TramTCP &tram)
{
    const ContactRaw contact = static_cast<ContactRaw>(tram.list);

    this->_databaseManager.newContact(contact.username, contact.contactName);
}

void ContactInterpreter::DELETE(const TramTCP &tram)
{
    const ContactRaw contact = static_cast<ContactRaw>(tram.list);

    this->_databaseManager.removeContact(contact.username, contact.contactName);
}