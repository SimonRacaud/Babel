/*
** EPITECH PROJECT , 2021
** TCPTram
** File description:
** simon
*/

#ifndef TCPTRAMFACTORY_HPP
#define TCPTRAMFACTORY_HPP

#include <array>
#include <cstring>
#include <memory>
#include <vector>

#include "ContactRaw.hpp"
#include "UserRaw.hpp"
#include "tram.hpp"

namespace Network
{
    class TCPTram {
      public:
        TCPTram(TramAction action, TramType type = TramType::USER, bool error = false) : _contactPtr(nullptr), _userPtr(nullptr)
        {
            this->_tram.action = action;
            this->_tram.type = type;
            this->_tram.error = error;
            this->_tram.list_size = 0;
            this->_tram.list = nullptr;
        }
        ~TCPTram()
        {
            this->_destroyBody();
        }

        void setContactList(std::vector<ContactRaw> const &list)
        {
            this->_destroyBody();
            _contactPtr = new ContactRaw[list.size()];
            this->_tram.type = TramType::CONTACT;
            this->_tram.list = _contactPtr;
            this->_tram.list_size = list.size();
            for (size_t i = 0; i < list.size(); i++) {
                _contactPtr[i] = list[i];
            }
        }

        void setUserList(std::vector<UserRaw> const &list)
        {
            this->_destroyBody();
            _userPtr = new UserRaw[list.size()];
            this->_tram.type = TramType::USER;
            this->_tram.list = _userPtr;
            this->_tram.list_size = list.size();
            for (size_t i = 0; i < list.size(); i++) {
                _userPtr[i] = list[i];
            }
        }

        template <std::size_t PACKETSIZE> std::shared_ptr<std::array<char, PACKETSIZE>> getBuffer() const
        {
            std::shared_ptr<std::array<char, PACKETSIZE>> buffer = std::make_shared<std::array<char, PACKETSIZE>>();
            TramTCP *content = (TramTCP *) (buffer->data());

            std::memcpy(content, &this->_tram, sizeof(TramTCP));
            content->list = nullptr;
            if (this->_tram.type == TramType::USER && _userPtr) {
                content->list = _userPtr;
            } else if (this->_tram.type == TramType::CONTACT && _contactPtr) {
                content->list = _contactPtr;
            }
            return buffer;
        }

      private:
        void _destroyBody() noexcept
        {
            if (this->_contactPtr) {
                delete this->_contactPtr;
            }
            if (this->_userPtr) {
                delete this->_userPtr;
            }
        }

      private:
        ContactRaw *_contactPtr;
        UserRaw *_userPtr;
        TramTCP _tram;
    };
} // namespace Network

#endif // TCPTRAMFACTORY_HPP
