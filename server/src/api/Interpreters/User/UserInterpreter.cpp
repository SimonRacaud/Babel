/*
 * EPITECH PROJECT, 2021
 * User
 * File description:
 * UserInterpreter.cpp - Created: 27/09/2021
 */

#include <stdexcept>

#include "User.hpp"
#include "UserInterpreter.hpp"

using namespace network;

UserInterpreter::UserInterpreter(DatabaseManager &databaseManager) : _databaseManager(databaseManager)
{
}

void UserInterpreter::GET(const TramTCP &tram)
{
    const UserRaw user = static_cast<UserRaw>(tram.list);

    this->_databaseManager.getUser(user.username);
}

void UserInterpreter::POST(const TramTCP &tram)
{
    const UserRaw user = static_cast<UserRaw>(tram.list);

    this->_databaseManager.setUser(user.username, user.ip, user.port);
}

void UserInterpreter::DELETE(const TramTCP &tram)
{
    throw std::runtime_error("Method not override");
}