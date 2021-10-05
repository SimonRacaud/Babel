/*
** EPITECH PROJECT , 2021
** Worker
** File description:
** simon
*/

#ifndef NET_WORKER_HPP
#define NET_WORKER_HPP

#include <QWidget>
#include <QObject>
#include <vector>
#include "UserRaw.hpp"
#include "ContactRaw.hpp"

namespace Network
{
    class NetworkWorker : public QObject {
        Q_OBJECT
      public:
        NetworkWorker();
        virtual ~NetworkWorker() = default;

      public slots:
        void work();

      signals:
        void contactAdded(ContactRaw const &contact);
        void contactRemoved(ContactRaw const &contact);
        void logged(UserRaw const &user);
        void callVoiceConnect(std::vector<UserRaw> const &users);
        void networkRequestFailed(QString const &message);
    };
}

#endif // NET_WORKER_HPP
