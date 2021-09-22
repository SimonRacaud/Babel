/*
** EPITECH PROJECT , 2021
** Account
** File description:
** simon
*/

#include "Account.hpp"

using namespace GUI;

Account::Account(QWidget *parent) : QGroupBox("My Account", parent)
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
    this->setMaximumHeight(100);
    /**
     * TODO:
     *  apply button event => set account username
     *  _username label update with the new username + color
     */
     QObject::connect(_apply, SIGNAL(clicked()), this, SLOT(applyUsername(void)));
}

void Account::applyUsername()
{
    std::cout << "TEST\n";
}