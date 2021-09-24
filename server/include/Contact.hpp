/*
** EPITECH PROJECT , 2021
** Contact
** File description:
** simon
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <memory>

struct Contact {
    int id;
    std::unique_ptr<int> userId;    // must map to User::id
    std::unique_ptr<int> contactId; // must map to User::id
};

#endif // CONTACT_HPP
