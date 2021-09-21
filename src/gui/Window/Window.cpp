/*
** EPITECH PROJECT , 2021
** Window
** File description:
** simon
*/

#include "Window.hpp"

using namespace GUI;

Window::Window()
{
    this->setWindowTitle("Babel");
    QMdiArea *centerArea = new QMdiArea;
    this->setCentralWidget(centerArea);

    this->_test = new QPushButton("Hello World", centerArea);
}