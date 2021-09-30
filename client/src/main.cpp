/*
 * EPITECH PROJECT, 2021
 * src
 * File description:
 * main.cpp - Created: 23/09/2021
 */

/*
#include <QApplication>
#include "gui/Window/Window.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GUI::Window win(app);
    win.show();

    return app.exec();
}
*/

#include <cstring>
#include <iostream>
#include "UDPAudio/UDPAudio.hpp"

int main(int ac, char **av)
{
    size_t input = 0;
    size_t output = 0;
    UserRaw user = {"cmoi", "127.0.0.1", 8082};

    if (ac != 2)
        return 84;
    if (std::strcmp(av[1], "send") == 0) {
        input = 8080;
        output = 8081;
        user.port = 8080;
    } else if (std::strcmp(av[1], "recv") == 0) {
        input = 8081;
        output = 8080;
        user.port = 8081;
    } else {
        return 84;
    }
    UDPAudio core(input, output);
    core.addUser(user);
    while (1)
        core.streamAudio();
    return 0;
}