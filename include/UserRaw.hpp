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
};

#endif // USERRAW_HPP