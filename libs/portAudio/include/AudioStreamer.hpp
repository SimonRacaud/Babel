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
            void setCallBack(int (*func) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *));
            std::queue<Audio::rawFrameBuffer> &getSampleBuffer();

            /*
            ** IAudioStreamer
            */
            void setFrame(Audio::rawFrameBuffer);

        private:
            static int defaultCallBack(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);
        
        private:
            PaStream *_stream;
            PaStreamParameters _parameters;
            std::queue<Audio::rawFrameBuffer> _streaming;
            int (*_callback) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);
    };
}

#endif