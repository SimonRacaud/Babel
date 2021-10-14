/*
** EPITECH PROJECT , 2021
** Worker
** File description:
** simon
*/

#include "SoundWorker.hpp"

using namespace Network;

extern NetworkManager networkManager;

SoundWorker::SoundWorker(QObject *parent) : QThread(parent)
{
}

void SoundWorker::run()
{
    while (!this->isInterruptionRequested()) {
        try {
            networkManager.streamAudio();
        } catch (std::exception const &e) {
            std::cerr << "An exception occurred with networkManager.streamAudio()" << e.what() << std::endl;
        }
        usleep(1);
    }
}
