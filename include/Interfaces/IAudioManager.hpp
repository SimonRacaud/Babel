/*
** PERSONAL PROJECT, 2021
** IAudioManager
** File description:
** IAudioManager.hpp
*/

#ifndef IAUDIOMANAGER_HPP
#define IAUDIOMANAGER_HPP

#include <queue>
#include <functional>

namespace Audio
{
    template <typename callbackProto, typename sampleBuffer>
    class IAudioManager
    {
        public:
            virtual ~IAudioManager() = default;

            virtual void endStreaming() = 0;
            virtual void startStreaming() = 0;
            virtual bool isStreaming() const = 0;
            virtual void setCallBack(std::function<callbackProto>) = 0;
            virtual std::queue<sampleBuffer> &getSampleBuffer() = 0;
    };
}

#endif