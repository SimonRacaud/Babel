/*
** PERSONAL PROJECT, 2021
** NetworkManager
** File description:
** NetworkManager.cpp
*/

#include "NetworkManager.hpp"
#include <stdexcept>

using namespace Network;

NetworkManager::NetworkManager()
    : _logged(false), _user({0}), _connectionUDP(nullptr),
      _connectionServer(std::make_unique<AsioClientTCP<PACKETSIZE>>()),
      _callServer(std::make_unique<AsioServerTCP<PACKETSIZE>>(PORT_CALL_SERVER)),
      _callClient(std::make_unique<AsioClientTCP<PACKETSIZE>>())
{
    this->connectServer();
}

NetworkManager::~NetworkManager()
{
    if (this->_connectionUDP)
        this->_connectionUDP.reset();
    if (this->_connectionServer)
        this->_connectionServer.reset();
    this->_callServer.reset();
    this->_callClient.reset();
}

void NetworkManager::callHangUp()
{
    this->mustBeConnected();
    this->_connectionUDP.reset();
    // this->_connectionUDP = nullptr; // needed ?
    // TODO : GUI - empty call member list
}

bool NetworkManager::isLogged() const
{
    return this->_logged;
}

void NetworkManager::sendCallMemberList()
{
    this->mustBeConnected();
    // TODO : get call members
    // TODO : send list on _connection
}

void NetworkManager::login(const userNameType &username)
{
    /// Update User
    std::strncpy(_user.username, username.toStdString().c_str(), USERNAME_SIZE);
    _user.port = PORT_SERVER;
    /// Create tram
    TCPTram tram(TramAction::POST, TramType::USER);
    tram.setUserList({ this->_user });
    /// Send to server
    _connectionServer->sendAll(*tram.getBuffer<PACKETSIZE>().get());
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
    if (!this->_connectionUDP)
        this->_connectionUDP = std::make_unique<connectionClass>(8080 /*todo change this*/);
    user = this->getUser(username);
    this->voiceConnect(user);
}

void NetworkManager::voiceConnect(const UserType &user)
{
    this->mustBeConnected();
    if (!this->_connectionUDP)
        throw std::invalid_argument("User must be in call");
    this->_connectionUDP->connect(user.ip, user.port);
}

void NetworkManager::newContact(const userNameType &)
{
    this->mustBeConnected();
    // TODO: Need srv API
}

void NetworkManager::voiceDisconnect(const UserType &user)
{
    this->mustBeConnected();
    if (!this->_connectionUDP)
        throw std::invalid_argument("User must be in call");
    this->_connectionUDP->disconnect(user.ip, user.port);
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

void NetworkManager::connectServer()
{
    if (!this->_connectionServer) {
        this->_connectionServer->connect(IP_SERVER, PORT_SERVER);
    }
}