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
#include "tram.hpp"

namespace network
{
    template <size_t PACKETSIZE> class API : public IAPI<PACKETSIZE> {
      public:
        API(IConnection<PACKETSIZE> &network, DatabaseManager &databaseManager);
        ~API() = default;

        void operator()(const std::array<char, PACKETSIZE> &data, const string &ip = "", const size_t port = 0);

      private:
        const TramTCP _dataFilter(const std::array<char, PACKETSIZE> &data) const;
        void _get(const TramTCP &tram, const string &ip, const size_t &port);
        void _post(const TramTCP &tram, const string &ip, const size_t &port);
        void _delete(const TramTCP &tram, const string &ip, const size_t &port);

        DatabaseManager &_databaseManager;
        IConnection &_network;

        const std::unordered_map<TramAction, std::function<void(const TramTCP &, const string &, const size_t &)>> _tramActions = {
            {TramAction::GET, this->_get},
            {TramAction::POST, this->_post},
            {TramAction::DELETE, this->_delete},
        };
        const std::unordered_map<TramType, std::function<void(const TramTCP &)>> _tramTypes = {
            {TramType::USER, new UserInterpreter(this->_databaseManager)},
            {TramType::CONTACT, new ContactInterpreter(this->_databaseManager)},
        };
    };

}; // namespace network

#endif