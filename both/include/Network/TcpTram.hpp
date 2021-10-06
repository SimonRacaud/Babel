/*
** EPITECH PROJECT , 2021
** TCPTram
** File description:
** simon
*/

#ifndef TCPTRAMFACTORY_HPP
#define TCPTRAMFACTORY_HPP

#include "tram.hpp"
#include "UserRaw.hpp"
#include "ContactRaw.hpp"
#include <vector>
#include <array>
#include <cstring>
#include <memory>
#include <iostream>

namespace Network
{
    class TCPTram {
      public:
        TCPTram(TramAction action, TramType type = TramType::USER, bool error = false);
        virtual ~TCPTram();

        void setContactList(std::vector<ContactRaw> const &list);
        void setUserList(std::vector<UserRaw> const &list);

        template <std::size_t PACKETSIZE>
        std::array<char, PACKETSIZE> getBuffer() const
        {
            std::array<char, PACKETSIZE> buffer;
            TramTCP *content = (TramTCP *)(buffer.data());

            std::memset(content, 0, PACKETSIZE);
            std::memcpy(content, &_tram, sizeof(TramTCP));
            content->list = nullptr;
            if (_tram.type == TramType::USER && _userPtr) {
                UserRaw *ptr = (UserRaw *)(((char *)content) + TRAM_SIZE_SHIFT);
                for (size_t i = 0; i < _tram.list_size / sizeof(UserRaw); i += sizeof(UserRaw)) {
                    ptr[i] = _userPtr[i];
                }
            } else if (_tram.type == TramType::CONTACT && _contactPtr) {
                ContactRaw *ptr = (ContactRaw *)(((char *)content) + TRAM_SIZE_SHIFT);
                for (size_t i = 0; i < _tram.list_size / sizeof(ContactRaw); i += sizeof(ContactRaw)) {
                    ptr[i] = _contactPtr[i];
                }
            }
            return buffer;
        }

      private:
        void destroyBody() noexcept;

      private:
        ContactRaw *_contactPtr;
        UserRaw *_userPtr;
        TramTCP _tram;
    };
}

#endif // TCPTRAMFACTORY_HPP
