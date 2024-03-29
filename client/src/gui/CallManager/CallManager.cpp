/*
** EPITECH PROJECT , 2021
** CallManager
** File description:
** simon
*/

#include "CallManager.hpp"

using namespace GUI;

extern Network::NetworkManager networkManager;

CallManager::CallManager() : _contactList(nullptr)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    _memberGroup = new QGroupBox("Call Members");
    _memberList = new QVBoxLayout;
    _hangUpButton = new QPushButton("Hang Up");

    /// link
    this->setLayout(mainLayout);
    mainLayout->addWidget(_memberGroup);
    mainLayout->addWidget(_hangUpButton);
    _memberGroup->setLayout(_memberList);
    /// config
    _hangUpButton->setStyleSheet("QPushButton { background-color: red; }");
    _memberList->setAlignment(Qt::AlignTop);
    /// Events
    QObject::connect(_hangUpButton, SIGNAL(clicked()), this, SLOT(slotHangUpCall()));
    QObject::connect(&networkManager, &Network::NetworkManager::sigCallSuccess, this, &CallManager::slotSetCallList);
    QObject::connect(&networkManager, &Network::NetworkManager::sigCallUpdate, this, &CallManager::slotSetCallList);
}

CallManager::~CallManager()
{
    delete _hangUpButton;
    delete _memberGroup;
}

void CallManager::setCallMembers(std::vector<QString> const &usernames)
{
    for (QString const &username : usernames) {
        QLabel *item = new QLabel(username);
        _memberList->addWidget(item);
    }
}

void CallManager::removeMember(QString const &username)
{
    for (int i = 0; i < _memberList->count(); i++) {
        QLayoutItem *item = _memberList->itemAt(i);
        if (static_cast<QLabel *>(item->widget())->text() == username) {
            _memberList->removeWidget(item->widget());
        }
    }
}

void CallManager::addMember(QString const &username)
{
    _memberList->addWidget(new QLabel(username));
}

void CallManager::clearMemberList()
{
    while (_memberList->count()) {
        QLayoutItem *item = _memberList->itemAt(0);
        delete item->widget();
    }
}

void CallManager::slotHangUpCall() noexcept
{
    try {
        networkManager.callHangUp();
        this->clearMemberList();
        if (_contactList) {
            this->_contactList->enableCallButtons();
        }
    } catch (std::exception const &e) {
        std::cerr << "Fail to hang up call. " << e.what() << std::endl;
    }
}

void CallManager::slotSetCallList(std::vector<UserRaw> const &list) noexcept
{
    this->clearMemberList();
    for (UserRaw const &user : list) {
        this->addMember(QString(user.username));
    }
}

void CallManager::setContactList(MyContactList &contactList)
{
    this->_contactList = &contactList;
}