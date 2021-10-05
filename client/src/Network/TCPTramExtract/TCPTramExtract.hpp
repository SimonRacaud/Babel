/*
** PERSONAL PROJECT, 2021
** TCPTramExtract
** File description:
** TCPTramExtract.hpp
*/

#ifndef TCPTRAMEXTRACT_HPP
#define TCPTRAMEXTRACT_HPP

#include "tram.hpp"
#include <array>
#include <vector>
#include <cstring>
#include <stdexcept>

template <std::size_t PACKETSIZE>
class TCPTramExtract
{
    public:
        TCPTramExtract(const std::array<char, PACKETSIZE> &buf) : _buf(buf)
        {
            if (PACKETSIZE < sizeof(Network::TramTCP))
                throw std::invalid_argument("Invalid PACKETSIZE");
            std::memmove(&this->_tram, this->_buf.data(), sizeof(Network::TramTCP));
            if (PACKETSIZE < sizeof(Network::TramTCP) + this->_tram.list_size)
                throw std::invalid_argument("Invalid _tram");
        }

        ~TCPTramExtract() = default;

        template <typename type> std::vector<type> getListOf() const
        {
            type tmp;
            std::vector<type> list;
            size_t size = this->_tram.list_size / sizeof(type);

            if (!size)
                throw std::invalid_argument("Invalid type: Too big");
            if (this->_tram.list_size % sizeof(type) != 0)
                throw std::invalid_argument("Invalid type: Not multiple");
            list = std::vector<type>(size * sizeof(type));
            std::memmove(list.data(), this->_buf.data() + sizeof(Network::TramTCP), this->_tram.list_size);
            return list;
        }

        bool isCorrectTram() const
        {
            return !this->_tram.error;
        }

        std::string getStrError() const
        {
            std::string output = "";

            if (this->isCorrectTram())
                throw std::invalid_argument("No error is correct tram");
            std::memmove(output.data(), this->_buf.data() + sizeof(Network::TramTCP), this->_tram.list_size);
            return output;
        }

    private:
        const std::array<char, PACKETSIZE> _buf;
        Network::TramTCP _tram;
};

#endif