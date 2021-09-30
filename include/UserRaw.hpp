/*
** EPITECH PROJECT , 2021
** User
** File description:
** simon
*/

#ifndef USERRAW_HPP
#define USERRAW_HPP

#include <cstddef>

struct UserRaw {
    char username[42];
    char ip[15];
    std::size_t port;

    bool operator==(const UserRaw &Rvalue) const
    {
        return this->port == Rvalue.port && this->ip == Rvalue.ip && this->username == Rvalue.username;
    }
};

#endif // USERRAW_HPP