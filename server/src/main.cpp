/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** Server side of Babel
*/

#include <iostream>

#include "API.hpp"
#include "AsioServerTCP.hpp"
#include "Network.hpp"
#include "server.hpp"
#include "utils.hpp"

static void init(Network::DatabaseManager &database, bool &serverLoop)
{
    Network::AsioServerTCP<Network::BUFFER_SIZE> serv(Network::PORT_MAIN_SERVER);
    Network::API<Network::BUFFER_SIZE> api(serv, database);

    signalManager(SIGINT, serverLoop);
    signalManager(SIGQUIT, serverLoop);
    serv.runAsync();
    while (serverLoop) {
        auto recvData = serv.receiveAny();

        if (std::get<1>(recvData) > 0)
            api(std::get<0>(recvData), std::get<2>(recvData), std::get<3>(recvData));
    }
    serv.stopRunAsync();
}

int main()
{
    bool serverLoop = true;

    try {
        Network::DatabaseManager database;

        init(database, serverLoop);

    } catch (const std::out_of_range &e) {
        std::cerr << "out_of_range: " << e.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::invalid_argument &e) {
        std::cerr << "invalid_argument: " << e.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::system_error &e) {
        std::cerr << "out_of_range: " << e.what() << ", " << e.code() << std::endl;
        return EXIT_ERROR;
    } catch (const std::runtime_error &e) {
        std::cerr << "runtime_error: " << e.what() << std::endl;
        return EXIT_ERROR;
    } catch (const std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
        return EXIT_ERROR;
    } catch (...) {
        std::cerr << "catch error" << std::endl;
        return EXIT_ERROR;
    }

    std::cout << "Server stopped" << std::endl;
    return EXIT_SUCCESS;
}