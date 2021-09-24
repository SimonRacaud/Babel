/*
 * EPITECH PROJECT, 2021
 * examples
 * File description:
 * IODevices.cpp - Created: 23/09/2021
 */

#include "IODevices.hpp"
#include <iostream>

int main()
{
    PortAudioCaps::IODevices ioDevices;
    const std::vector<PortAudioCaps::DeviceInfos> inputs = ioDevices.getInputs();

    for (size_t i = 0; i < inputs.size(); i++) {
        std::cout << "Input device:" << std::endl;
        std::cout << "\tname: \t" << inputs[i].infos->name << std::endl;
        std::cout << "\tindex: \t" << inputs[i].index << std::endl;
        std::cout << "\tdefaultHighInputLatency: \t" << inputs[i].infos->defaultHighInputLatency << std::endl;
        std::cout << "\tdefaultLowInputLatency: \t" << inputs[i].infos->defaultLowInputLatency << std::endl;
        std::cout << "\tdefaultHighOutputLatency: \t" << inputs[i].infos->defaultHighOutputLatency << std::endl;
        std::cout << "\tdefaultLowOutputLatency: \t" << inputs[i].infos->defaultLowOutputLatency << std::endl;
        std::cout << "\tmaxInputChannels: \t" << inputs[i].infos->maxInputChannels << std::endl;
        std::cout << "\tmaxOutputChannels: \t" << inputs[i].infos->maxOutputChannels << std::endl;
    }

    std::cout << "====================================" << std::endl;

    const std::vector<PortAudioCaps::DeviceInfos> outputs = ioDevices.getOutputs();

    for (size_t i = 0; i < outputs.size(); i++) {
        std::cout << "Output device:" << std::endl;
        std::cout << "\tname: \t" << outputs[i].infos->name << std::endl;
        std::cout << "\tindex: \t" << outputs[i].index << std::endl;
        std::cout << "\tdefaultHighInputLatency: \t" << outputs[i].infos->defaultHighInputLatency << std::endl;
        std::cout << "\tdefaultLowInputLatency: \t" << outputs[i].infos->defaultLowInputLatency << std::endl;
        std::cout << "\tdefaultHighOutputLatency: \t" << outputs[i].infos->defaultHighOutputLatency << std::endl;
        std::cout << "\tdefaultLowOutputLatency: \t" << outputs[i].infos->defaultLowOutputLatency << std::endl;
        std::cout << "\tmaxInputChannels: \t" << outputs[i].infos->maxInputChannels << std::endl;
        std::cout << "\tmaxOutputChannels: \t" << outputs[i].infos->maxOutputChannels << std::endl;
    }

    std::cout << "====================================" << std::endl;

    std::cout << "Input device: " << ioDevices.getSelectedInput().infos->name << std::endl;
    std::cout << "Output device: " << ioDevices.getSelectedOutput().infos->name << std::endl;

    return 0;
}