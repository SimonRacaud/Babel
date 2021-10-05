/*
** PERSONAL PROJECT, 2021
** NetworkManager
** File description:
** NetworkManager.hpp
*/

#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <QApplication>
#include <QObject>
#include <memory>
#include "AsioClientTCP.hpp"
#include "AsioConnectionUDP.hpp"
#include "AsioServerTCP.hpp"
#include "INetwork.hpp"
#include "INetworkManager.hpp"

#include "Network/TCPTram/TcpTram.hpp"
#include "UserRaw.hpp"

const std::size_t PACKETSIZE(2048); // todo change that
#define IP_SERVER        "127.0.0.0"
#define PORT_MAIN_SERVER 8081
#define PORT_CALL_SERVER 8082
#define PORT_UDP_EMIT    8088

namespace Network
{
    class NetworkManager : public QObject, public INetworkManager<UserRaw, QString> {
        Q_OBJECT

        using UserType = UserRaw;
        using userNameType = QString;
        using connectionClass = Network::AsioConnectionUDP<PACKETSIZE>;

      public:
        NetworkManager();
        ~NetworkManager();

        void init();

        /// Emit network requests
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

      public slots:
        /// Apply network response
        void slotLogged(UserType const &user);
        void slotContactAdded(ContactRaw const &contact);
        void slotContactRemoved(ContactRaw const &contact);
        void slotCallVoiceConnect(std::vector<UserType> const &users);

      signals:
        void sigUpdateUsername(QString const &username);

      private:
        bool _logged;
        UserType _user;
        // TODO : call members list

        std::unique_ptr<Network::IConnection<PACKETSIZE>> _connectionUDP;
        std::unique_ptr<AsioClientTCP<PACKETSIZE>> _connectionServer;
        std::unique_ptr<AsioServerTCP<PACKETSIZE>> _callServer;
        std::unique_ptr<AsioClientTCP<PACKETSIZE>> _callClient;
    };
} // namespace Network

#endif