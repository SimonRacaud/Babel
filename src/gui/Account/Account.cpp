/*
** EPITECH PROJECT , 2021
** Account
** File description:
** simon
*/

#include "Account.hpp"

using namespace GUI;

Account::Account() : QGroupBox("My Account")
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *upperLayout = new QHBoxLayout;
    QHBoxLayout *lowerLayout = new QHBoxLayout;
    QLabel *usernameLabel = new QLabel("My username: ");
    _input = new QLineEdit;
    _apply = new QPushButton("Apply");
    _username = new QLabel("undefined");

    /// link
    this->setLayout(mainLayout);
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);
    upperLayout->addWidget(usernameLabel);
    upperLayout->addWidget(_username);
    lowerLayout->addWidget(_input);
    lowerLayout->addWidget(_apply);
    /// config
    _input->setPlaceholderText("username");
    mainLayout->setAlignment(Qt::AlignTop);
    upperLayout->setAlignment(Qt::AlignLeft);
    _username->setStyleSheet("QLabel { color: red; }");
    /**
     * TODO:
     *  apply button event => set account username
     *  _username label update with the new username + color
     */
}