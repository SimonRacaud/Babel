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
    MyContactList *contactBox = new MyContactList(DEBUG_LIST); // TODO : inject contacts username
    leftLayout->addWidget(contactBox);

    /// Add Contact
    AddContact *addContactBox = new AddContact;
    leftLayout->addWidget(addContactBox);

    /// Account
    Account *account = new Account;
    rightLayout->addWidget(account);

    /// CallManager manager
    CallManager *callManager = new CallManager;
    rightLayout->addWidget(callManager);
}