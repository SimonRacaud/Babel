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
    class ContactInterpreter : public IInterpreter {
      public:
        ContactInterpreter(DatabaseManager &databaseManager);

        void GET(const TramTCP &tram);
        void POST(const TramTCP &tram);
        void DELETE(const TramTCP &tram);

      private:
        DatabaseManager &_databaseManager;
    };
}; // namespace network

#endif