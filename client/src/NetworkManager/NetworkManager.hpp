/*
** PERSONAL PROJECT, 2021
** NetworkManager
** File description:
** NetworkManager.hpp
*/

#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <QApplication>
#include "INetworkManager.hpp"

class NetworkManager : public INetworkManager<int, QString>
{
    using UserType = int;
    using userNameType = QString;
    public:
        NetworkManager();
        ~NetworkManager();
        void callHangUp();
        void isLogged() const;
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
};

#endif