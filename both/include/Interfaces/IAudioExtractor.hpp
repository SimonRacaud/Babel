/*
** PERSONAL PROJECT, 2021
** IAudioExtractor
** File description:
** IAudioExtractor.hpp
*/

#ifndef IAUDIOEXTRACTOR_HPP
#define IAUDIOEXTRACTOR_HPP

namespace Audio
{
    template<typename encodedBuffer, typename decodedBuffer>
    class IAudioExtractor
    {
        public:
            virtual ~IAudioExtractor() = default;
            virtual decodedBuffer extract(const encodedBuffer &) = 0;
            virtual void extract(decodedBuffer &, const encodedBuffer &) = 0;
    };
}

#endif