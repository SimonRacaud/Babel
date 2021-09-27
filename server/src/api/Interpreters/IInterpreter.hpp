/*
 * EPITECH PROJECT, 2021
 * Interpreters
 * File description:
 * IInterpreter.hpp - Created: 27/09/2021
 */

#ifndef INTERPRETER_INTERFACE_HPP
#define INTERPRETER_INTERFACE_HPP

#include "DatabaseManager.hpp"
#include "tram.hpp"

namespace network
{
    class IInterpreter {
      public:
        virtual IInterpreter(DatabaseManager &databaseManager);

        virtual void GET(const TramTCP &tram) = 0;
        virtual void POST(const TramTCP &tram) = 0;
        virtual void DELETE(const TramTCP &tram) = 0;
    };
}; // namespace network

#endif