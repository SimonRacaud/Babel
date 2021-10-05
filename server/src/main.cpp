/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** Server side of Babel
*/

#include <iostream>

#include "API.hpp"
#include "AsioServerTCP.hpp"
#include "server.hpp"
#include "utils.hpp"

static void init(Network::DatabaseManager &database, bool &serverLoop)
{
    Network::AsioServerTCP<T_PACKETSIZE> serv(8080);
    Network::API<T_PACKETSIZE> api(serv, database);

    signalManager(SIGINT, serverLoop);
    signalManager(SIGQUIT, serverLoop);
    while (serverLoop) {
        // serv.runOneAction();
        auto recvData = serv.receiveAny();

        if (std::get<1>(recvData) > 0)
            api(std::get<0>(recvData), std::get<2>(recvData), std::get<3>(recvData));
    }
}

int main()
{
    bool serverLoop = true;

    try {
        Network::DatabaseManager database;

        init(database, serverLoop);
    } catch (...) {
        std::cerr << "catch error" << std::endl;
        return EXIT_ERROR;
    }

    std::cout << "Server stopped" << std::endl;
    return EXIT_SUCCESS;
}