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
    this->_input->startStreaming();
}

InputAudioManager::~InputAudioManager()
{
    this->_input->endStreaming();
    this->_input.reset();
    this->_encoder.reset();
}

std::queue<Audio::compressFrameBuffer> InputAudioManager::getFrameBuffer()
{
    std::queue<Audio::compressFrameBuffer> tmp;

    try {
        while (1)
            tmp.push(this->_encoder->compress(this->_input->getFrame()));
    } catch ([[maybe_unused]] const std::invalid_argument &e) {
    }
    return tmp;
}