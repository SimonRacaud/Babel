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
    : _logged(false), _audioManager(PORT_UDP_RECEIVE), _user({0}), _connectionServer(nullptr), _callServer(nullptr), _callClient(nullptr)
{
}

NetworkManager::~NetworkManager()
{
    if (this->_connectionServer)
        this->_connectionServer.reset();
    this->_callServer.reset();
    this->_callClient.reset();
}

void NetworkManager::init()
{
    if (this->_connectionServer != nullptr) {
        throw std::logic_error("call init once at the beginning");
    }
    this->_connectionServer = std::make_unique<AsioClientTCP<Network::BUFFER_SIZE>>();
    this->_callServer = std::make_unique<AsioServerTCP<Network::BUFFER_SIZE>>(PORT_CALL_SERVER);
    this->_callClient = std::make_unique<AsioClientTCP<Network::BUFFER_SIZE>>();

    this->connectServer();
}

void NetworkManager::callHangUp()
{
    this->mustBeConnected();
    // TODO : GUI - empty call member list
}

bool NetworkManager::isLogged() const
{
    return this->_logged;
}

void NetworkManager::login(const userNameType &username)
{
    /// Update User
    std::strncpy(_user.username, username.toStdString().c_str(), USERNAME_SIZE);
    _user.port = PORT_CALL_SERVER;
    std::strcpy(_user.ip, "0.0.0.0");
    /// Create tram
    TCPTram tram(TramAction::POST, TramType::USER);
    tram.setUserList({ this->_user });
    /// Send to server
    _connectionServer->sendAll(*tram.getBuffer<Network::BUFFER_SIZE>().get());
}

void NetworkManager::getUser(const userNameType &username)
{
    this->mustBeConnected();
    /// Create tram
    UserRaw user;
    std::strncpy(user.username, username.toStdString().c_str(), USERNAME_SIZE);
    std::strcpy(user.ip, "");
    user.port = 0;
    TCPTram tram(TramAction::GET, TramType::USER);
    tram.setUserList({ user });
    /// Send to server
    _connectionServer->sendAll(*tram.getBuffer<Network::BUFFER_SIZE>().get());
}

void NetworkManager::callUser(const userNameType &username)
{
    UserType user;

    this->mustBeConnected();
    /// ask for the user IP to send the handshake
    this->getUser(username);
}

void NetworkManager::voiceConnect(const UserType &user)
{
    this->mustBeConnected();
    // TODO
}

void NetworkManager::newContact(const userNameType &contactName)
{
    this->mustBeConnected();
    /// Create contact
    ContactRaw contact;
    std::strncpy(contact.username, _user.username, USERNAME_SIZE);
    std::strncpy(contact.contactName, contactName.toStdString().c_str(), USERNAME_SIZE);
    /// Create tram
    TCPTram tram(TramAction::POST, TramType::CONTACT);
    tram.setContactList({ contact });
    /// Send
    _connectionServer->sendAll(*tram.getBuffer<Network::BUFFER_SIZE>().get());
}

void NetworkManager::voiceDisconnect(const UserType &user)
{
    this->mustBeConnected();
    // TODO
}

void NetworkManager::removeContact(const userNameType &contactName)
{
    this->mustBeConnected();
    /// Create contact
    ContactRaw contact;
    std::strncpy(contact.username, _user.username, USERNAME_SIZE);
    std::strncpy(contact.contactName, contactName.toStdString().c_str(), USERNAME_SIZE);
    /// Create tram
    TCPTram tram(TramAction::DELETE, TramType::CONTACT);
    tram.setContactList({ contact });
    /// Send
    _connectionServer->sendAll(*tram.getBuffer<Network::BUFFER_SIZE>().get());
}

void NetworkManager::mustBeConnected() const
{
    if (!this->_logged)
        throw std::invalid_argument("User must be connected");
}

void NetworkManager::connectServer()
{
    if (!this->_connectionServer) {
        this->_connectionServer->connect(IP_SERVER, PORT_MAIN_SERVER);
    }
}

void NetworkManager::slotLogged(UserType const &user)
{
    _user = user;
    this->_logged = true;
    emit sigUpdateUsername(QString(user.username));
}

void NetworkManager::slotContactAdded(ContactRaw const &contact)
{
    emit sigUpdateContacts(QString(contact.contactName));
}

void NetworkManager::slotContactRemoved(ContactRaw const &contact)
{
    emit sigRemoveContact(QString(contact.contactName));
}

void NetworkManager::slotSendCallMemberList(const UserType &target)
{
    this->mustBeConnected();
    // TODO : get call UserRaw members (with _audioManager)
    /// Create tram
    TCPTram tram(TramAction::POST, TramType::USER);
    tram.setUserList({ /* TODO */ });
    ///     Send contact list
    this->_callClient->connect(target.ip, PORT_CALL_SERVER);
    this->_callClient->send(*tram.getBuffer<Network::BUFFER_SIZE>().get(), target.ip, PORT_CALL_SERVER);
}

void NetworkManager::slotCallVoiceConnect(std::vector<UserType> const &users, UserRaw const &target)
{

    // TODO : update call member list => UDP (with _audioManager)

}
