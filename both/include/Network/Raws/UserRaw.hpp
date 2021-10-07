/*
** EPITECH PROJECT , 2021
** User
** File description:
** simon
*/

#ifndef USERRAW_HPP
#define USERRAW_HPP

#include "utils.hpp"

#define USERNAME_SIZE 42
#define IP_SIZE       15

struct __attribute__((packed)) /* todo #define for windows compilation */ UserRaw {
    char username[USERNAME_SIZE];
    char ip[IP_SIZE];
    size_t port;

    bool operator==(const UserRaw &RValue) const
    {
        return this->port == RValue.port && string(this->ip) == string(RValue.ip) && string(this->username) == string(RValue.username);
    }
};

std::ostream &operator<<(std::ostream &stream, const UserRaw &userRaw);

#endif // USERRAW_HPP