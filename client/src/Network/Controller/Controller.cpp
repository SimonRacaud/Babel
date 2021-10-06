/*
** EPITECH PROJECT , 2021
** Controller
** File description:
** simon
*/

#include "Controller.hpp"

using namespace Network;

extern std::unique_ptr<GUI::Window> window;

Controller::Controller(NetworkManager &manager) : _manager(manager)
{
    NetworkWorker *worker = new NetworkWorker;

    worker->moveToThread(&workerThread);
    QObject::connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    QObject::connect(this, &Controller::operate, worker, &NetworkWorker::work);

    QObject::connect(worker, &NetworkWorker::logged, &_manager, &NetworkManager::slotLogged);
    QObject::connect(worker, &NetworkWorker::contactAdded, &_manager, &NetworkManager::slotContactAdded);
    QObject::connect(worker, &NetworkWorker::contactRemoved, &_manager, &NetworkManager::slotContactRemoved);
    QObject::connect(worker, &NetworkWorker::callHandshakeReceived, &_manager, &NetworkManager::slotCallVoiceConnect);
    QObject::connect(worker, &NetworkWorker::userReceived, &_manager, &NetworkManager::slotSendCallMemberList);
    QObject::connect(worker, &NetworkWorker::networkRequestFailed, this, &Controller::showDialogue);
    QObject::connect(worker, &NetworkWorker::contactListReceived, &(window->getContactList()), &GUI::MyContactList::slotSetContactList);
    workerThread.start();
}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

void Controller::showDialogue(QString const &message) const
{
    GUI::DialogueBox::error(message);
}