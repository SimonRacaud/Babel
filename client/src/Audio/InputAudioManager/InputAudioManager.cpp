/*
** PERSONAL PROJECT, 2021
** OutputAudioManager
** File description:
** OutputAudioManager.cpp
*/

#include "InputAudioManager.hpp"

using namespace Audio;

InputAudioManager::InputAudioManager() :
_input(std::make_unique<PortAudioCaps::AudioRecorder>()),
_encoder(std::make_unique<OpusCaps::opusEncoder>())
{
}

InputAudioManager::~InputAudioManager()
{
    this->_input.reset();
    this->_encoder.reset();
}

std::queue<Audio::compressFrameBuffer> InputAudioManager::getFrameBuffer()
{
    std::queue<Audio::compressFrameBuffer> tmp;

    return tmp;
}