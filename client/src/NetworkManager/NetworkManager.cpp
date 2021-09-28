/*
** PERSONAL PROJECT, 2021
** NetworkManager
** File description:
** NetworkManager.cpp
*/

#include <stdexcept>
#include "NetworkManager.hpp"

NetworkManager::NetworkManager() : _logged(false), _user({0}), _connection(nullptr)
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::callHangUp()
{
    this->mustBeConnected();
    // TODO: NOW
}

bool NetworkManager::isLogged() const
{
    return this->_logged;
}

void NetworkManager::sendCallMemberList()
{
    this->mustBeConnected();
    // TODO: Need srv API
}

void NetworkManager::login(const userNameType &)
{
    // TODO: Need srv API
    this->_user = {0}; // API request
    this->_connection = std::make_unique<connectionClass>();
    this->_logged = true;
}

NetworkManager::UserType NetworkManager::getUser(const userNameType &)
{
    this->mustBeConnected();
    // TODO: Need srv API
    return NetworkManager::UserType();
}

void NetworkManager::callUser(const userNameType &)
{
    this->mustBeConnected();
    // TODO: Need srv API
}

void NetworkManager::voiceConnect(const UserType &)
{
    this->mustBeConnected();
    // TODO: NOW
}

void NetworkManager::newContact(const userNameType &)
{
    this->mustBeConnected();
    // TODO: Need srv API
}

void NetworkManager::voiceDisconnect(const UserType &)
{
    this->mustBeConnected();
    // TODO: NOW
}

void NetworkManager::removeContact(const userNameType &)
{
    this->mustBeConnected();
    // TODO: Need srv API
}

void NetworkManager::mustBeConnected() const
{
    if (!this->_logged)
        throw std::invalid_argument("User must be connected");
}