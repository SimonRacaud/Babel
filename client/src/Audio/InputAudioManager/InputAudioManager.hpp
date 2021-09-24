/*
** PERSONAL PROJECT, 2021
** InputAudioManager
** File description:
** InputAudioManager.hpp
*/

#ifndef INPUTAUDIOMANAGER_HPP
#define INPUTAUDIOMANAGER_HPP

#include <memory>
#include "opusEncoder.hpp"
#include "AudioRecorder.hpp"
#include "compressFrameBuffer.hpp"

namespace Audio
{
    class InputAudioManager
    {
        using defaultBuffer = Audio::rawFrameBuffer;
        using compressBuffer = Audio::compressFrameBuffer;
        using callBackType = int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);
        public:
            InputAudioManager();
            ~InputAudioManager();

            std::queue<Audio::compressFrameBuffer> getFrameBuffer();

        private:
            std::unique_ptr<Audio::IAudioRecorder<callBackType>> _input;
            std::unique_ptr<Audio::IAudioCompressor<compressBuffer, defaultBuffer>> _encoder;
    };
}

#endif