/*
 * EPITECH PROJECT, 2021
 * API
 * File description:
 * API.cpp - Created: 27/09/2021
 */

#include <string.h>

#include "API.hpp"

using namespace network;

template <size_t PACKETSIZE> API<PACKETSIZE>::API(DatabaseManager &databaseManager) : _databaseManager(databaseManager)
{
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::operator()(const std::array<char, PACKETSIZE> &data, const size_t &size)
{
    const TramTCP &tram = this->_dataFilter(data);

    this->_tramActions[tram.action](tram);
}

template <size_t PACKETSIZE> const TramTCP API<PACKETSIZE>::_dataFilter(const std::array<char, PACKETSIZE> &data) const
{
    TramTCP tram;

    memcpy(tram.action, data[0], sizeof(TramAction));
    memcpy(tram.type, data[sizeof(TramAction)], sizeof(TramType));
    memcpy(tram.list_size, data[sizeof(TramAction) + sizeof(TramType)], sizeof(size_t));
    tram.list = data[sizeof(TramAction) + sizeof(TramType) + sizeof(size_t)];
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_get(const TramTCP &tram)
{
    this->_tramTypes[tram.type].GET(tram);
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_post(const TramTCP &tram)
{
    this->_tramTypes[tram.type].POST(tram);
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_delete(const TramTCP &tram)
{
    this->_tramTypes[tram.type].DELETE(tram);
}