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
#include "UDPAudio/UDPAudio.hpp"

#define IP_SERVER        "127.0.0.0"
#define PORT_MAIN_SERVER 8081
#define PORT_CALL_SERVER 8082
#define PORT_UDP_RECEIVE 8088

namespace Network
{
    class NetworkManager : public QObject, public INetworkManager<UserRaw, QString> {
        Q_OBJECT

        using UserType = UserRaw;
        using userNameType = QString;
        using connectionClass = Network::AsioConnectionUDP<Network::BUFFER_SIZE>;

      public:
        NetworkManager();
        ~NetworkManager();

        void init();

        /// Emit network requests
        void callHangUp();
        bool isLogged() const;
        void login(const userNameType &);
        void getUser(const userNameType &username);
        void callUser(const userNameType &username);
        void voiceConnect(const UserType &);
        void newContact(const userNameType &contactName);
        void voiceDisconnect(const UserType &);
        void removeContact(const userNameType &contactName);

      private:
        void mustBeConnected() const;
        void connectServer();

      public slots:
        /// Apply network response
        void slotLogged(UserType const &user);
        void slotContactAdded(ContactRaw const &contact);
        void slotContactRemoved(ContactRaw const &contact);
        /**
         *
         * @param users : new list of members of the current call.
         * @param target : the client that have sent the request (we need his ip)
         */
        void slotCallVoiceConnect(std::vector<UserType> const &users, UserRaw const &target);

        void slotSendCallMemberList(const UserType &target);

      signals:
        void sigUpdateUsername(QString const &username);
        void sigUpdateContacts(QString const &contactUsername);
        void sigRemoveContact(QString const &contactUsername);
        void sigCallSuccess(QString const &username);

      private:
        bool _logged;
        UDPAudio _audioManager;
        UserType _user;

        std::unique_ptr<AsioClientTCP<Network::BUFFER_SIZE>> _connectionServer;
        std::unique_ptr<AsioServerTCP<Network::BUFFER_SIZE>> _callServer;
        std::unique_ptr<AsioClientTCP<Network::BUFFER_SIZE>> _callClient;
    };
} // namespace Network

#endif