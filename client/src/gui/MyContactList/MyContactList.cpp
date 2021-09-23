/*
** EPITECH PROJECT , 2021
** GroupBoxMyContact
** File description:
** simon
*/

#include "MyContactList.hpp"

using namespace GUI;

MyContactList::MyContactList(std::vector<QString> const &contactNameList) : QGroupBox("My Contacts")
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *container = new QWidget;

    mainLayout->addWidget(scrollArea);
    this->setLayout(mainLayout);

    _contactList = new QVBoxLayout;
    _contactList->setAlignment(Qt::AlignTop);
    scrollArea->setWidget(container);
    scrollArea->setWidgetResizable(true);
    container->setLayout(_contactList);

    for (QString const &username : contactNameList) {
        _contacts.push_back(new Contact(*_contactList, username));
    }
}

MyContactList::~MyContactList()
{
    for (Contact *contact : _contacts) {
        delete contact;
    }
}

void MyContactList::addContact(QString const& username)
{
    _contacts.push_back(new Contact(*_contactList, username));
}

void MyContactList::enableCallButtons()
{
    for (Contact *contact : _contacts) {
        contact->enableCall();
    }
}

void MyContactList::removeContact(QString const &username)
{
    // TODO
}