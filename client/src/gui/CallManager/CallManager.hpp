/*
** EPITECH PROJECT , 2021
** CallManager
** File description:
** simon
*/

#ifndef CALLMANAGER_HPP
#define CALLMANAGER_HPP

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include "gui/MyContactList/MyContactList.hpp"

namespace GUI
{
    class CallManager : public QGroupBox {
        Q_OBJECT

      public:
        CallManager(MyContactList &contactList);
        virtual ~CallManager();

        void setCallMembers(std::vector<QString> const &usernames);
        void removeMember(QString const &username);
        void addMember(QString const &username);
        void clearMemberList();

      private slots:
        void slotHangUpCall() noexcept;

      private:
        MyContactList &_contactList;
        QGroupBox *_memberGroup;
        QVBoxLayout *_memberList;

        QPushButton *_hangUpButton;
    };
} // namespace GUI

#endif // CALLMANAGER_HPP
