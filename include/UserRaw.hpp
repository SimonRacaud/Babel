/*
** EPITECH PROJECT , 2021
** User
** File description:
** simon
*/

#ifndef USERRAW_HPP
#define USERRAW_HPP

#include "utils.hpp"

struct UserRaw {
    char username[42];
    char ip[15];
    size_t port;

    bool operator==(const UserRaw &RValue) const
    {
        return this->port == RValue.port && string(this->ip) == string(RValue.ip) && string(this->username) == string(RValue.username);
    }
};

#endif // USERRAW_HPP