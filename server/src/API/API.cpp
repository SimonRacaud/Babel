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
    : _network(network), _databaseManager(databaseManager)
{
}

template <size_t PACKETSIZE>
void API<PACKETSIZE>::operator()(const std::array<char, PACKETSIZE> &data, const string &ip, const size_t port)
{
    const TramTCP &tram = this->_dataFilter(data);

    this->_tramActions.at(tram.action)(tram, ip, port);
}

template <size_t PACKETSIZE> const TramTCP API<PACKETSIZE>::_dataFilter(const std::array<char, PACKETSIZE> &data) const
{
    TramTCP tram;

    std::memcpy(tram.action, data[0], sizeof(TramAction));
    std::memcpy(tram.type, data[sizeof(TramAction)], sizeof(TramType));
    std::memcpy(tram.list_size, data[sizeof(TramAction) + sizeof(TramType)], sizeof(size_t));
    tram.list = data[sizeof(TramAction) + sizeof(TramType) + sizeof(size_t)];

    return tram;
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_get(const TramTCP &tram, const string &ip, const size_t &port)
{
    this->_tramTypes.at(tram.type).GET(tram, ip, port);
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_post(const TramTCP &tram, const string &ip, const size_t &port)
{
    this->_tramTypes.at(tram.type).POST(tram, ip, port);
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_delete(const TramTCP &tram, const string &ip, const size_t &port)
{
    this->_tramTypes.at(tram.type).DELETE(tram, ip, port);
}