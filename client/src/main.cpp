/*
 * EPITECH PROJECT, 2021
 * src
 * File description:
 * main.cpp - Created: 23/09/2021
 */

#include <QApplication>
#include <iostream>

#include "gui/Window/Window.hpp"
#include "NetworkManager/NetworkManager.hpp"
#include "Network/Controller/Controller.hpp"

Network::NetworkManager networkManager;
std::unique_ptr<GUI::Window> window;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    try {
        std::cerr << "Info: will init network connection." << std::endl;
        networkManager.init();
        std::cerr << "Info: will init gui." << std::endl;
        window = std::make_unique<GUI::Window>(app);
        window->show();
        Network::Controller controller(networkManager);
        return app.exec();
    } catch (std::exception const &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Exception: no Exception::what()" << std::endl;
    }
}