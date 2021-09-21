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
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>

#define ADD_CONTACT_MAX_WIDTH 300

namespace GUI
{
    class AddContact : public QGroupBox {
      public:
        AddContact();
        virtual ~AddContact() = default;

      private:
        QPushButton *_apply;
        QLineEdit *_input;
    };
}

#endif // ADDCONTACT_HPP
