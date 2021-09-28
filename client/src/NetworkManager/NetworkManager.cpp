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
    if (this->_connection)
        this->_connection.reset();
}

void NetworkManager::callHangUp()
{
    this->mustBeConnected();
    this->_connection.reset();
    this->_connection = nullptr;
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

void NetworkManager::login(const userNameType &username)
{
    // TODO: Need srv API
    this->_logged = true;
    this->_user = this->getUser(username);
}

NetworkManager::UserType NetworkManager::getUser(const userNameType &)
{
    this->mustBeConnected();
    // TODO: Need srv API
    return NetworkManager::UserType();
}

void NetworkManager::callUser(const userNameType &username)
{
    UserType user;

    this->mustBeConnected();
    if (!this->_connection)
        this->_connection = std::make_unique<connectionClass>();
    user = this->getUser(username);
    this->voiceConnect(user);
}

void NetworkManager::voiceConnect(const UserType &user)
{
    this->mustBeConnected();
    if (!this->_connection)
        throw std::invalid_argument("User must be in call");
    this->_connection->connect(user.ip, user.port);
}

void NetworkManager::newContact(const userNameType &)
{
    this->mustBeConnected();
    // TODO: Need srv API
}

void NetworkManager::voiceDisconnect(const UserType &user)
{
    this->mustBeConnected();
    if (!this->_connection)
        throw std::invalid_argument("User must be in call");
    this->_connection->disconnect(user.ip, user.port);
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