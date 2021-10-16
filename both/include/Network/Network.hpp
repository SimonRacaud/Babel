/*
** PERSONAL PROJECT, 2021
** Network
** File description:
** Network.hpp
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <cstring>
#include <ctime>
#include <string>

namespace Network
{
    const std::string IP_SERVER = "10.19.240.217";
    const int PORT_MAIN_SERVER = 8081;
    const int PORT_CALL_SERVER = 8082;
    const int PORT_UDP_RECEIVE = 8088;
    const int DATA_SIZE = 1008;
    const int BUFFER_SIZE = 1024;
    const unsigned int MAGIC_NUMBER = 0x42;

    const int MAX_MEMBER_CALL = 5;
    const int MAX_CONTACT = 5;

    typedef struct __attribute__((packed)) UDPTram_s {
        unsigned int magicNumber;      // 4
        size_t timestamp;              // 8
        char data[Network::DATA_SIZE]; // 1024 - (4 * 2 + 8)
        unsigned int dataSize;         // 4
        UDPTram_s()
        {
            std::memset(this, 0, sizeof(UDPTram_s));
            this->magicNumber = Network::MAGIC_NUMBER;
            this->timestamp = std::time(0);
            this->dataSize = Network::DATA_SIZE;
        }
        UDPTram_s(void *src)
        {
            std::memset(this, 0, sizeof(UDPTram_s));
            this->magicNumber = Network::MAGIC_NUMBER;
            this->timestamp = std::time(0);
            std::memmove(this->data, src, Network::DATA_SIZE);
            this->dataSize = Network::DATA_SIZE;
        }
    } UDPTram_t;
} // namespace Network

#endif