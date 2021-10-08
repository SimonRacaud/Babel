/*
** EPITECH PROJECT , 2021
** DatabaseManager
** File description:
** simon
*/

#include "DatabaseManager.hpp"

using namespace sqlite_orm;
using namespace Network;

DatabaseManager::DatabaseManager()
{
    _storage = std::make_unique<Storage>(initStorage("babel.sqlite"));
    auto syncSchemaRes = _storage->sync_schema();
    for (auto &p : syncSchemaRes) {
        std::cerr << "Database sync schema: " << p.first << " " << p.second << std::endl;
    }
}

void DatabaseManager::clearDatabase() const
{
    this->_storage->remove_all<Contact>();
    this->_storage->remove_all<User>();
}

void DatabaseManager::dumpDatabase() const
{
    std::cout << "User List:" << std::endl;
    for (auto &user : _storage->iterate<User>()) {
        std::cout << user.id << "\tusername: " << user.username << "\tip: " << user.ip << "\tport: " << user.port << std::endl;
    }
    std::cout << "Contact List:" << std::endl;
    for (auto &contact : _storage->iterate<Contact>()) {
        std::cout << contact.id << "\tuser id: " << *contact.userId << "\tcontact user id: " << *contact.contactId << std::endl;
    }
}

void DatabaseManager::insertTestDataset()
{
    try {
        this->_storage->replace(User{1, "Arthur.J", "192.168.1.2", 42});
        this->_storage->replace(User{2, "Sullivan.G", "192.168.1.5", 42});
        this->_storage->replace(User{3, "Vincent.A", "192.168.1.10", 42});

        this->_storage->replace(Contact{1, std::make_unique<int>(1), std::make_unique<int>(2)}); // 1 => 2
        this->_storage->replace(Contact{2, std::make_unique<int>(1), std::make_unique<int>(3)}); // 1 => 3
        this->_storage->replace(Contact{3, std::make_unique<int>(3), std::make_unique<int>(1)}); // 3 => 1
        this->_storage->replace(Contact{4, std::make_unique<int>(3), std::make_unique<int>(2)}); // 3 => 2
    } catch (std::exception const &e) {
        std::cerr << "DatabaseManager::insertTestDataset() " << e.what() << std::endl;
    }
}

void DatabaseManager::setUser(std::string const &username, std::string const &ip, std::size_t port)
{
    try {
        this->updateUser(username, ip, port);
    } catch (std::invalid_argument const &e) {
        this->newUser(username, ip, port);
    }
}

User DatabaseManager::getUser(std::string const &username)
{
    auto users = _storage->get_all<User>(where(c(&User::username) = username));

    if (users.size() == 1) {
        return users[0];
    } else {
        throw std::invalid_argument("DatabaseManager::getUser user not found");
    }
}

std::vector<User> DatabaseManager::getContacts(std::string const &username)
{
    const User user = this->getUser(username);
    std::vector<User> result;

    auto rows = _storage->select(columns(&Contact::contactId, &User::username, &User::ip, &User::port),
        join<User>(on(c(&Contact::contactId) == &User::id)),
        where(c(&Contact::userId) == user.id));
    for (auto &row : rows) {
        result.push_back({(*std::get<0>(row)), std::get<1>(row), std::get<2>(row), std::get<3>(row)});
    }
    return result;
}

void DatabaseManager::newContact(std::string const &username, std::string const &contactName)
{
    const User user = this->getUser(username);
    const User contact = this->getUser(contactName);

    Contact data = {0, std::make_unique<int>(user.id), std::make_unique<int>(contact.id)};
    _storage->insert(data);
}

void DatabaseManager::removeContact(std::string const &username, std::string const &contactName)
{
    const User user = this->getUser(username);
    const User contact = this->getUser(contactName);

    _storage->remove_all<Contact>(where(c(&Contact::userId) == user.id and c(&Contact::contactId) == contact.id));
}

void DatabaseManager::newUser(std::string const &username, std::string const &ip, std::size_t port)
{
    User data = {0, username, ip, port};

    this->_storage->insert(data);
}

void DatabaseManager::updateUser(std::string const &username, std::string const &ip, std::size_t port)
{
    User user = this->getUser(username);

    _storage->begin_transaction();
    user.ip = ip;
    user.port = port;
    _storage->update(user);
    _storage->commit();
}