/*
 * EPITECH PROJECT, 2021
 * API
 * File description:
 * API.hpp - Created: 27/09/2021
 */

#ifndef API_HPP
#define API_HPP

#include <functional>
#include <unordered_map>

#include "Contact/ContactInterpreter.hpp"
#include "IAPI.hpp"
#include "User/UserInterpreter.hpp"

namespace Network
{
    template <size_t PACKETSIZE> class API : public IAPI<PACKETSIZE> {
      public:
        API(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager);
        ~API() = default;

        void operator()(const std::array<char, PACKETSIZE> &data, const string &ip = "", const size_t port = 0);

      private:
        void _get(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port);
        void _post(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port);
        void _delete(const TCPTramExtract<PACKETSIZE> &tram, const string &ip, const size_t &port);

        DatabaseManager &_databaseManager;
        IConnection<PACKETSIZE> &_network;
        UserInterpreter<PACKETSIZE> _userInterpreter;
        ContactInterpreter<PACKETSIZE> _contactInterpreter;
    };

}; // namespace Network

#endif