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

/*
** #include <iostream>
** #include "InputAudioManager.hpp"
** #include "OutputAudioManager.hpp"
** 
** int main()
** {
**     Audio::OutputAudioManager output;
**     Audio::InputAudioManager input;
** 
**     std::cout << "record" << std::endl;
**     for (size_t i = 0; i < 5; i++)
**         Pa_Sleep(1000);
** 
**     std::cout << "stream" << std::endl;
**     auto tmp = input.getFrameBuffer();
**     output.setFrameBuffer(tmp);
**     for (size_t i = 0; i < 50; i++)
**         Pa_Sleep(100);
** }
*/