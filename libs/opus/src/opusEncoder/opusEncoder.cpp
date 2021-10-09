/*
** PERSONAL PROJECT, 2021
** opusEncoder
** File description:
** opusEncoder.hpp
*/

#include <iostream>
#include <stdexcept>
#include "opusEncoder.hpp"

using namespace OpusCaps;

opusEncoder::opusEncoder() : _encoder(NULL)
{
    int err_opus = 0;

    this->_encoder = opus_encoder_create(Audio::SAMPLE_RATE, Audio::NUM_CHANNELS, OPUS_APPLICATION_VOIP, &err_opus);
    if (err_opus != OPUS_OK || !this->_encoder)
        throw std::invalid_argument("Failed: opus_encoder_create");
}

opusEncoder::~opusEncoder()
{
    opus_encoder_destroy(this->_encoder);
}

compressBuffer opusEncoder::compress(const defaultBuffer &src)
{
    compressBuffer dest;

    this->compress(dest, src);
    return dest;
}

void opusEncoder::compress(compressBuffer &dest, const defaultBuffer &src)
{
    //std::cout << "Compressor: float -> unsigned char" << std::endl;
    dest.data = std::vector<unsigned char>(Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(unsigned char));
    std::fill(dest.data.begin(), dest.data.end(), 0);
    dest.encodedBit = opus_encode_float(this->_encoder, src.data.data(), Audio::FRAMES_PER_BUFFER, dest.data.data(), Audio::FRAMES_PER_BUFFER * Audio::NUM_CHANNELS);
    if (dest.encodedBit < 0)
        throw std::invalid_argument("Failed: opus_encode_float");
    dest.data.resize(dest.encodedBit);
}