/*
** EPITECH PROJECT , 2021
** Contact
** File description:
** simon
*/

#include "Contact.hpp"

using namespace GUI;

Contact::Contact(QVBoxLayout &parent, QString const &userName)
{
    this->_widthControl = new QWidget;
    this->_layout = new QHBoxLayout;
    this->_label = new QLabel(userName);
    this->_buttonCall = new QPushButton("Call");
    this->_buttonRemove = new QPushButton("Remove");

    _widthControl->setMaximumWidth(CONTACT_MAX_WIDTH);
    _widthControl->setLayout(_layout);
    _layout->addWidget(_label);
    _layout->addWidget(_buttonCall);
    _layout->addWidget(_buttonRemove);
    _buttonCall->setFixedWidth(CONTACT_BUTT_WIDTH);
    _buttonRemove->setFixedWidth(CONTACT_BUTT_WIDTH);

    parent.addWidget(_widthControl);
}

Contact::~Contact()
{
    delete _label;
    delete _buttonCall;
    delete _buttonRemove;
}

void Contact::slotRemoveContact() noexcept
{
    // TODO
    // get contact name
    // Network : API remove contact
    // remove contact from GUI list
}

void Contact::slotCallContact() noexcept
{
    // TODO
    // get contact name
    // gui : callManager add member
    // Network : start call
    // disable call button
}

void Contact::enableCall()
{
    this->_buttonCall->setDisabled(false);
}

void Contact::disableCall()
{
    this->_buttonCall->setDisabled(true);
}