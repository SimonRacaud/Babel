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
#include "INetworkManager.hpp"
#include "UserRaw.hpp"

class IConnection {
  protected:
    using unknown = int;

  public:
    virtual void connect(std::string ip, uint port) = 0;
    virtual void disconnect(std::string ip, uint port) = 0;
    virtual void disconnectAll() = 0;
    virtual std::pair<std::pair<std::array<char, 0>, unknown>, unknown> receiveAny() = 0;
    virtual std::array<char, 0> receive(std::string ip, uint port) = 0;
    virtual void sendAll(std::array<char, 0> buff) = 0;
    virtual void send(std::array<char, 0> buff, std::string ip, uint port) = 0;
    virtual bool isConnected(std::string ip, uint port) = 0;
};

class connection : public IConnection {
  public:
    connection() = default;
    ~connection() = default;
    void connect(std::string, uint)
    {
    }
    void disconnect(std::string, uint)
    {
    }
    void disconnectAll()
    {
    }
    std::pair<std::pair<std::array<char, 0>, unknown>, unknown> receiveAny()
    {
        return std::pair<std::pair<std::array<char, 0>, unknown>, unknown>();
    }
    std::array<char, 0> receive(std::string, uint)
    {
        return std::array<char, 0>();
    }
    void sendAll(std::array<char, 0>)
    {
    }
    void send(std::array<char, 0>, std::string, uint)
    {
    }
    bool isConnected(std::string, uint)
    {
        return true;
    }
};

class NetworkManager : public INetworkManager<UserRaw, QString> {
    using UserType = UserRaw;
    using userNameType = QString;
    using connectionClass = connection;

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
    std::unique_ptr<IConnection> _connection;
};

#endif