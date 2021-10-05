/*
** EPITECH PROJECT , 2021
** GroupBoxMyContact
** File description:
** simon
*/

#ifndef MYCONTACTLIST_HPP
#define MYCONTACTLIST_HPP

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>
#include <vector>
#include <algorithm>

#include "ICallManager.hpp"
#include "IMyContactList.hpp"
#include "IContact.hpp"
#include "Contact/Contact.hpp"

namespace GUI
{
    class MyContactList : public QGroupBox, public IMyContactList {
        Q_OBJECT

      public:
        MyContactList(ICallManager &callManager, std::vector<QString> const &contactNameList = {});
        virtual ~MyContactList();

        void addContact(QString const &username);
        void enableCallButtons();
        void removeContact(IContact &contact);

        bool exist(QString const &contactName) const;

      private:
        ICallManager &_callManager;
        QVBoxLayout *_contactList;
        std::vector<Contact *> _contacts;
    };
} // namespace GUI

#endif // MYCONTACTLIST_HPP
