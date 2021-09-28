/*
 * EPITECH PROJECT, 2021
 * Contact
 * File description:
 * ContactInterpreter.hpp - Created: 27/09/2021
 */

#ifndef CONTACT_INTERPRETER_HPP
#define CONTACT_INTERPRETER_HPP

#include "IInterpreter.hpp"

namespace network
{
    template <size_t PACKETSIZE> class ContactInterpreter : public IInterpreter<PACKSIZE> {
      public:
        ContactInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager);
        ~ContactInterpreter() = default;

        void GET(const TramTCP &tram, const string &ip, const size_t &port);
        void POST(const TramTCP &tram, const string &ip, const size_t &port);
        void DELETE(const TramTCP &tram, const string &ip, const size_t &port);

      protected:
        void _send(const std::array<char, PACKETSIZE> &data, const string &ip, const size_t &port);

      private:
        DatabaseManager &_databaseManager;
        IConnection<PACKETSIZE> &_network;
    };
}; // namespace network

#endif