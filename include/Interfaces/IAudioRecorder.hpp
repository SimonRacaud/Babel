/*
** PERSONAL PROJECT, 2021
** IAudioRecorder
** File description:
** IAudioRecorder.hpp
*/

#ifndef IAUDIORECORDER_HPP
#define IAUDIORECORDER_HPP

#include "IAudioManager.hpp"
#include "rawFrameBuffer.hpp"

namespace Audio
{
    template <typename callbackProto>
    class IAudioRecorder : public IAudioManager<callbackProto, rawFrameBuffer>
    {
        public:
            virtual ~IAudioRecorder() = default;

            /*
            ** IAudioManager
            */
            virtual void endStreaming() = 0;
            virtual void startStreaming() = 0;
            virtual bool isStreaming() const = 0;
            virtual void setCallBack(callbackProto) = 0;
            virtual std::queue<rawFrameBuffer> &getSampleBuffer() = 0;

            /*
            ** IAudioRecorder
            */
            virtual rawFrameBuffer getFrame() = 0;
    };
}

#endif