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
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <iostream>

namespace GUI
{
    class CallManager : public QGroupBox {
      public:
        CallManager();
        virtual ~CallManager() = default;

        void setCallMembers(std::vector<QString> const &usernames);
        void removeMember(QString const &username);
        void addMember(QString const &username);
        void clearMemberList();

      private:
        QGroupBox *_memberGroup;
        QVBoxLayout *_memberList;

        QPushButton *_hangUpButton;
    };
}

#endif // CALLMANAGER_HPP
