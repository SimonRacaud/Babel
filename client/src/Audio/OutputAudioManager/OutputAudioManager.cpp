/*
** PERSONAL PROJECT, 2021
** InputAudioManager
** File description:
** InputAudioManager.cpp
*/

#include "OutputAudioManager.hpp"

using namespace Audio;

OutputAudioManager::OutputAudioManager() :
_output(std::make_unique<PortAudioCaps::AudioStreamer>()),
_decoder(std::make_unique<OpusCaps::opusDecoder>())
{
}

OutputAudioManager::~OutputAudioManager()
{
    this->_output.reset();
    this->_decoder.reset();
}

void OutputAudioManager::setFrameBuffer(std::queue<Audio::compressFrameBuffer> &)
{
}