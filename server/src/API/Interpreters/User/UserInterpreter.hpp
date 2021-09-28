/*
 * EPITECH PROJECT, 2021
 * User
 * File description:
 * UserInterpreter.hpp - Created: 27/09/2021
 */

#ifndef USER_INTERPRETER_HPP
#define USER_INTERPRETER_HPP

#include "IInterpreter.hpp"

namespace network
{
    class UserInterpreter : public IInterpreter {
      public:
        UserInterpreter(DatabaseManager &databaseManager);
        ~UserInterpreter() = default;

        void GET(const TramTCP &tram);
        void POST(const TramTCP &tram);
        void DELETE(const TramTCP &tram);

      private:
        DatabaseManager &_databaseManager;
    };
}; // namespace network

#endif