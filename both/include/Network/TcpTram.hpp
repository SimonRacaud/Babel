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
#include <iostream>
#include <memory>
#include <vector>
#include "ContactRaw.hpp"
#include "UserRaw.hpp"
#include "tram.hpp"

namespace Network
{
    class TCPTram {
      public:
        TCPTram(TramAction action, TramType type = TramType::USER, bool error = false);
        virtual ~TCPTram();

        void setContactList(std::vector<ContactRaw> const &list);
        void setUserList(std::vector<UserRaw> const &list);
        void setErrorMessage(std::string const &message);

        template <std::size_t PACKETSIZE> std::array<char, PACKETSIZE> getBuffer() const
        {
            std::array<char, PACKETSIZE> buffer;
            TramTCP *content = (TramTCP *) (buffer.data());

            std::memset(content, 0, PACKETSIZE);
            std::memcpy(content, &_tram, sizeof(TramTCP));
            if (_tram.type == TramType::USER && _userPtr && !_tram.error) {
                UserRaw *ptr = (UserRaw *) (((char *) content) + TRAM_SIZE_SHIFT);
                std::memcpy(ptr, _userPtr, _tram.list_size);
            } else if (_tram.type == TramType::CONTACT && _contactPtr && !_tram.error) {
                ContactRaw *ptr = (ContactRaw *) (((char *) content) + TRAM_SIZE_SHIFT);
                std::memcpy(ptr, _contactPtr, _tram.list_size);
            } else if (_tram.error) {
                char *ptr = ((char *)content) + TRAM_SIZE_SHIFT;
                std::memcpy(ptr, _errorMessage.c_str(), _tram.list_size);
            }
            return buffer;
        }

      private:
        void destroyBody() noexcept;

      private:
        ContactRaw *_contactPtr;
        UserRaw *_userPtr;
        std::string _errorMessage;
        TramTCP _tram;
    };
} // namespace Network

#endif // TCPTRAMFACTORY_HPP