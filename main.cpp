
/*
** PERSONAL PROJECT, 2021
** opusDecoder
** File description:
** opusDecoder.hpp
*/

#include "opusDecoder.hpp"
#include "opusEncoder.hpp"

int main()
{
    Audio::rawFrameBuffer Frame;
    Audio::compressFrameBuffer compressed;

    Frame.data = std::vector<float>(Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(float));
    std::fill(Frame.data.begin(), Frame.data.end(), 0);

    compressed.data = std::vector<unsigned char>(Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(unsigned char));
    std::fill(compressed.data.begin(), compressed.data.end(), 0);
    compressed.encodedBit = 0;

    OpusCaps::opusDecoder decode;
    OpusCaps::opusEncoder encode;

    Frame = decode.extract(compressed);
    compressed = encode.compress(Frame);
    return 0;
}