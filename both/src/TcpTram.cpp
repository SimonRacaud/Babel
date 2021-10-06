/*
** EPITECH PROJECT , 2021
** TCPTram
** File description:
** simon
*/

#include "TcpTram.hpp"

using namespace Network;

TCPTram::TCPTram(TramAction action, TramType type, bool error) : _contactPtr(nullptr), _userPtr(nullptr)
{
    _tram.action = action;
    _tram.type = type;
    _tram.error = error;
    _tram.list_size = 0;
    _tram.list = nullptr;
}

TCPTram::~TCPTram()
{
    this->destroyBody();
}

void TCPTram::destroyBody() noexcept
{
    if (_contactPtr) {
        delete[] _contactPtr;
    }
    if (_userPtr) {
        delete[] _userPtr;
    }
}

void TCPTram::setContactList(std::vector<ContactRaw> const &list)
{
    this->destroyBody();
    _contactPtr = new ContactRaw [list.size()];
    _tram.type = TramType::CONTACT;
    _tram.list = _contactPtr;
    _tram.list_size = list.size() * sizeof(ContactRaw);
    for (size_t i = 0; i < list.size(); i++) {
        _contactPtr[i] = list[i];
    }
}

void TCPTram::setUserList(std::vector<UserRaw> const &list)
{
    this->destroyBody();
    _userPtr = new UserRaw [list.size()];
    _tram.type = TramType::USER;
    _tram.list = _userPtr;
    _tram.list_size = list.size() * sizeof(UserRaw);
    for (size_t i = 0; i < list.size(); i++) {
        _userPtr[i] = list[i];
    }
}