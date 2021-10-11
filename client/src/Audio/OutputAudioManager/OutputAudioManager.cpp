/*
** PERSONAL PROJECT, 2021
** InputAudioManager
** File description:
** InputAudioManager.cpp
*/

#include <cstring>
#include "OutputAudioManager.hpp"

using namespace Audio;

OutputAudioManager::OutputAudioManager() :
_output(std::make_unique<PortAudioCaps::AudioStreamer>()),
_decoder(std::make_unique<OpusCaps::opusDecoder>())
{
    this->_output->startStreaming();
}

OutputAudioManager::OutputAudioManager(int device) :
_output(std::make_unique<PortAudioCaps::AudioStreamer>()),
_decoder(std::make_unique<OpusCaps::opusDecoder>())
{
    this->_output->setDevice(device);
    this->_output->startStreaming();
}

OutputAudioManager::~OutputAudioManager()
{
    this->_output->endStreaming();
    this->_output.reset();
    this->_decoder.reset();
}

void OutputAudioManager::setFrameBuffer(std::queue<Audio::compressFrameBuffer> &data, bool merging)
{
    Audio::rawFrameBuffer extractedData;

    if (!merging) {
        while (data.size()) {
            extractedData = this->_decoder->extract(data.front());
            data.pop();
            this->_output->setFrame(extractedData);
        }
    } else {
        Audio::rawFrameBuffer mergingData;

        mergingData.data = std::vector<float>(Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(float));
        std::memset(mergingData.data.data(), 0, Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(float));
        while (data.size()) {
            extractedData = this->_decoder->extract(data.front());
            data.pop();
            for (size_t i = 0; i < extractedData.data.size(); i++) {
                mergingData.data[i] += extractedData.data[i];
            }
        }
        this->_output->setFrame(mergingData, true);
    }
}