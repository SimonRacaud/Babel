/*
 * EPITECH PROJECT, 2021
 * src
 * File description:
 * UserRaw.cpp - Created: 06/10/2021
 */

#include "UserRaw.hpp"

std::ostream &operator<<(std::ostream &stream, const UserRaw &userRaw)
{
    stream << "UserRaw:" << std::endl;
    stream << "\tip: [" << userRaw.ip << "]" << std::endl;
    stream << "\tport: [" << userRaw.port << "]" << std::endl;
    stream << "\tusername: [" << userRaw.username << "]" << std::endl;
    return stream;
}