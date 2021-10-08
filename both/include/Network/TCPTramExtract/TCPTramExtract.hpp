/*
** PERSONAL PROJECT, 2021
** TCPTramExtract
** File description:
** TCPTramExtract.hpp
*/

#ifndef TCPTRAMEXTRACT_HPP
#define TCPTRAMEXTRACT_HPP

#include <array>
#include <cstring>
#include <stdexcept>
#include <vector>

#include "tram.hpp"

namespace Network
{
    template <std::size_t PACKETSIZE> class TCPTramExtract {
      public:
        TCPTramExtract(const std::array<char, PACKETSIZE> &buf) : _buf(buf)
        {
            if (PACKETSIZE < sizeof(Network::TramTCP))
                throw std::invalid_argument("Invalid PACKETSIZE");
            std::memcpy(&this->_tram, this->_buf.data(), Network::TRAM_SIZE_SHIFT);
            if (PACKETSIZE < sizeof(Network::TramTCP) + this->_tram.list_size) {
                std::cerr << PACKETSIZE << " < " << sizeof(Network::TramTCP) + this->_tram.list_size << std::endl;
                std::cerr << "list size: " << this->_tram.list_size << std::endl;
                throw std::invalid_argument("Invalid _tram");
            }
        }

        ~TCPTramExtract() = default;

        template <typename type> std::vector<type> getListOf() const
        {
            std::vector<type> list;
            size_t size = this->_tram.list_size / sizeof(type);

            if (!size) {
                std::cerr << this->_tram.list_size << " / " << sizeof(type) << " = " << size << std::endl;
                std::cerr << "list size: " << this->_tram.list_size << " -> " << this->_tram.list_size / sizeof(type) << std::endl;
                throw std::invalid_argument("Invalid type: Too big");
            }
            if (this->_tram.list_size % sizeof(type) != 0)
                throw std::invalid_argument("Invalid type: Not multiple");
            list = std::vector<type>(size);
            std::memcpy(list.data(), this->_buf.data() + Network::TRAM_SIZE_SHIFT, this->_tram.list_size);
            return list;
        }

        Network::TramAction getAction() const
        {
            return _tram.action;
        }

        Network::TramType getType() const
        {
            return _tram.type;
        }

        bool isCorrectTram() const
        {
            return !this->_tram.error;
        }

        std::string getStrError() const
        {
            std::string output = "";

            if (this->isCorrectTram())
                throw std::invalid_argument("No error, tram is correct");
            std::memcpy(output.data(), this->_buf.data() + TRAM_SIZE_SHIFT, this->_tram.list_size + 1);
            return output;
        }

        void dump() const
        {
            std::cout << "Action : " << int(_tram.action) << std::endl;
            std::cout << "Type : " << int(_tram.type) << std::endl;
            std::cout << "error : " << _tram.error << std::endl;
            std::cout << "data :";
            //            std::cout.write((const char *) (_tram.list), sizeof(UserRaw));
            std::cout.write(_buf.data(), PACKETSIZE);
            std::cout << std::endl;
        }

      private:
        const std::array<char, PACKETSIZE> _buf;
        Network::TramTCP _tram;
    };
} // namespace Network

#endif