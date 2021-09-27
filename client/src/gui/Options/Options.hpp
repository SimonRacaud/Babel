/*
** EPITECH PROJECT , 2021
** Options
** File description:
** simon
*/

#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QObject>
#include <QCloseEvent>
#include <iostream>
#include <QApplication>
#include <QListWidget>
#include <QGroupBox>
#include <algorithm>

#include "IWindow.hpp"
#include "IODevices.hpp"

namespace GUI
{
    class Options : public QWidget {
        Q_OBJECT

      public:
        Options(IWindow &window, PortAudioCaps::IODevices &ioDevices);
        virtual ~Options() = default;

      private slots:
        void closeEvent(QCloseEvent *event);
        void slotSelectInput();
        void slotSelectOutput();

      private:
        void initDeviceLists();


      private:
        IWindow &_mainWindow;
        PortAudioCaps::IODevices &_ioDevices;

        QListWidget *_inputList;
        QListWidget *_outputList;

        std::vector<PortAudioCaps::DeviceInfos> _inputDeviceData;
        std::vector<PortAudioCaps::DeviceInfos> _outputDeviceData;
    };
}

#endif // OPTIONS_HPP
