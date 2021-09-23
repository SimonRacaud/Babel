/*
** PERSONAL PROJECT, 2021
** AudioRecorder
** File description:
** AudioRecorder.hpp
*/

#ifndef AUDIORECORDER_HPP
#define AUDIORECORDER_HPP

#include <queue>
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
            void setCallBack(std::function<int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *)>);

            /*
            ** IAudioRecorder
            */
            Audio::rawFrameBuffer getFrame();
        
        private:
            PaStream *_stream;
            PaStreamParameters _parameters;
            std::queue<Audio::rawFrameBuffer> _streaming;
            std::function<int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *)> _callback;
    };
}

#endif