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
#include <algorithm>
#include <iostream>
#include <vector>

#include "Contact/Contact.hpp"
#include "ICallManager.hpp"
#include "IContact.hpp"
#include "IMyContactList.hpp"

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
        void clearList();

      public slots:
        void slotSetContactList(std::vector<ContactRaw> const &contacts);

      private:
        ICallManager &_callManager;
        QVBoxLayout *_contactList;
        std::vector<Contact *> _contacts;
    };
} // namespace GUI

#endif // MYCONTACTLIST_HPP
