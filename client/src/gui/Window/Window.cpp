/*
** EPITECH PROJECT , 2021
** Window
** File description:
** simon
*/

#include "Window.hpp"

using namespace GUI;

Window::Window(QApplication &app) : _app(app)
{
    QMdiArea *centerArea = new QMdiArea;
    QHBoxLayout *rootLayout = new QHBoxLayout(centerArea);
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;

    /// Menu bar
    QMenu *menuFile = this->menuBar()->addMenu("&View");
    QAction *actionOption = new QAction("&Options", this);
    menuFile->addAction(actionOption);

    /// Config Window
    this->setWindowTitle("Babel");
    this->setStyleSheet("background-color: white;");
    this->setCentralWidget(centerArea);
    rootLayout->addLayout(leftLayout);
    rootLayout->addLayout(rightLayout);
    /// CallManager
    _callManager = new CallManager();
    /// Contacts
    _contactBox = new MyContactList(*_callManager);
    /// Add Contact
    _addContactBox = new AddContact((*_contactBox));
    /// Account
    _account = new Account;
    /// Call Manager
    this->_callManager->setContactList(*_contactBox);
    /// Options
    _winOption = new Options((*this), _ioDevices);

    /// Links
    leftLayout->addWidget(_contactBox);
    leftLayout->addWidget(_addContactBox);
    rightLayout->addWidget(_account);
    rightLayout->addWidget(_callManager);
    /// Events
    QObject::connect(actionOption, SIGNAL(triggered()), this, SLOT(showOptions()));
}

void Window::showOptions()
{
    _winOption->show();
    this->hide();
}

void Window::hideOptions()
{
    _winOption->hide();
    this->show();
}

MyContactList &Window::getContactList()
{
    return *_contactBox;
}