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
#include "TCPTram/TcpTram.hpp"
#include "TCPTramExtract/TCPTramExtract.hpp"

namespace Network
{
    template <size_t PACKETSIZE> class IInterpreter {
      public:
        virtual void GET(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port) = 0;
        virtual void POST(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port) = 0;
        virtual void DELETE(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port) = 0;

      protected:
        virtual void _send(const TCPTram &data, const string &ip, const size_t &port) = 0;
    };
}; // namespace Network

#endif