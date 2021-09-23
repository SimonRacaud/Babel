/*
 * EPITECH PROJECT, 2021
 * src
 * File description:
 * main.cpp - Created: 23/09/2021
 */

#include <QApplication>
#include "gui/Window/Window.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GUI::Window win;
    win.show();

    return app.exec();
}