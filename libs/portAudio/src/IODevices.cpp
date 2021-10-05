/*
 * EPITECH PROJECT, 2021
 * IODevices
 * File description:
 * IODevices.cpp - Created: 22/09/2021
 */

#include "IODevices.hpp"
#include <algorithm>
#include <iostream>
#include "utils.hpp"

using namespace PortAudioCaps;

IODevices::IODevices()
{
    if (Pa_Initialize() != paNoError)
        throw std::invalid_argument("Failed: Pa_Initialize");

    this->_inputDevice = Pa_GetDefaultInputDevice();
    this->_outputDevice = Pa_GetDefaultOutputDevice();
}

IODevices::~IODevices()
{
    if (Pa_Terminate() != paNoError)
        throw std::invalid_argument("Failed: Pa_Terminate");
}

const std::vector<DeviceInfos> IODevices::getInputs() const
{
    std::vector<DeviceInfos> inputDevices;
    const PaDeviceIndex devicesCount = Pa_GetDeviceCount();

    for (PaDeviceIndex i = 0; i < devicesCount; i++) {
        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);

        if (!deviceInfo)
            throw std::invalid_argument("Failed: getInputs => Pa_GetDeviceInfo(" + myToString(i) + ")");
        if (deviceInfo->maxInputChannels > 0)
            inputDevices.push_back({deviceInfo, i});
    }
    return inputDevices;
}

const std::vector<DeviceInfos> IODevices::getOutputs() const
{
    std::vector<DeviceInfos> outputDevices;
    const PaDeviceIndex devicesCount = Pa_GetDeviceCount();

    for (PaDeviceIndex i = 0; i < devicesCount; i++) {
        const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(i);

        if (!deviceInfo)
            throw std::invalid_argument("Failed: getOutputs => Pa_GetDeviceInfo(" + myToString(i) + ")");
        if (deviceInfo->maxOutputChannels > 0)
            outputDevices.push_back({deviceInfo, i});
    }
    return outputDevices;
}

void IODevices::selectInput(const PaDeviceIndex &deviceIndex)
{
    if (deviceIndex == this->_inputDevice)
        return;
    const std::vector<DeviceInfos> &inputDevices = this->getInputs();
    const auto &result = std::find_if(inputDevices.begin(), inputDevices.end(), [deviceIndex](const DeviceInfos &deviceInfos) {
        return deviceInfos.index == deviceIndex;
    });

    if (result == inputDevices.end())
        throw std::invalid_argument("Failed: selectInput => " + myToString(deviceIndex) + " isn't an input device");

    this->_inputDevice = deviceIndex;
}

void IODevices::selectOutput(const PaDeviceIndex &deviceIndex)
{
    if (deviceIndex == this->_outputDevice)
        return;
    const std::vector<DeviceInfos> &outputDevices = this->getOutputs();
    const auto &result = std::find_if(outputDevices.begin(), outputDevices.end(), [deviceIndex](const DeviceInfos &deviceInfos) {
        return deviceInfos.index == deviceIndex;
    });

    if (result == outputDevices.end())
        throw std::invalid_argument("Failed: selectOutput => " + myToString(deviceIndex) + " isn't an output device");

    this->_outputDevice = deviceIndex;
}

void IODevices::setDefaultInput()
{
    this->_inputDevice = Pa_GetDefaultInputDevice();
}

void IODevices::setDefaultOutput()
{
    this->_outputDevice = Pa_GetDefaultOutputDevice();
}

const DeviceInfos IODevices::getSelectedInput() const
{
    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(this->_inputDevice);

    if (!deviceInfo)
        throw std::invalid_argument("Failed: getSelectedInput => Pa_GetDeviceInfo(" + myToString(this->_inputDevice) + ")");
    return {deviceInfo, this->_inputDevice};
}

const DeviceInfos IODevices::getSelectedOutput() const
{
    const PaDeviceInfo *deviceInfo = Pa_GetDeviceInfo(this->_outputDevice);

    if (!deviceInfo)
        throw std::invalid_argument("Failed: getSelectedOutput => Pa_GetDeviceInfo(" + myToString(this->_outputDevice) + ")");
    return {deviceInfo, this->_outputDevice};
}