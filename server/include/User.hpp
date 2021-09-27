/*
** EPITECH PROJECT , 2021
** User
** File description:
** simon
*/

#ifndef USER_HPP
#define USER_HPP

#include <string>

struct User {
    int id;
    std::string username;
    std::string ip;
    std::size_t port;
};

struct UserRaw {
    char username[42];
    char ip[15];
    uint port;
}

#endif // USER_HPP
