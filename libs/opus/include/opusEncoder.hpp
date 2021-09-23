/*
** PERSONAL PROJECT, 2021
** opusEncoder
** File description:
** opusEncoder.hpp
*/

#ifndef OPUSENCODER_HPP
#define OPUSENCODER_HPP

#include <opus.h>
#include "../../include/Audio.hpp"
#include "../../include/rawFrameBuffer.hpp"
#include "../../include/compressFrameBuffer.hpp"
#include "../../include/Interfaces/IAudioCompressor.hpp"

namespace OpusCaps
{
    using defaultBuffer = Audio::rawFrameBuffer;
    using compressBuffer = Audio::compressFrameBuffer;

    class opusEncoder : public Audio::IAudioCompressor<compressBuffer, defaultBuffer>
    {
        public:
            opusEncoder();
            ~opusEncoder();
            compressBuffer compress(const defaultBuffer &);
            void compress(compressBuffer &, const defaultBuffer &);

        private:
            OpusEncoder *_encoder;
    };
}

#endif