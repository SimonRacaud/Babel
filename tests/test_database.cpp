/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** Server side of Babel
*/

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include "database/DatabaseManager.hpp"

int main(void)
{
    // create/init
    network::DatabaseManager db;
    db.clearDatabase();

    // login
    db.setUser("hello.w", "192.168.1.1", 4242);
    db.setUser("user.B", "192.168.513.1", 42);
    // add contact
    db.newContact("hello.w", "user.B");

    db.dumpDatabase();

    // get contact list
    auto contact = db.getContacts("hello.w");
    std::cout << "contact size : " << contact.size() << "\n";

    // get user data
    db.getUser("hello.w");

    try {
        auto contact2 = db.getContacts("x"); // undefined user
        std::cout << "contact size : " << contact2.size() << "\n";
    } catch (std::exception const &e) {
        std::cerr << e.what() << "\n";
    }
    try {
        db.getUser("ee"); // undefined user
    } catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
    }
    // remove contact
    db.removeContact("hello.w", "user.B");
    db.dumpDatabase();

    db.removeContact("hello.w", "user.B"); // no contact to delete, nothing happen
    return 0;
}
