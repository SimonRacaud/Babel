/*
 * EPITECH PROJECT, 2021
 * Interpreters
 * File description:
 * IInterpreter.hpp - Created: 27/09/2021
 */

#ifndef INTERPRETER_INTERFACE_HPP
#define INTERPRETER_INTERFACE_HPP

#include "DatabaseManager.hpp"
#include "INetwork.hpp"
#include "tram.hpp"

namespace network
{
    template <size_t PACKETSIZE> class IInterpreter {
      public:
        virtual IInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager) = 0;

        virtual void GET(const TramTCP &tram, const string &ip, const size_t &port) = 0;
        virtual void POST(const TramTCP &tram, const string &ip, const size_t &port) = 0;
        virtual void DELETE(const TramTCP &tram, const string &ip, const size_t &port) = 0;

      protected:
        virtual void _send(const std::array<char, PACKETSIZE> &data, const string &ip, const size_t &port) = 0;
    };
}; // namespace network

#endif