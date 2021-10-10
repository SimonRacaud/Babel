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
    const int MAX_FRAME_IN = 1000;
    class AudioRecorder : public Audio::IAudioRecorder<int (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *)>
    {
        public:
            AudioRecorder();
            ~AudioRecorder();

            /*
            ** IAudioManager
            */
            void setDevice(int);
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
            static int defaultCallBack(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);
        
        private:
            PaStream *_stream;
            PaStreamParameters _parameters;
            std::queue<Audio::rawFrameBuffer> _streaming;
            int (*_callback) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);
    };
}

#endif