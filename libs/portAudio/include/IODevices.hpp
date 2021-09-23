/*
 * EPITECH PROJECT, 2021
 * IODevices
 * File description:
 * IODevices.hpp - Created: 22/09/2021
 */

#ifndef IO_DEVICES_HPP
#define IO_DEVICES_HPP

#include <portaudio.h>
#include <vector>

namespace PortAudioCaps
{
    struct DeviceInfos {
        const PaDeviceInfo *infos;
        PaDeviceIndex index;
    };

    class IODevices {
      public:
        IODevices();
        ~IODevices();

        const std::vector<DeviceInfos> getInputs() const;
        const std::vector<DeviceInfos> getOutputs() const;
        const DeviceInfos getSelectedInput() const;
        const DeviceInfos getSelectedOutput() const;

        void selectInput(const PaDeviceIndex &deviceIndex);
        void selectOutput(const PaDeviceIndex &deviceIndex);
        void setDefaultInput();
        void setDefaultOutput();

      private:
        PaDeviceIndex _inputDevice = -1;
        PaDeviceIndex _outputDevice = -1;
    };

}; // namespace PortAudioCaps

#endif