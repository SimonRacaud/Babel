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
    /// Contacts
    _contactBox = new MyContactList(DEBUG_LIST); // TODO : inject contacts username
    leftLayout->addWidget(_contactBox);
    /// Add Contact
    _addContactBox = new AddContact((*_contactBox));
    leftLayout->addWidget(_addContactBox);
    /// Account
    _account = new Account;
    rightLayout->addWidget(_account);
    /// CallManager manager
    _callManager = new CallManager((*_contactBox));
    rightLayout->addWidget(_callManager);
    /// Options
    //_winOption = new Options;
}

void Window::showOptions()
{
    //_winOption->show();
    this->hide();
}