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
    /**
     * TODO:
     *  Call button event => start a call with the current user
     *  Remove button event => remove contact
     */
}