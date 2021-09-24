/*
** PERSONAL PROJECT, 2021
** AudioRecorder
** File description:
** AudioRecorder.cpp
*/

#include <cstring>
#include <stdexcept>
#include "Audio.hpp"
#include "AudioRecorder.hpp"

using namespace PortAudioCaps;

AudioRecorder::AudioRecorder() : _stream(nullptr), _callback(AudioRecorder::defaultCallBack)
{
    int PA_err = Pa_Initialize();

    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_Initialize");
    this->_parameters.device = Pa_GetDefaultInputDevice();
    if (this->_parameters.device == paNoDevice)
        throw std::invalid_argument("Failed: Pa_GetDefaultInputDevice");
    this->_parameters.sampleFormat =  paFloat32;
    this->_parameters.hostApiSpecificStreamInfo = NULL;
    this->_parameters.channelCount = Audio::NUM_CHANNELS;
    this->_parameters.suggestedLatency = Pa_GetDeviceInfo(this->_parameters.device)->defaultLowOutputLatency;
}

AudioRecorder::~AudioRecorder()
{
    if (this->isStreaming())
        throw std::invalid_argument("AudioRecorder is currently streaming");
    Pa_Terminate();
    while (this->_streaming.size())
        this->_streaming.pop();
}

/*
** IAudioManager
*/

void AudioRecorder::endStreaming()
{
    int PA_err = Pa_CloseStream(this->_stream);

    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_CloseStream");
    this->_stream = nullptr;
}

void AudioRecorder::startStreaming()
{
    int PA_err = 0;

    if (!this->_callback)
        throw std::invalid_argument("AudioRecorder invalid callback: nullptr");
    PA_err = Pa_OpenStream(&this->_stream, &this->_parameters, NULL, Audio::SAMPLE_RATE, Audio::FRAMES_PER_BUFFER, paClipOff, this->_callback, this);
    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_OpenStream");
    PA_err = Pa_StartStream(this->_stream);
    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_OpenStart");
}

bool AudioRecorder::isStreaming() const
{
    return this->_stream && Pa_IsStreamActive(this->_stream) == 1;
}

void AudioRecorder::setCallBack(int (*func) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *))
{
    this->_callback = func;
}

std::queue<Audio::rawFrameBuffer> &AudioRecorder::getSampleBuffer()
{
    return this->_streaming;
}

void AudioRecorder::setDevice(int device)
{
    this->_parameters.device = device;
    if (this->_parameters.device == paNoDevice)
        throw std::invalid_argument("Failed: invalid device");
    this->_parameters.suggestedLatency = Pa_GetDeviceInfo(this->_parameters.device)->defaultLowOutputLatency;
}

/*
** IAudioRecorder
*/

Audio::rawFrameBuffer AudioRecorder::getFrame()
{
    Audio::rawFrameBuffer tmp;

    if (!this->_streaming.size())
        throw std::invalid_argument("Not frame available");
    tmp = this->_streaming.front();
    this->_streaming.pop();
    return tmp;
}

int AudioRecorder::defaultCallBack(const void *input, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *params)
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