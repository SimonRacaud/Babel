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

#include "TcpTram.hpp"
#include "Network/TCPTramExtract/TCPTramExtract.hpp"
#include "UserRaw.hpp"
#include "UDPAudio/UDPAudio.hpp"
#include "gui/Dialogue/DialogueBox.hpp"

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
        void newContact(const userNameType &contactName);
        void removeContact(const userNameType &contactName);

        /// Receive requests
        void streamAudio();
        TCPTramExtract<BUFFER_SIZE> receiveFromServer() const;
        std::tuple<TCPTramExtract<BUFFER_SIZE>, UserType> receiveFromClient();

      private:
        void mustBeConnected() const;
        void connectServer();

        void sendCallMemberList(const UserType &target);

      public slots:
        /// Apply network response (called by the worker)
        void slotLogged(UserType const &user);
        void slotContactAdded(ContactRaw const &contact);
        void slotContactRemoved(ContactRaw const &contact);
        /**
         * Called be the worker
         * @param users : new list of members of the current call.
         * @param target : the client that have sent the request (we need his ip)
         */
        void slotCallVoiceConnect(std::vector<UserType> const &users, UserRaw const &target);

        void slotSendCallMemberList(const UserType &target);

      signals:
        void sigUpdateUsername(QString const &username);
        void sigUpdateContacts(QString const &contactUsername);
        void sigRemoveContact(QString const &contactUsername);
        void sigCallSuccess(std::vector<UserType> const &list);

      private:
        bool _logged;
        UDPAudio _audioManager;
        UserType _user;
        bool _callInProgress;
        QString _calledUser;

        std::unique_ptr<AsioClientTCP<Network::BUFFER_SIZE>> _connectionServer;
        std::unique_ptr<AsioServerTCP<Network::BUFFER_SIZE>> _callServer;
        std::unique_ptr<AsioClientTCP<Network::BUFFER_SIZE>> _callClient;
    };
} // namespace Network

#endif