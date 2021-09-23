/*
** PERSONAL PROJECT, 2021
** AudioStreamer
** File description:
** AudioStreamer.cpp
*/

#include "AudioStreamer.hpp"
#include <stdexcept>
#include "Audio.hpp"

using namespace PortAudioCaps;

AudioStreamer::AudioStreamer() : _stream(nullptr), _callback(nullptr)
{
    int PA_err = Pa_Initialize();

    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_Initialize");
    this->_parameters.device = Pa_GetDefaultOutputDevice();
    if (this->_parameters.device == paNoDevice)
        throw std::invalid_argument("Failed: Pa_GetDefaultOutputDevice");
    this->_parameters.sampleFormat =  paFloat32;
    this->_parameters.hostApiSpecificStreamInfo = NULL;
    this->_parameters.channelCount = Audio::NUM_CHANNELS;
    this->_parameters.suggestedLatency = Pa_GetDeviceInfo(this->_parameters.device)->defaultLowOutputLatency;
}

AudioStreamer::~AudioStreamer()
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

void AudioStreamer::endStreaming()
{
    int PA_err = Pa_CloseStream(this->_stream);

    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_CloseStream");
    this->_stream = nullptr;
}

void AudioStreamer::startStreaming()
{
    int PA_err = 0;

    if (!this->_callback)
        throw std::invalid_argument("AudioStreamer invalid callback: nullptr");
    PA_err = Pa_OpenStream(&this->_stream, NULL, &this->_parameters, Audio::SAMPLE_RATE, Audio::FRAMES_PER_BUFFER, paClipOff, this->_callback, this);
    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_OpenStream");
    PA_err = Pa_StartStream(this->_stream);
    if (PA_err != paNoError)
        throw std::invalid_argument("Failed: Pa_OpenStart");
}

bool AudioStreamer::isStreaming() const
{
    return this->_stream && Pa_IsStreamActive(this->_stream) == 1;
}

void AudioStreamer::setCallBack(int (*func) (const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *))
{
    this->_callback = func;
}

std::queue<Audio::rawFrameBuffer> &AudioStreamer::getSampleBuffer()
{
    return this->_streaming;
}

/*
** IAudioStreamer
*/
void AudioStreamer::setFrame(Audio::rawFrameBuffer frame)
{
    this->_streaming.push(frame);
}