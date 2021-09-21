/*
** EPITECH PROJECT , 2021
** Account
** File description:
** simon
*/

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

namespace GUI
{
    class Account : public QGroupBox {
      public:
        Account();
        virtual ~Account() = default;

      private:
        QLineEdit *_input;
        QPushButton *_apply;
        QLabel *_username;
    };
}

#endif // ACCOUNT_HPP
