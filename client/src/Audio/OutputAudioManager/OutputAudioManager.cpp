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
    this->_output->startStreaming();
}

OutputAudioManager::~OutputAudioManager()
{
    this->_output->endStreaming();
    this->_output.reset();
    this->_decoder.reset();
}

void OutputAudioManager::setFrameBuffer(std::queue<Audio::compressFrameBuffer> &data)
{
    Audio::rawFrameBuffer extractedData;

    while (data.size()) {
        extractedData = this->_decoder->extract(data.front());
        data.pop();
        this->_output->setFrame(extractedData);
    }
}