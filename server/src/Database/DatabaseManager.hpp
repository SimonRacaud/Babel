/*
** EPITECH PROJECT , 2021
** DatabaseManager
** File description:
** simon
*/

#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sqlite_orm/sqlite_orm.h>

#include "Contact.hpp"
#include "User.hpp"

namespace Network
{
    inline auto initStorage(const std::string &path)
    {
        using namespace sqlite_orm;
        return make_storage(path,
            make_table("users",
                make_column("id", &User::id, autoincrement(), primary_key()),
                make_column("username", &User::username),
                make_column("ip", &User::ip),
                make_column("port", &User::port)),
            make_table("contacts",
                make_column("id", &Contact::id, autoincrement(), primary_key()),
                make_column("users_id", &Contact::userId),
                make_column("contact_id", &Contact::contactId),
                foreign_key(&Contact::userId).references(&User::id),
                foreign_key(&Contact::contactId).references(&User::id)));
    }
    using Storage = decltype(initStorage(""));

    class DatabaseManager {
      public:
        DatabaseManager();
        virtual ~DatabaseManager() = default;

        void setUser(std::string const &username, std::string const &ip, std::size_t port);
        User getUser(std::string const &username);
        std::vector<User> getContacts(std::string const &username);
        void newContact(std::string const &username, std::string const &contactName);
        void removeContact(std::string const &username, std::string const &contactName);

        void clearDatabase() const;
        void insertTestDataset();
        void dumpDatabase() const;

      private:
        void newUser(std::string const &username, std::string const &ip, std::size_t port);
        void updateUser(std::string const &username, std::string const &ip, std::size_t port);

        std::unique_ptr<Storage> _storage;
    };
} // namespace Network

#endif // DATABASEMANAGER_HPP
