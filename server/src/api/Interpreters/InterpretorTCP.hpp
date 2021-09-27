/*
 * EPITECH PROJECT, 2021
 * Interpreters
 * File description:
 * InterpretorTCP.hpp - Created: 27/09/2021
 */

#ifndef API_INTERPRETER_TCP_HPP
#define API_INTERPRETER_TCP_HPP

#include <functional>
#include <unordered_map>

#include "IInterpreter.hpp"

namespace network
{
    enum class TramType
    {
        USER = "USER",
        CONTACT = "CONTACT"
    };

    template <size_t PACKETSIZE> class InterpreterTCP : public IInterpreter<PACKETSIZE> {
      public:
        InterpreterTCP(DatabaseManager &databaseManager);
        ~InterpreterTCP() = default;

        void operator()(const std::array<char, PACKETSIZE> &data, const size_t &size);

      private:
        void _get(const std::array<char, PACKETSIZE> &data, const size_t &size);
        void _post(const std::array<char, PACKETSIZE> &data, const size_t &size);
        void _delete(const std::array<char, PACKETSIZE> &data, const size_t &size);

        DatabaseManager &_databaseManager;

        const std::unordered_map<string, std::function<void(const std::array<char, PACKETSIZE> &, const size_t &)>> _tramActions = {
            {"GET", this->_get},
            {"POST", this->_post},
            {"DELETE", this->_delete},
        };
    };
}; // namespace network

#endif