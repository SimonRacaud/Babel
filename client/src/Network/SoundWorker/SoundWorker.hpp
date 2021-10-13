/*
** EPITECH PROJECT , 2021
** Worker
** File description:
** simon
*/

#ifndef SOUND_WORKER_HPP
#define SOUND_WORKER_HPP

#include <QWidget>
#include <QThread>
#include <vector>
#include "NetworkManager/NetworkManager.hpp"
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

namespace Network
{
    class SoundWorker : public QThread {
        Q_OBJECT
      public:
        SoundWorker(QObject *parent = nullptr);
        virtual ~SoundWorker() = default;

      public:
        void run() override;
    };
}

#endif // SOUND_WORKER_HPP
