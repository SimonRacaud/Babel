/*
 * EPITECH PROJECT, 2021
 * User
 * File description:
 * UserInterpreter.hpp - Created: 27/09/2021
 */

#ifndef USER_INTERPRETER_HPP
#define USER_INTERPRETER_HPP

#include "IInterpreter.hpp"

namespace Network
{
    template <size_t PACKETSIZE> class UserInterpreter : public IInterpreter<PACKETSIZE> {
      public:
        UserInterpreter(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager);
        ~UserInterpreter() = default;

        void GET(const TramTCP &tram, const string &ip, const size_t &port);
        void POST(const TramTCP &tram, const string &ip, const size_t &port);
        void DELETE(const TramTCP &tram, const string &ip, const size_t &port);

      protected:
        void _send(const std::array<char, PACKETSIZE> &data, const string &ip, const size_t &port);

      private:
        DatabaseManager &_databaseManager;
        IConnection<PACKETSIZE> &_network;
    };
}; // namespace Network

#endif