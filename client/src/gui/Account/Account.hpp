/*
** EPITECH PROJECT , 2021
** Account
** File description:
** simon
*/

#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <QObject>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QObject>
#include <iostream>

namespace GUI
{
    class Account : public QGroupBox {
        Q_OBJECT

      public:
        Account(QWidget *parent = nullptr);
        virtual ~Account() = default;

      private slots:
        void applyUsername();

      private:
        QLineEdit *_input;
        QPushButton *_apply;
        QLabel *_username;
    };
}

#endif // ACCOUNT_HPP
