/*
 * EPITECH PROJECT, 2021
 * IODevices
 * File description:
 * IODevices.cpp - Created: 22/09/2021
 */

#include "IODevices.hpp"
#include <iostream>

using namespace PortAudioCaps;

IODevices::IODevices(const PaDeviceIndex &inputDevice, const PaDeviceIndex &outputDevice)
    : _inputDevice(inputDevice), _outputDevice(outputDevice)
{
    if (Pa_Initialize() != paNoError)
        throw std::invalid_argument("Failed: Pa_Initialize");
}

IODevices::~IODevices()
{
    if (Pa_Terminate() != paNoError)
        throw std::invalid_argument("Failed: Pa_Terminate");
}

const std::vector<DeviceInfos> IODevices::getInputs() const
{
    std::cout << "devices count: " << Pa_GetDeviceCount() << std::endl;

    std::vector<DeviceInfos> inputDevices;
    const PaDeviceIndex devicesCount = Pa_GetDeviceCount();

    for (PaDeviceIndex i = 0; i < devicesCount; i++) {
        inputDevices.push_back({Pa_GetDeviceInfo(i), i});
    }
    return inputDevices;
}

const std::vector<DeviceInfos> IODevices::getOutputs() const
{
    std::vector<DeviceInfos> inputDevices;
    const PaDeviceIndex devicesCount = Pa_GetDeviceCount();

    for (PaDeviceIndex i = 0; i < devicesCount; i++) {
        inputDevices.push_back({Pa_GetDeviceInfo(i), i});
    }
    return inputDevices;
}

void IODevices::selectInput(const PaDeviceIndex &deviceIndex)
{
    this->_inputDevice = deviceIndex;
}

void IODevices::selectOutput(const PaDeviceIndex &deviceIndex)
{
    this->_outputDevice = deviceIndex;
}

const DeviceInfos IODevices::getSelectedInput() const
{
    return {Pa_GetDeviceInfo(this->_inputDevice), this->_inputDevice};
}

const DeviceInfos IODevices::getSelectedOutput() const
{
    return {Pa_GetDeviceInfo(this->_outputDevice), this->_outputDevice};
}