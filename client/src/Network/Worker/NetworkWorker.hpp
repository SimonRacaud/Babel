/*
** EPITECH PROJECT , 2021
** Worker
** File description:
** simon
*/

#ifndef NET_WORKER_HPP
#define NET_WORKER_HPP

#include <QWidget>
#include <QThread>
#include <vector>
#include "UserRaw.hpp"
#include "ContactRaw.hpp"
#include "NetworkManager/NetworkManager.hpp"

namespace Network
{
    class NetworkWorker : public QThread {
        Q_OBJECT
      public:
        NetworkWorker(QObject *parent = nullptr);
        virtual ~NetworkWorker() = default;

      public:
        void run() override;

      private:
        void processServerCommunication();
        void processClientCommunication();

      signals:
        void contactAdded(ContactRaw const &contact);
        void contactRemoved(ContactRaw const &contact);
        void logged(UserRaw const &user);
        void userReceived(UserRaw const &user);
        void callHandshakeReceived(std::vector<UserRaw> const &users, UserRaw const &target);
        void networkRequestFailed(QString const &message);
        void contactListReceived(std::vector<ContactRaw> const &contacts);
    };
}

#endif // NET_WORKER_HPP
