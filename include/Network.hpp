/*
** PERSONAL PROJECT, 2021
** Network
** File description:
** Network.hpp
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

namespace Network
{
    const int BUFFER_SIZE = 1024;

    typedef struct UDPTram_s
    {
        unsigned int magicNumber;   // 4
        size_t timestamp;           // 8
        char size[1008];            // 1024 - (4 * 2 + 8)
        unsigned int dataSize;      // 4
    } UDPTram_t;
}

#endif