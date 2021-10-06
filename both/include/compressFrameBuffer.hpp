/*
** PERSONAL PROJECT, 2021
** compressFrameBuffer
** File description:
** compressFrameBuffer.hpp
*/

#ifndef COMPRESSFRAMEBUFFER_HPP
#define COMPRESSFRAMEBUFFER_HPP

#include <vector>

namespace Audio
{
    typedef struct compressFrameBuffer_s
    {
        std::vector<unsigned char> data;
        int encodedBit;
    } compressFrameBuffer;
}

#endif