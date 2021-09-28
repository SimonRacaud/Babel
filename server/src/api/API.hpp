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

#include "ContactInterpreter.hpp"
#include "IAPI.hpp"
#include "UserInterpreter.hpp"
#include "tram.hpp"

namespace network
{
    template <size_t PACKETSIZE> class API : public IAPI<PACKETSIZE> {
      public:
        API(DatabaseManager &databaseManager);
        ~API() = default;

        void operator()(const std::array<char, PACKETSIZE> &data, const size_t &size);

      private:
        const TramTCP _dataFilter(const std::array<char, PACKETSIZE> &data) const;
        void _get(const TramTCP &tram);
        void _post(const TramTCP &tram);
        void _delete(const TramTCP &tram);

        DatabaseManager &_databaseManager;

        const std::unordered_map<TramAction, std::function<void(const TramTCP &)>> _tramActions = {
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