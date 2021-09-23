/*
** PERSONAL PROJECT, 2021
** AudioStreamer
** File description:
** AudioStreamer.hpp
*/

#ifndef AUDIOSTREAMER_HPP
#define AUDIOSTREAMER_HPP

#include <portaudio.h>
#include "IAudioStreamer.hpp"

namespace PortAudioCaps
{
    class AudioStreamer : public Audio::IAudioStreamer<int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *)>
    {
        public:
            AudioStreamer();
            ~AudioStreamer();

            /*
            ** IAudioManager
            */
            void endStreaming();
            void startStreaming();
            bool isStreaming() const;
            void setCallBack(std::function<int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *)>);

            /*
            ** IAudioStreamer
            */
            void setFrame(Audio::rawFrameBuffer);
        
        private:
    };
}

#endif