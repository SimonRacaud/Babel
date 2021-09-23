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
        IODevices(const PaDeviceIndex &inputDevice = Pa_GetDefaultInputDevice(),
            const PaDeviceIndex &outputDevice = Pa_GetDefaultOutputDevice());
        ~IODevices();

        const std::vector<DeviceInfos> getInputs() const;
        const std::vector<DeviceInfos> getOutputs() const;

        void selectInput(const PaDeviceIndex &deviceIndex);
        void selectOutput(const PaDeviceIndex &deviceIndex);

        const DeviceInfos getSelectedInput() const;
        const DeviceInfos getSelectedOutput() const;

      private:
        PaDeviceIndex _inputDevice = -1;
        PaDeviceIndex _outputDevice = -1;
    };

}; // namespace PortAudioCaps

#endif