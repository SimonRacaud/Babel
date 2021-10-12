/*
** EPITECH PROJECT , 2021
** Contact
** File description:
** simon
*/

#include "Contact.hpp"

using namespace GUI;

extern Network::NetworkManager networkManager;

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
    QObject::connect(&networkManager, &Network::NetworkManager::sigRemoveContact, this, &Contact::slotApplyRemove);
    QObject::connect(&networkManager, &Network::NetworkManager::sigCallSuccess, this, &Contact::slotApplyCall);
    QObject::connect(&networkManager, &Network::NetworkManager::sigCallUpdate, this, &Contact::slotUpdateCall);
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
    try {
        networkManager.removeContact(this->getUsername());
    } catch (std::exception const &e) {
        std::cerr << "Error : fail to remove contact. " << e.what() << std::endl;
    }
}

void Contact::slotApplyRemove(QString const &contactUsername) noexcept
{
    if (this->getUsername() == contactUsername) {
        this->_contactList.removeContact(*this);
    }
}

void Contact::slotCallContact() noexcept
{
    QString const &username = this->getUsername();

    try {
        networkManager.callUser(username);
    } catch (std::exception const &e) {
        std::cerr << "Error: fail to call user " << username.toStdString()
                  << ". " << e.what() << std::endl;
    }
}

void Contact::slotApplyCall(std::vector<UserRaw> const &list) noexcept
{
    QString username = this->getUsername();
    auto it = std::find_if(list.begin(), list.end(), [username] (UserRaw const &user) { return QString(user.username) == username; });

    if (it != list.end()) {
        this->disableCall();
    }
}

void Contact::slotUpdateCall(std::vector<UserRaw> const &list) noexcept
{
    QString username = this->getUsername();
    auto it = std::find_if(list.begin(), list.end(), [username] (UserRaw const &user) { return QString(user.username) == username; });

    if (it == list.end()) {
        this->enableCall();
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