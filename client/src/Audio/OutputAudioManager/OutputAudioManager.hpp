/*
** PERSONAL PROJECT, 2021
** OutputAudioManager
** File description:
** OutputAudioManager.hpp
*/

#ifndef OUTPUTAUDIOMANAGER_HPP
#define OUTPUTAUDIOMANAGER_HPP

#include <memory>
#include "opusDecoder.hpp"
#include "AudioStreamer.hpp"
#include "compressFrameBuffer.hpp"

namespace Audio
{
    class OutputAudioManager
    {
        using defaultBuffer = Audio::rawFrameBuffer;
        using compressBuffer = Audio::compressFrameBuffer;
        using callBackType = int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);
        public:
            OutputAudioManager();
            ~OutputAudioManager();

            void setFrameBuffer(std::queue<Audio::compressFrameBuffer> &);

        private:
            std::unique_ptr<Audio::IAudioStreamer<callBackType>> _output;
            std::unique_ptr<Audio::IAudioExtractor<compressBuffer, defaultBuffer>> _decoder;
    };
}

#endif