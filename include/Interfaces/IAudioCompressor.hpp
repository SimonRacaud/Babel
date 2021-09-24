/*
** PERSONAL PROJECT, 2021
** IAudioCompressor
** File description:
** IAudioCompressor.hpp
*/

#ifndef IAUDIOCOMPRESSOR_HPP
#define IAUDIOCOMPRESSOR_HPP

namespace Audio
{
    template<typename encodedBuffer, typename decodedBuffer>
    class IAudioCompressor
    {
        public:
            virtual ~IAudioCompressor() = default;
            virtual encodedBuffer compress(const decodedBuffer &) = 0;
            virtual void compress(encodedBuffer &, const decodedBuffer &) = 0;
    };
}

#endif