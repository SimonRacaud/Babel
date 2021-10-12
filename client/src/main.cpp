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


/*#include <cstring>
#include <iostream>
#include "UDPAudio/UDPAudio.hpp"

static void sending()
{
    UDPAudio core(8080);
    UserRaw user = {"cmoi", "127.0.0.1", 8081};

    core.addUser(user);
    while (1) {
        //std::cout << "streaming" << std::endl;
        core.streamAudio();
    }
}

static void receiving()
{
    Network::AsioConnectionUDP<Network::BUFFER_SIZE> in(8081);

    while (1) {
        //std::cout << "respond" << std::endl;
        auto tmp = in.receive("127.0.0.1", 8080);
        in.send(tmp.first, "127.0.0.1", 8080);
    }
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (std::strcmp(av[1], "send") == 0) {
        sending();
    } else if (std::strcmp(av[1], "recv") == 0) {
        receiving();
    } else {
        return 84;
    }
    return 0;
}*/