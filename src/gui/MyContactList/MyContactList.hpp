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
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QScrollArea>
#include <vector>

#include "Contact/Contact.hpp"

namespace GUI
{
    class MyContactList : public QGroupBox {
      public:
        MyContactList(std::vector<QString> const &contactNameList);
        virtual ~MyContactList() = default;

      private:
        QVBoxLayout *_contactList;
        std::vector<Contact *> _contacts;
    };
} // namespace GUI

#endif // MYCONTACTLIST_HPP
