/*
** PERSONAL PROJECT, 2021
** rawFrameBuffer
** File description:
** rawFrameBuffer.hpp
*/

#ifndef RAWFRAMEBUFFER_HPP
#define RAWFRAMEBUFFER_HPP

#include <vector>

namespace Audio
{
    typedef struct rawFrameBuffer_s
    {
        std::vector<float> data;
    } rawFrameBuffer;
}

#endif