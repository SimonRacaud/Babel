/*
** EPITECH PROJECT , 2021
** Contact
** File description:
** simon
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "ICallManager.hpp"
#include "IMyContactList.hpp"
#include "IContact.hpp"

/**
 * Config
 */
#define CONTACT_BUTT_WIDTH 70
#define CONTACT_MAX_WIDTH  300

namespace GUI
{
    class Contact : public QObject, public IContact {
        Q_OBJECT

      public:
        Contact(QVBoxLayout &parent, QString const &userName,
            ICallManager &callManager, IMyContactList &contactList);
        virtual ~Contact();

        void enableCall();
        void disableCall();

        QWidget *getTopWidget();

      private slots:
        void slotCallContact() noexcept;
        void slotRemoveContact() noexcept;

      private:
        ICallManager &_callManager;
        IMyContactList &_contactList;

        QWidget *_widthControl;
        QHBoxLayout *_layout;
        QLabel *_label;
        QPushButton *_buttonCall;
        QPushButton *_buttonRemove;
    };
} // namespace GUI

#endif // CONTACT_HPP
