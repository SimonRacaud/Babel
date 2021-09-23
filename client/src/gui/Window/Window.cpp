/*
** EPITECH PROJECT , 2021
** Window
** File description:
** simon
*/

#include "Window.hpp"

using namespace GUI;

const std::vector<QString> DEBUG_LIST = {
    "USER A", "USER B", "USER C"
};

Window::Window()
{
    QMdiArea *centerArea = new QMdiArea;
    QHBoxLayout *rootLayout = new QHBoxLayout(centerArea);
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    /// Config Window
    this->setWindowTitle("Babel");
    this->setStyleSheet("background-color: white;");
    this->setCentralWidget(centerArea);
    rootLayout->addLayout(leftLayout);
    rootLayout->addLayout(rightLayout);
    /// CallManager
    _callManager = new CallManager();
    /// Contacts
    _contactBox = new MyContactList(*_callManager, DEBUG_LIST); // TODO : inject contacts username
    /// Add Contact
    _addContactBox = new AddContact((*_contactBox));
    /// Account
    _account = new Account;
    /// Call Manager
    this->_callManager->setContactList(*_contactBox);
    /// Options
    //_winOption = new Options;

    /// Links
    leftLayout->addWidget(_contactBox);
    leftLayout->addWidget(_addContactBox);
    rightLayout->addWidget(_account);
    rightLayout->addWidget(_callManager);
}

void Window::showOptions()
{
    //_winOption->show();
    this->hide();
}