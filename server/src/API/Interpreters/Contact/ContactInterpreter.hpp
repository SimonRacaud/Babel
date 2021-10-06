/*
 * EPITECH PROJECT, 2021
 * Contact
 * File description:
 * ContactInterpreter.hpp - Created: 27/09/2021
 */

#ifndef CONTACT_INTERPRETER_HPP
#define CONTACT_INTERPRETER_HPP

#include "IInterpreter.hpp"

namespace Network
{
    template <size_t PACKETSIZE> class ContactInterpreter : public IInterpreter<PACKETSIZE> {
      public:
        ContactInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager);
        ~ContactInterpreter() = default;

        void GET(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port);
        void POST(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port);
        void DELETE(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port);

      protected:
        void _send(const TCPTram &data, const string &ip, const size_t &port);

      private:
        DatabaseManager &_databaseManager;
        IConnection<PACKETSIZE> &_network;
    };
}; // namespace Network

#endif