/*
** PERSONAL PROJECT, 2021
** opusDecoder
** File description:
** opusDecoder.hpp
*/

#include <iostream>
#include <stdexcept>
#include "opusDecoder.hpp"

using namespace OpusCaps;

opusDecoder::opusDecoder() : _decoder(NULL)
{
    int err_opus = 0;

    this->_decoder = opus_decoder_create(Audio::SAMPLE_RATE, Audio::NUM_CHANNELS, &err_opus);
    if (err_opus != OPUS_OK || !this->_decoder)
        throw std::invalid_argument("Failed: opus_decoder_create");
}

opusDecoder::~opusDecoder()
{
    opus_decoder_destroy(this->_decoder);
}

defaultBuffer opusDecoder::extract(const compressBuffer &src)
{
    defaultBuffer dest;

    this->extract(dest, src);
    return dest;
}

void opusDecoder::extract(defaultBuffer &dest, const compressBuffer &src)
{
    int bit_decode = 0;

    std::cout << "Extractor: unsigned char -> float" << std::endl;
    dest.data = std::vector<float>(Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(float));
    std::fill(dest.data.begin(), dest.data.end(), 0);
    bit_decode = opus_decode_float(this->_decoder, src.data.data(), src.encodedBit, dest.data.data(), Audio::FRAMES_PER_BUFFER, 0);
    if (bit_decode < 0)
        throw std::invalid_argument("Failed: opus_decode_float");
}