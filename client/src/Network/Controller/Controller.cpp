/*
** EPITECH PROJECT , 2021
** Controller
** File description:
** simon
*/

#include "Controller.hpp"

using namespace Network;

extern std::unique_ptr<GUI::Window> window;

Controller::Controller(NetworkManager &manager) : workerThread(new NetworkWorker), _manager(manager)
{
    std::cerr << "Instance created" << std::endl;
    workerThread = new NetworkWorker(this);

    /// register types
    qRegisterMetaType<UserRaw>("UserRaw");
    qRegisterMetaType<ContactRaw>("ContactRaw");
    /// Events
    QObject::connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);
    QObject::connect(workerThread, &NetworkWorker::logged, &_manager, &NetworkManager::slotLogged);
    QObject::connect(workerThread, &NetworkWorker::contactAdded, &_manager, &NetworkManager::slotContactAdded);
    QObject::connect(workerThread, &NetworkWorker::contactRemoved, &_manager, &NetworkManager::slotContactRemoved);
    QObject::connect(workerThread, &NetworkWorker::callHandshakeReceived, &_manager, &NetworkManager::slotCallVoiceConnect);
    QObject::connect(workerThread, &NetworkWorker::userReceived, &_manager, &NetworkManager::slotSendCallMemberList);
    QObject::connect(workerThread, &NetworkWorker::networkRequestFailed, this, &Controller::showDialogue);
    QObject::connect(workerThread, &NetworkWorker::contactListReceived, &(window->getContactList()), &GUI::MyContactList::slotSetContactList);
    workerThread->start();
}

Controller::~Controller()
{
    workerThread->requestInterruption();
    workerThread->quit();
    workerThread->wait();
}

void Controller::showDialogue(QString const &message) const
{
    GUI::DialogueBox::error(message);
}