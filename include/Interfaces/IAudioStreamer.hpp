/*
** PERSONAL PROJECT, 2021
** IAudioStreamer
** File description:
** IAudioStreamer.hpp
*/

#ifndef IAUDIOSTREAMER_HPP
#define IAUDIOSTREAMER_HPP

#include "IAudioManager.hpp"
#include "rawFrameBuffer.hpp"

namespace Audio
{
    template <typename callbackProto>
    class IAudioStreamer : public IAudioManager<callbackProto>
    {
        public:
            virtual ~IAudioStreamer() = default;

            /*
            ** IAudioManager
            */
            virtual void endStreaming() = 0;
            virtual void startStreaming() = 0;
            virtual bool isStreaming() const = 0;
            virtual void setCallBack(std::function<callbackProto>) = 0;

            /*
            ** IAudioRecorder
            */
            virtual void setFrame(rawFrameBuffer) = 0;
    };
}

#endif