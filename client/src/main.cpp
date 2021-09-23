/*
** PERSONAL PROJECT, 2021
** opusDecoder
** File description:
** opusDecoder.hpp
*/

#include <memory>
#include <iostream>
#include <unistd.h>
#include "AudioStreamer.hpp"
#include "AudioRecorder.hpp"
#include "opusDecoder.hpp"
#include "opusEncoder.hpp"

static int recordCallBack(const void *input, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *params)
{
    PortAudioCaps::AudioRecorder *tools = static_cast<PortAudioCaps::AudioRecorder *>(params);
    const float *inputFrameBuffer = static_cast<const float *>(input);
    std::queue<Audio::rawFrameBuffer> &tab = tools->getSampleBuffer();
    std::vector<float> translateBuffer;

    for (size_t i = 0; i < Audio::FRAMES_PER_BUFFER * Audio::NUM_CHANNELS; i++)
        translateBuffer.push_back(inputFrameBuffer[i]);
    tab.push({
        translateBuffer
    });
    std::cout << "here2: " << translateBuffer.size() << std::endl;
    return paContinue;
}

static int streamerCallBack(const void *, void *output, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *params)
{
    PortAudioCaps::AudioStreamer *tools = static_cast<PortAudioCaps::AudioStreamer *>(params);
    float *outputFrameBuffer = static_cast<float *>(output);
    std::queue<Audio::rawFrameBuffer> &tab = tools->getSampleBuffer();

    std::cout << "here1: " << tab.size() << std::endl;
    //while (tab.size()) {
        auto &member = tab.back();
        for (size_t i = 0; i < member.data.size() && i < Audio::FRAMES_PER_BUFFER; i++)
            outputFrameBuffer[i] = member.data[i];
        tab.pop();
    //}
    return (tab.size()) ? paContinue : paComplete;
}

int main()
{
    // Audio::rawFrameBuffer Frame;
    // Audio::compressFrameBuffer compressed;

    // Frame.data = std::vector<float>(Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(float));
    // std::fill(Frame.data.begin(), Frame.data.end(), 0);

    // compressed.data = std::vector<unsigned char>(Audio::SAMPLE_RATE * Audio::NUM_CHANNELS * sizeof(unsigned char));
    // std::fill(compressed.data.begin(), compressed.data.end(), 0);
    // compressed.encodedBit = 0;

    // OpusCaps::opusDecoder decode;
    // OpusCaps::opusEncoder encode;

    // Frame = decode.extract(compressed);
    // compressed = encode.compress(Frame);

    std::unique_ptr<PortAudioCaps::AudioRecorder> record = std::make_unique<PortAudioCaps::AudioRecorder>();
    record->setCallBack(recordCallBack);
    record->startStreaming();
    for (size_t i = 0; i < 5; i++)
        Pa_Sleep(1000);
    record->endStreaming();
    auto buffer = record->getSampleBuffer();
    record.reset();

    std::unique_ptr<PortAudioCaps::AudioStreamer> streamer = std::make_unique<PortAudioCaps::AudioStreamer>();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "ICICICICICICICICICI: " << buffer.size() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    while (buffer.size()) {
        streamer->getSampleBuffer().push(buffer.back());
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