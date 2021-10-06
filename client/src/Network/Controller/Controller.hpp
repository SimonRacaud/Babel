/*
** EPITECH PROJECT , 2021
** Controller
** File description:
** simon
*/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QThread>

#include "NetworkManager/NetworkManager.hpp"
#include "Network/Worker/NetworkWorker.hpp"
#include "gui/Dialogue/DialogueBox.hpp"

namespace Network
{
    class Controller : public QObject {
        Q_OBJECT
        QThread workerThread;

      public:
        Controller(NetworkManager &manager);
        virtual ~Controller();
      signals:
        void operate();

      private:
        void showDialogue(QString const &message) const;

      private:
        NetworkManager &_manager;
    };
}

#endif // CONTROLLER_HPP
