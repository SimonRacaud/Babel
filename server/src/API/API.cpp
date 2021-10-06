/*
 * EPITECH PROJECT, 2021
 * API
 * File description:
 * API.cpp - Created: 27/09/2021
 */

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
    const TCPTramExtract<PACKETSIZE> tram(data);

    std::cout << "redirect" << std::endl;
    switch (tram.getAction()) {
        case TramAction::GET: this->_get(tram, ip, port); break;
        case TramAction::POST: this->_post(tram, ip, port); break;
        case TramAction::DELETE: this->_delete(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramAction");
    }
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_get(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port)
{
    std::cout << "GET" << std::endl;
    switch (tram.getType()) {
        case TramType::USER: std::cerr << "USER" << std::endl; break;
        case TramType::CONTACT: std::cerr << "CONTACT" << std::endl; break;
        default: std::cerr << "UNKNOWN" << std::endl;
    }
    switch (tram.getType()) {
        case TramType::USER: this->_userInterpreter.GET(tram, ip, port); break;
        case TramType::CONTACT: this->_contactInterpreter.GET(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramType");
    }
}

template <size_t PACKETSIZE> void API<PACKETSIZE>::_post(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port)
{
    std::cout << "POST" << std::endl;
    switch (tram.getType()) {
        case TramType::USER: std::cerr << "USER" << std::endl; break;
        case TramType::CONTACT: std::cerr << "CONTACT" << std::endl; break;
        default: std::cerr << "UNKNOWN" << std::endl;
    }
    switch (tram.getType()) {
        case TramType::USER: this->_userInterpreter.POST(tram, ip, port); break;
        case TramType::CONTACT: this->_contactInterpreter.POST(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramType");
    }
}

template <size_t PACKETSIZE>
void API<PACKETSIZE>::_delete(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port)
{
    std::cout << "DELETE" << std::endl;
    switch (tram.getType()) {
        case TramType::USER: std::cerr << "USER" << std::endl; break;
        case TramType::CONTACT: std::cerr << "CONTACT" << std::endl; break;
        default: std::cerr << "UNKNOWN" << std::endl;
    }
    switch (tram.getType()) {
        case TramType::USER: this->_userInterpreter.DELETE(tram, ip, port); break;
        case TramType::CONTACT: this->_contactInterpreter.DELETE(tram, ip, port); break;
        default: throw std::invalid_argument("Invalid TramType");
    }
}

template class API<Network::BUFFER_SIZE>;