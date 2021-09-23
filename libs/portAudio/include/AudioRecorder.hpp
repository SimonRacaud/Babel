/*
** PERSONAL PROJECT, 2021
** AudioRecorder
** File description:
** AudioRecorder.hpp
*/

#ifndef AUDIORECORDER_HPP
#define AUDIORECORDER_HPP

#include <portaudio.h>
#include "IAudioRecorder.hpp"

namespace PortAudioCaps
{
    class AudioRecorder : public Audio::IAudioRecorder<int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *)>
    {
        public:
            AudioRecorder();
            ~AudioRecorder();

            /*
            ** IAudioManager
            */
            void endStreaming();
            void startStreaming();
            bool isStreaming() const;
            void setCallBack(int (*func) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *));
            std::queue<Audio::rawFrameBuffer> &getSampleBuffer();

            /*
            ** IAudioRecorder
            */
            Audio::rawFrameBuffer getFrame();
        
        private:
            PaStream *_stream;
            PaStreamParameters _parameters;
            std::queue<Audio::rawFrameBuffer> _streaming;
            int (*_callback) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);
    };
}

#endif