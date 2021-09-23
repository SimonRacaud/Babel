/*
** EPITECH PROJECT , 2021
** AddContact
** File description:
** simon
*/

#include "AddContact.hpp"

using namespace GUI;

AddContact::AddContact(MyContactList &contactList) : QGroupBox("Add Contact"), _contactList(contactList)
{
    _mainLayout = new QHBoxLayout;
    _widthControl = new QWidget;
    _layout = new QHBoxLayout;
    _apply = new QPushButton("Apply");
    _input = new QLineEdit;

    // Link
    this->setLayout(_mainLayout);
    _mainLayout->addWidget(_widthControl);
    _widthControl->setLayout(_layout);
    _layout->addWidget(_input);
    _layout->addWidget(_apply);
    // Config
    _mainLayout->setAlignment(Qt::AlignLeft);
    _widthControl->setMaximumWidth(ADD_CONTACT_MAX_WIDTH);
    _input->setPlaceholderText("username");
    /// Events
    QObject::connect(_apply, SIGNAL(clicked()), this, SLOT(addContact()));
}

AddContact::~AddContact()
{
    delete _apply;
    delete _input;
    delete _widthControl;
}

void AddContact::addContact() noexcept
{
    QString const &input = _input->text();

    if (input.isEmpty() == false) {
        /// TODO : Network add contact
        if (true/* contact added on server */) {
            _input->setText("");
            _contactList.addContact(input);
        }
    }
}