/*
 * EPITECH PROJECT, 2021
 * Interpreters
 * File description:
 * IInterpreter.hpp - Created: 27/09/2021
 */

#ifndef API_INTERFACE_INTERPRETER_HPP
#define API_INTERFACE_INTERPRETER_HPP

#include <array>

#include "DatabaseManager.hpp"
#include "utils.hpp"

namespace network
{
    template <size_t PACKETSIZE> class IInterpreter {
      public:
        virtual IInterpreter(DatabaseManager &databaseManager);

        virtual void operator()(const std::array<char, PACKETSIZE> &data, const size_t &size);
    };
}; // namespace network

#endif