/*
** EPITECH PROJECT , 2021
** AddContact
** File description:
** simon
*/

#ifndef ADDCONTACT_HPP
#define ADDCONTACT_HPP

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include "gui/MyContactList/MyContactList.hpp"
#include "NetworkManager/NetworkManager.hpp"

#define ADD_CONTACT_MAX_WIDTH 300

namespace GUI
{
    class AddContact : public QGroupBox {
        Q_OBJECT

      public:
        AddContact(MyContactList &contactList);
        virtual ~AddContact();

      private slots:
        void slotAddContact();
        void slotApplyUpdate(QString const &contactName);

      private:
        MyContactList &_contactList;
        QPushButton *_apply;
        QLineEdit *_input;

        QHBoxLayout *_mainLayout;
        QWidget *_widthControl;
        QHBoxLayout *_layout;
    };
} // namespace GUI

#endif // ADDCONTACT_HPP
