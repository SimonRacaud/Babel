/*
 * EPITECH PROJECT, 2021
 * API
 * File description:
 * API.cpp - Created: 27/09/2021
 */

#include <string.h>

#include "API.hpp"

using namespace Network;

template <size_t PACKETSIZE>
API<PACKETSIZE>::API(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager)
    : _databaseManager(databaseManager), _network(network), _userInterpreter(network, databaseManager),
      _contactInterpreter(network, databaseManager)
{
}

template <size_t PACKETSIZE>
void API<PACKETSIZE>::operator()(const std::array<char, PACKETSIZE> &data, const string &ip, const size_t port)
{
    const TramTCP &tram = this->_dataFilter(data);

    switch (tram.action) {
        case TramAction::GET: this->_get(tram, ip, port); break;
        case TramAction::POST: this->_post(tram, ip, port); break;
        case TramAction::DELETE: this->_delete(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramAction");
    }
}

template <size_t PACKETSIZE> const TramTCP API<PACKETSIZE>::_dataFilter(const std::array<char, PACKETSIZE> &data) const
{
    TramTCP tram;

    std::memcpy(&tram.action, &(data[0]), sizeof(TramAction));
    std::memcpy(&tram.type, &(data[sizeof(TramAction)]), sizeof(TramType));
    std::memcpy(&tram.list_size, &(data[sizeof(TramAction) + sizeof(TramType)]), sizeof(size_t));

    const size_t listPos = sizeof(TramAction) + sizeof(TramType) + sizeof(size_t);
    std::memcpy(&tram.list, &(data[listPos]), PACKETSIZE - listPos);

    return tram;
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_get(const TramTCP &tram, const string &ip, const size_t &port)
{
    switch (tram.type) {
        case TramType::USER: this->_userInterpreter.GET(tram, ip, port); break;
        case TramType::CONTACT: this->_contactInterpreter.GET(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramType");
    }
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_post(const TramTCP &tram, const string &ip, const size_t &port)
{
    switch (tram.type) {
        case TramType::USER: this->_userInterpreter.POST(tram, ip, port); break;
        case TramType::CONTACT: this->_contactInterpreter.POST(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramType");
    }
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_delete(const TramTCP &tram, const string &ip, const size_t &port)
{
    switch (tram.type) {
        case TramType::USER: this->_userInterpreter.DELETE(tram, ip, port); break;
        case TramType::CONTACT: this->_contactInterpreter.DELETE(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramType");
    }
}

template class API<Network::BUFFER_SIZE>;