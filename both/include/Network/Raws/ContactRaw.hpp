/*
** EPITECH PROJECT , 2021
** Contact
** File description:
** simon
*/

#ifndef CONTACTRAW_HPP
#define CONTACTRAW_HPP

#include <ostream>

struct ContactRaw {
    char username[42];
    char contactName[42];
};

std::ostream &operator<<(std::ostream &stream, const ContactRaw &contactRaw);

#endif // CONTACTRAW_HPP