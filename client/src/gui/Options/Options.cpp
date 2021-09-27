/*
** EPITECH PROJECT , 2021
** Options
** File description:
** simon
*/

#include "Options.hpp"

using namespace GUI;

Options::Options(IWindow &window, PortAudioCaps::IODevices &ioDevices): _mainWindow(window), _ioDevices(ioDevices)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QVBoxLayout *inputLayout = new QVBoxLayout;
    QVBoxLayout *outputLayout = new QVBoxLayout;
    QGroupBox *inputDeviceBox = new QGroupBox("Input Devices");
    QGroupBox *outputDeviceBox = new QGroupBox("Output Devices");
    _inputList = new QListWidget;
    _outputList = new QListWidget;

    mainLayout->addWidget(inputDeviceBox);
    mainLayout->addWidget(outputDeviceBox);
    inputDeviceBox->setLayout(inputLayout);
    outputDeviceBox->setLayout(outputLayout);
    inputLayout->addWidget(_inputList);
    outputLayout->addWidget(_outputList);

    this->initDeviceLists();
    QObject::connect(_inputList, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectInput()));
    QObject::connect(_outputList, SIGNAL(itemSelectionChanged()), this, SLOT(slotSelectOutput()));
}

void Options::closeEvent(QCloseEvent *)
{
    this->_mainWindow.hideOptions();
}

void Options::initDeviceLists()
{
    _inputDeviceData = _ioDevices.getInputs();
    _outputDeviceData = _ioDevices.getOutputs();

    _inputList->clear();
    for (PortAudioCaps::DeviceInfos &device : _inputDeviceData) {
        _inputList->addItem(device.infos->name);
    }
    _outputList->clear();
    _outputList->addItem("Default");
    for (PortAudioCaps::DeviceInfos &device : _outputDeviceData) {
        _outputList->addItem(device.infos->name);
    }
}

void Options::slotSelectInput()
{
    QListWidgetItem *item = _inputList->currentItem();
    QString selection = item->text();

    auto deviceIt = std::find_if(_inputDeviceData.begin(),
        _inputDeviceData.end(), [selection](auto &item) { return selection == item.infos->name; });

    if (deviceIt == _inputDeviceData.end()) {
        std::cerr << "Options::slotSelectInput() : selected device not found." << std::endl;
    } else {
        std::cerr << "Options::slotSelectInput() : select device " << ((int)deviceIt->index) << std::endl;
        this->_ioDevices.selectInput(deviceIt->index);
    }
}

void Options::slotSelectOutput()
{
    QListWidgetItem *item = _outputList->currentItem();
    QString selection = item->text();

    if (selection == "Default") {
        this->_ioDevices.setDefaultOutput();
    } else {
        auto deviceIt = std::find_if(_outputDeviceData.begin(),
            _outputDeviceData.end(), [selection](auto &item) { return selection == item.infos->name; });

        if (deviceIt == _outputDeviceData.end()) {
            std::cerr << "Options::slotSelectOutput() : selected device [" << selection.toStdString() << "] not found." << std::endl;
        } else {
            std::cerr << "Options::slotSelectOutput() : select device " << ((int)deviceIt->index) << std::endl;
            this->_ioDevices.selectOutput(deviceIt->index);
        }
    }
}