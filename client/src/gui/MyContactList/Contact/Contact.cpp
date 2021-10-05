/*
** EPITECH PROJECT , 2021
** Contact
** File description:
** simon
*/

#include "Contact.hpp"

using namespace GUI;

Contact::Contact(QVBoxLayout &parent, QString const &userName,
    ICallManager &callManager, IMyContactList &contactList)
    : _callManager(callManager), _contactList(contactList)
{
    this->_widthControl = new QWidget;
    this->_layout = new QHBoxLayout;
    this->_label = new QLabel(userName);
    this->_callLabel = new QLabel;
    this->_buttonCall = new QPushButton("Call");
    this->_buttonRemove = new QPushButton("Remove");

    _widthControl->setMaximumWidth(CONTACT_MAX_WIDTH);
    _widthControl->setLayout(_layout);
    _layout->addWidget(_label);
    _layout->addWidget(_buttonCall);
    _layout->addWidget(_buttonRemove);
    _layout->addWidget(_callLabel);
    _buttonCall->setFixedWidth(CONTACT_BUTT_WIDTH);
    _buttonRemove->setFixedWidth(CONTACT_BUTT_WIDTH);

    parent.addWidget(_widthControl);

    /// Events
    QObject::connect(
        _buttonCall, SIGNAL(clicked()), this, SLOT(slotCallContact()));
    QObject::connect(
        _buttonRemove, SIGNAL(clicked()), this, SLOT(slotRemoveContact()));
}

Contact::~Contact()
{
    delete _label;
    delete _callLabel;
    delete _buttonCall;
    delete _buttonRemove;
}

void Contact::slotRemoveContact() noexcept
{
    //QString const &username = _label->text();

    // TODO Network : API remove contact
    if (true /*network ok*/) {
        this->_contactList.removeContact(*this);
    }
}

void Contact::slotCallContact() noexcept
{
    QString const &username = _label->text();

    this->disableCall();
    // TODO Network : start call
    if (true /*network ok*/) {
        _callManager.addMember(username);
    } else {
        this->enableCall();
        std::cerr << "Info: fail to call " << username.toStdString()
                  << ". Network error" << std::endl;
    }
}

void Contact::enableCall()
{
    this->_buttonCall->setDisabled(false);
    this->_callLabel->setText("");
}

void Contact::disableCall()
{
    this->_buttonCall->setDisabled(true);
    this->_callLabel->setText("...calling");
}

QWidget *Contact::getTopWidget()
{
    return _widthControl;
}

QString Contact::getUsername() const
{
    return _label->text();
}