/*
** PERSONAL PROJECT, 2021
** opusDecoder
** File description:
** opusDecoder.hpp
*/

#include <memory>
#include <cstring>
#include <iostream>
#include "AudioStreamer.hpp"
#include "AudioRecorder.hpp"
#include "opusDecoder.hpp"
#include "opusEncoder.hpp"

static int recordCallBack(const void *input, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *params)
{
    PortAudioCaps::AudioRecorder *tools = static_cast<PortAudioCaps::AudioRecorder *>(params);
    std::queue<Audio::rawFrameBuffer> &tab = tools->getSampleBuffer();
    Audio::rawFrameBuffer frameBuffer;

    frameBuffer.data = std::vector<float>(Audio::FRAMES_PER_BUFFER * Audio::NUM_CHANNELS * sizeof(float));
    std::memset(frameBuffer.data.data(), 0, Audio::FRAMES_PER_BUFFER * Audio::NUM_CHANNELS * sizeof(float));
    if (input)
        std::memcpy(frameBuffer.data.data(), input, Audio::FRAMES_PER_BUFFER * Audio::NUM_CHANNELS * sizeof(float));
    tab.push(frameBuffer);
    return paContinue;
}

static int streamerCallBack(const void *, void *output, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *params)
{
    PortAudioCaps::AudioStreamer *tools = static_cast<PortAudioCaps::AudioStreamer *>(params);
    std::queue<Audio::rawFrameBuffer> &tab = tools->getSampleBuffer();
    auto &member = tab.front();

    std::memcpy(output, member.data.data(), Audio::FRAMES_PER_BUFFER * Audio::NUM_CHANNELS * sizeof(float));
    tab.pop();
    return (tab.size()) ? paContinue : paComplete;
}

int main()
{
    /*
    ** OPUS
    */
    Audio::compressFrameBuffer compressed;

    compressed.data = std::vector<unsigned char>(Audio::FRAMES_PER_BUFFER * Audio::NUM_CHANNELS * sizeof(unsigned char));
    std::fill(compressed.data.begin(), compressed.data.end(), 0);
    compressed.encodedBit = 0;

    OpusCaps::opusDecoder decode;
    OpusCaps::opusEncoder encode;

    // Frame = decode.extract(compressed);
    // compressed = encode.compress(Frame);

    /*
    ** PortAudio
    */
    std::unique_ptr<PortAudioCaps::AudioRecorder> record = std::make_unique<PortAudioCaps::AudioRecorder>();
    record->setCallBack(recordCallBack);
    record->startStreaming();
    for (size_t i = 0; i < 5; i++)
        Pa_Sleep(1000);
    record->endStreaming();
    std::queue<Audio::rawFrameBuffer> buffer = record->getSampleBuffer();
    record.reset();

    /*
    ** COMPRESSION START
    */
    std::queue<Audio::compressFrameBuffer> listCompressed;
    while (buffer.size()) {
        listCompressed.push(encode.compress(buffer.front()));
        buffer.pop();
    }
    while (listCompressed.size()) {
        buffer.push(decode.extract(listCompressed.front()));
        listCompressed.pop();
    }
    /*
    ** COMPRESSION START
    */

    std::unique_ptr<PortAudioCaps::AudioStreamer> streamer = std::make_unique<PortAudioCaps::AudioStreamer>();

    while (buffer.size()) {
        streamer->getSampleBuffer().push(buffer.front());
        buffer.pop();
    }
    streamer->setCallBack(streamerCallBack);
    streamer->startStreaming();
    while (streamer->isStreaming())
        Pa_Sleep(100);
    streamer->endStreaming();
    streamer.reset();
    return 0;
}