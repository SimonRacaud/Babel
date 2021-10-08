/*
** EPITECH PROJECT , 2021
** Account
** File description:
** simon
*/

#include "Account.hpp"

using namespace GUI;

extern Network::NetworkManager networkManager;

Account::Account(QWidget *parent) : QGroupBox("My Account", parent)
{
    _mainLayout = new QVBoxLayout;
    _upperLayout = new QHBoxLayout;
    _lowerLayout = new QHBoxLayout;
    _usernameLabel = new QLabel("My username: ");
    _input = new QLineEdit;
    _apply = new QPushButton("Apply");
    _username = new QLabel("undefined");

    /// link
    this->setLayout(_mainLayout);
    _mainLayout->addLayout(_upperLayout);
    _mainLayout->addLayout(_lowerLayout);
    _upperLayout->addWidget(_usernameLabel);
    _upperLayout->addWidget(_username);
    _lowerLayout->addWidget(_input);
    _lowerLayout->addWidget(_apply);
    /// config
    _input->setPlaceholderText("username");
    _mainLayout->setAlignment(Qt::AlignTop);
    _upperLayout->setAlignment(Qt::AlignLeft);
    _username->setStyleSheet("QLabel { color: red; }");
    this->setMaximumHeight(100);
    QObject::connect(_input, SIGNAL(returnPressed()), this, SLOT(slotApplyUsername()));
    QObject::connect(_apply, SIGNAL(clicked()), this, SLOT(slotApplyUsername()));
    QObject::connect(&networkManager, &Network::NetworkManager::sigUpdateUsername, this, &Account::slotSetUsername);
}

Account::~Account()
{
    delete _input;
    delete _apply;
    delete _username;
    delete _usernameLabel;
}

void Account::slotApplyUsername()
{
    const QString &username = this->_input->text();

    if (username.isEmpty() == false) {
        _input->setText("");
        try {
            networkManager.login(username);
        } catch (std::exception const &e) {
            std::cerr << "Error: Failed to apply username." << std::endl;
        }
    }
}

void Account::slotSetUsername(QString const &username)
{
    this->_username->setText(username);
    _username->setStyleSheet("QLabel { color: blue; }");
}