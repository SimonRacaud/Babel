/*
** PERSONAL PROJECT, 2021
** NetworkManager
** File description:
** NetworkManager.hpp
*/

#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <QApplication>
#include <memory>
#include "AsioConnectionUDP.hpp"
#include "INetwork.hpp"
#include "INetworkManager.hpp"
#include "UserRaw.hpp"

const std::size_t PACKETSIZE(124); // todo change that

class NetworkManager : public INetworkManager<UserRaw, QString> {
    using UserType = UserRaw;
    using userNameType = QString;
    using connectionClass = Network::AsioConnectionUDP<PACKETSIZE>;

  public:
    NetworkManager();
    ~NetworkManager();
    void callHangUp();
    bool isLogged() const;
    void sendCallMemberList();
    void login(const userNameType &);
    UserType getUser(const userNameType &);
    void callUser(const userNameType &);
    void voiceConnect(const UserType &);
    void newContact(const userNameType &);
    void voiceDisconnect(const UserType &);
    void removeContact(const userNameType &);

  private:
    void mustBeConnected() const;

  private:
    bool _logged;
    UserType _user;
    std::unique_ptr<Network::IConnection<PACKETSIZE>> _connection;
};

#endif