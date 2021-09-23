/*
** PERSONAL PROJECT, 2021
** opusDecoder
** File description:
** opusDecoder.hpp
*/

#ifndef OPUSDECODER_HPP
#define OPUSDECODER_HPP

#include <opus.h>
#include "Audio.hpp"
#include "Interfaces/IAudioExtractor.hpp"
#include "compressFrameBuffer.hpp"
#include "rawFrameBuffer.hpp"

namespace OpusCaps
{
    using defaultBuffer = Audio::rawFrameBuffer;
    using compressBuffer = Audio::compressFrameBuffer;

    class opusDecoder : public Audio::IAudioExtractor<compressBuffer, defaultBuffer> {
      public:
        opusDecoder();
        ~opusDecoder();
        defaultBuffer extract(const compressBuffer &);
        void extract(defaultBuffer &, const compressBuffer &);

      private:
        OpusDecoder *_decoder;
    };
} // namespace OpusCaps

#endif