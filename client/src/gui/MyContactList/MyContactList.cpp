/*
** EPITECH PROJECT , 2021
** GroupBoxMyContact
** File description:
** simon
*/

#include "MyContactList.hpp"

using namespace GUI;

MyContactList::MyContactList(
    ICallManager &callManager, std::vector<QString> const &contactNameList)
    : QGroupBox("My Contacts"), _callManager(callManager)
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
        _contacts.push_back(
            new Contact(*_contactList, username, callManager, *this));
    }
}

MyContactList::~MyContactList()
{
    for (Contact *contact : _contacts) {
        delete contact;
    }
}

void MyContactList::addContact(QString const &username)
{
    _contacts.push_back(
        new Contact(*_contactList, username, _callManager, *this));
}

void MyContactList::enableCallButtons()
{
    for (Contact *contact : _contacts) {
        contact->enableCall();
    }
}

void MyContactList::removeContact(IContact &contact)
{
    auto contactIt = std::find(_contacts.begin(), _contacts.end(), &contact);

    if (contactIt != _contacts.end()) {
        _contactList->removeWidget(contact.getTopWidget());
        delete *contactIt;
        _contacts.erase(contactIt);
    }
}

bool MyContactList::exist(QString const &contactName) const
{
    for (Contact *contact : _contacts) {
        if (contact->getUsername() == contactName) {
            return true;
        }
    }
    return false;
}

void MyContactList::slotSetContactList(std::vector<ContactRaw> const &contacts)
{
    for (ContactRaw const &contact : contacts) {
        this->addContact(QString(contact.contactName));
    }
}