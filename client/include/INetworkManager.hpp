/*
** PERSONAL PROJECT, 2021
** INetworkManager
** File description:
** INetworkManager.hpp
*/

#ifndef INETWORKMANAGER_HPP
#define INETWORKMANAGER_HPP

namespace Network
{
    template <typename UserType, typename userNameType>
    class INetworkManager {

      public:
        virtual ~INetworkManager() = default;
        virtual void callHangUp() = 0;
        virtual bool isLogged() const = 0;
        virtual void login(const userNameType &) = 0;
        virtual void getUser(const userNameType &) = 0;
        virtual void callUser(const userNameType &) = 0;
        virtual void voiceConnect(const UserType &) = 0;
        virtual void newContact(const userNameType &) = 0;
        virtual void voiceDisconnect(const UserType &) = 0;
        virtual void removeContact(const userNameType &) = 0;
    };
}

#endif