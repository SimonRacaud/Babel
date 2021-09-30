/*
** PERSONAL PROJECT, 2021
** Network
** File description:
** Network.hpp
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <ctime>
#include <cstring>

namespace Network
{
    const int BUFFER_SIZE = 1024;
    const unsigned int MAGIC_NUMBER = 0x42;

    typedef struct UDPTram_s
    {
        unsigned int magicNumber;   // 4
        size_t timestamp;           // 8
        char data[1008];            // 1024 - (4 * 2 + 8)
        unsigned int dataSize;      // 4
        UDPTram_s()
        {
            std::memset(this, 0, sizeof(UDPTram_s));
            this->magicNumber = Network::MAGIC_NUMBER;
            this->timestamp = std::time(0);
        }
        UDPTram_s(void *src)
        {
            std::memset(this, 0, sizeof(UDPTram_s));
            this->magicNumber = Network::MAGIC_NUMBER;
            this->timestamp = std::time(0);
            std::memmove(this->data, src, sizeof(this->data));
        }
    } UDPTram_t;
}

#endif