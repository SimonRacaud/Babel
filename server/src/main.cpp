/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** Server side of Babel
*/

#include <iostream>

#include "API.hpp"
#include "AsioServerTCP.hpp"
#include "utils.hpp"

static void init(Network::DatabaseManager &database)
{
    Network::AsioServerTCP<T_PACKETSIZE> serv(8080);
    Network::API<T_PACKETSIZE> api(serv, database);

    while (true) {
        auto recvData = serv.receiveAny();

        api(std::get<0>(recvData), std::get<2>(recvData), std::get<3>(recvData));
    }
}

int main()
{
    try {
        Network::DatabaseManager database;

        init(database);
    } catch (...) {
        std::cerr << "catch error" << std::endl;
        return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}