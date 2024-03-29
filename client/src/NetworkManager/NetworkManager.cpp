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
    : _logged(false), _audioManager(PORT_UDP_RECEIVE), _user({0}), _callInProgress(false), _calledUser(), _connectionServer(nullptr),
      _callServer(nullptr), _callClient(nullptr)
{
}

NetworkManager::~NetworkManager()
{
    /// Hang up
    try {
        if (this->_logged) {
            this->callHangUp();
        }
    } catch (...) {}
    ///
    if (this->_connectionServer) {
        this->_connectionServer->stopRunAsync();
        this->_connectionServer.reset();
    }
    this->_callServer->stopRunAsync();
    this->_callServer.reset();
    this->_callClient->stopRunAsync();
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
    this->_connectionServer->runAsync();
    this->_callServer->runAsync();
    this->_callClient->runAsync();
}

void NetworkManager::callHangUp()
{
    this->mustBeConnected();
    std::vector<UserType> connections = _audioManager.getConnections();
    try {
        if (!connections.empty()) {
            this->_audioManager.closeConnections();
        }
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::callHangUp : request failed. " << e.what() << std::endl;
    }
    /// Send end call request
    for (UserType const &user : connections) {
        this->sendHangupRequest(user);
    }
}

void NetworkManager::sendHangupRequest(const UserType &user)
{
    TCPTram tram(TramAction::POST, TramType::STOP);

    try {
        this->_callClient->connect(user.ip, PORT_CALL_SERVER);
        this->_callClient->send(tram.getBuffer<Network::BUFFER_SIZE>(), user.ip, PORT_CALL_SERVER);
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::sendHangupRequest : request failed. " << e.what() << std::endl;
    }
}

void NetworkManager::slotRemoveCallMember(const UserType &user)
{
    try {
        this->mustBeConnected();
    } catch (std::exception const &) {
        return;
    }
    std::vector<UserType> connections = _audioManager.getConnections();
    std::vector<UserType> newConnections;

    for (UserType const &elem : connections) {
        if (std::strcmp(elem.ip, user.ip) != 0) {
            newConnections.push_back(elem);
        }
    }
    this->_audioManager.updateConnections(newConnections);
    emit this->sigCallUpdate(newConnections); // update gui
}

bool NetworkManager::isLogged() const
{
    return this->_logged;
}

void NetworkManager::login(const userNameType &username)
{
    /// Update User
    std::strncpy(_user.username, username.toStdString().c_str(), USERNAME_SIZE);
    _user.port = Network::PORT_CALL_SERVER;
    /*
    ** The client don't know is own IP.
    ** So, at this step it's impossible to get his IP
    ** Thus it's a conceptio's error. So we just send basic string
    */
    std::strcpy(_user.ip, "0.0.0.0");
    /// Create tram
    TCPTram tram(TramAction::POST, TramType::USER);
    tram.setUserList({this->_user});
    /// Send to server
    try {
        _connectionServer->sendAll(tram.getBuffer<Network::BUFFER_SIZE>());
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::login : request failed. " << e.what() << std::endl;
    }
}

void NetworkManager::streamAudio()
{
    try {
        this->_audioManager.streamAudio();
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::streamAudio : request failed. " << e.what() << std::endl;
    }
}

TCPTramExtract<BUFFER_SIZE> NetworkManager::receiveFromServer() const
{
    auto [data, size, ip, port] = this->_connectionServer->receiveAny();
    TCPTramExtract tram(data);

    if (size != BUFFER_SIZE) {
        throw std::invalid_argument("NetworkManager::receiveFromServer : invalid tram size");
    }
    std::cerr << "received data from server : " << std::endl;
    return tram;
}

std::tuple<TCPTramExtract<BUFFER_SIZE>, UserRaw> NetworkManager::receiveFromClient()
{
    auto [data, size, ip, port] = this->_callServer->receiveAny();
    TCPTramExtract tram(data);
    UserRaw user;

    if (size != BUFFER_SIZE) {
        throw std::invalid_argument("NetworkManager::receiveFromServer : invalid tram size");
    }
    strcpy(user.username, "");
    strncpy(user.ip, (ip.c_str()), USERNAME_SIZE);
    user.port = port;
    return std::make_tuple(tram, user);
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
    tram.setUserList({user});
    /// Send to server
    std::cerr << "call : GET USER" << std::endl;
    try {
        _connectionServer->sendAll(tram.getBuffer<Network::BUFFER_SIZE>());
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::getUser : request failed. " << e.what() << std::endl;
    }
}

void NetworkManager::callUser(const userNameType &username)
{
    this->mustBeConnected();
    /// ask for the user IP to send the handshake
    try {
        this->getUser(username);
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::callUser : request failed. " << e.what() << std::endl;
    }
    this->_callInProgress = true;
    this->_calledUser = username;
}

void NetworkManager::newContact(const userNameType &contactName)
{
    this->mustBeConnected();
    if (contactName == QString(_user.username)) {
        GUI::DialogueBox::error("An user cannot add himself.");
        return;
    }
    /// Create contact
    ContactRaw contact;
    std::strncpy(contact.username, _user.username, USERNAME_SIZE);
    std::strncpy(contact.contactName, contactName.toStdString().c_str(), USERNAME_SIZE);
    /// Create tram
    TCPTram tram(TramAction::POST, TramType::CONTACT);
    tram.setContactList({contact});
    /// Send
    try {
        _connectionServer->sendAll(tram.getBuffer<Network::BUFFER_SIZE>());
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::newContact : request failed. " << e.what() << std::endl;
    }
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
    tram.setContactList({contact});
    /// Send
    try {
        _connectionServer->sendAll(tram.getBuffer<Network::BUFFER_SIZE>());
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::removeContact : request failed. " << e.what() << std::endl;
    }
}

void NetworkManager::mustBeConnected() const
{
    if (!this->_logged) {
        GUI::DialogueBox::error("You aren't logged in.");
        throw std::invalid_argument("User must be connected");
    }
}

void NetworkManager::connectServer()
{
    while (!this->_connectionServer->isConnected(IP_SERVER, PORT_MAIN_SERVER))
        this->_connectionServer->connect(IP_SERVER, PORT_MAIN_SERVER);
}

void NetworkManager::slotLogged(UserType const &user)
{
    _user = user;
    this->_logged = true;
    emit sigUpdateUsername(QString(user.username));
    /// Ask for user contacts
    TCPTram tram(TramAction::GET, TramType::CONTACT);
    ContactRaw me{"", ""};
    std::strncpy(me.username, user.username, USERNAME_SIZE);
    tram.setContactList({me});
    try {
        _connectionServer->sendAll(tram.getBuffer<Network::BUFFER_SIZE>());
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::slotLogged : request failed. " << e.what() << std::endl;
    }
}

void NetworkManager::slotContactAdded(ContactRaw const &contact)
{
    emit sigUpdateContacts(QString(contact.contactName));
}

void NetworkManager::slotContactRemoved(ContactRaw const &contact)
{
    emit sigRemoveContact(QString(contact.contactName));
}

void NetworkManager::sendCallMemberList(std::vector<UserRaw> &list, const UserType &target)
{
    if (_audioManager.getConnections().size() >= MAX_MEMBER_CALL) {
        return; // abort
    }
    UserRaw me = {0};

    std::strcpy(me.username, _user.username);
    std::strcpy(me.ip, "");
    list.push_back(me);
    /// Create tram
    TCPTram tram(TramAction::POST, TramType::USER);
    tram.setUserList(list);
    ///     Send contact list
    std::cerr << "call : SEND CALL MEMBER LIST." << std::endl;
    try {
        this->_callClient->connect(target.ip, PORT_CALL_SERVER);
        this->_callClient->send(tram.getBuffer<Network::BUFFER_SIZE>(), target.ip, PORT_CALL_SERVER);
    } catch (std::exception const &e) {
        std::cerr << "NetworkManager::sendCallMemberList : request failed. " << e.what() << std::endl;
    }
}

void NetworkManager::slotSendCallMemberList(const UserType &target)
{
    this->mustBeConnected();
    /// Get current call members
    std::vector<UserRaw> connections = _audioManager.getConnections();

    /// Check if the target is not already called
    for (UserRaw const &user : connections) {
        if (std::strcmp(user.username, target.username) == 0) {
            GUI::DialogueBox::error("The user is already in the call !");
            return; // abort
        }
    }
    ///
    this->sendCallMemberList(connections, target);
}

void NetworkManager::slotCallVoiceConnect(std::vector<UserType> const &users, UserRaw const &target)
{
    try {
        this->mustBeConnected();
    } catch (std::exception const &) {
        return;
    }
    std::vector<UserType> list = users;
    UserType &me = _user;
    auto itSender = std::find_if(list.begin(), list.end(), [target](UserRaw const &user) {
        return std::string(user.ip) == "";
    });

    if (itSender == list.end()) {
        throw std::invalid_argument("NetworkManager::slotCallVoiceConnect : sender's username not found");
    }
    std::strcpy(itSender->ip, target.ip);
    itSender->port = target.port;
    std::cerr << "call : VOICE CONNECT." << std::endl;
    std::vector<UserType> usersWithoutMe;
    for (UserType const &user : list) {
        if (strcmp(user.username, me.username) != 0) {
            usersWithoutMe.push_back(user);
        }
    }
    if (this->_callInProgress == false) { // I'm replying to a call request.
        if (GUI::DialogueBox::question("Call in coming", "Accept " + QString(itSender->username) + " call connection ?")) {
            std::cerr << "call : SEND REPLY CALL MEMBER LIST." << std::endl;
            this->sendCallMemberList(list, target);
            this->_audioManager.updateConnections(usersWithoutMe);
        } else {
            return; // call rejected
        }
    } else {
        this->_audioManager.updateConnections(usersWithoutMe);
        this->_callInProgress = false;   // I already have sent my call member list.
    }
    emit this->sigCallSuccess(usersWithoutMe); // update gui
}
