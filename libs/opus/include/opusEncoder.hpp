/*
** PERSONAL PROJECT, 2021
** opusEncoder
** File description:
** opusEncoder.hpp
*/

#ifndef OPUSENCODER_HPP
#define OPUSENCODER_HPP

#include <opus.h>
#include "Audio.hpp"
#include "Interfaces/IAudioCompressor.hpp"
#include "compressFrameBuffer.hpp"
#include "rawFrameBuffer.hpp"

namespace OpusCaps
{
    using defaultBuffer = Audio::rawFrameBuffer;
    using compressBuffer = Audio::compressFrameBuffer;

    class opusEncoder : public Audio::IAudioCompressor<compressBuffer, defaultBuffer> {
      public:
        opusEncoder();
        ~opusEncoder();
        compressBuffer compress(const defaultBuffer &);
        void compress(compressBuffer &, const defaultBuffer &);

      private:
        OpusEncoder *_encoder;
    };
} // namespace OpusCaps

#endif