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
#include "AsioClientTCP.hpp"
#include "AsioServerTCP.hpp"
#include "INetwork.hpp"
#include "INetworkManager.hpp"

#include "UserRaw.hpp"
#include "Network/TCPTram/TcpTram.hpp"

const std::size_t PACKETSIZE(2048); // todo change that
#define IP_SERVER "127.0.0.0"
#define PORT_SERVER 8081
#define PORT_CALL_SERVER 8082

namespace Network
{
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
        void connectServer();

      private:
        bool _logged;
        UserType _user;
        // TODO : call members list

        std::unique_ptr<Network::IConnection<PACKETSIZE>> _connectionUDP;
        std::unique_ptr<AsioClientTCP<PACKETSIZE>> _connectionServer;
        std::unique_ptr<AsioServerTCP<PACKETSIZE>> _callServer;
        std::unique_ptr<AsioClientTCP<PACKETSIZE>> _callClient;
    };
}

#endif