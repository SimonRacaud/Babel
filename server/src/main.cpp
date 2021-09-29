/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** Server side of Babel
*/

#include <cstring>
#include <iostream>
#include "../../src/Network/AsioConnectionUDP.hpp"
#include "../../client/src/Audio/InputAudioManager/InputAudioManager.hpp"
#include "../../client/src/Audio/OutputAudioManager/OutputAudioManager.hpp"

#define BUFF_SIZE 1000

static void serverfunc(void)
{
    std::array<char, BUFF_SIZE> buff{"hello les pd!"};

    network::AsioConnectionUDP<BUFF_SIZE> serv(8080);
    Audio::InputAudioManager input;
    std::queue<Audio::compressFrameBuffer> frameBuffer;

    serv.connect("127.0.0.1", 8081);
    while (1) {
        frameBuffer = input.getFrameBuffer();
        while (frameBuffer.size()) {
            auto it = frameBuffer.front();

            std::memset(buff.data(), 0, BUFF_SIZE);
            std::memcpy(buff.data(), it.data.data(), it.encodedBit);
            std::memcpy(buff.data() + (BUFF_SIZE - sizeof(int)), &it.encodedBit, sizeof(int));
            try {
                std::cout << "send" << std::endl;
                serv.send(buff, "127.0.0.1", 8081);
            } catch (const std::system_error &) {
                std::cout << "ECHEC" << std::endl;
            }
            frameBuffer.pop();
        }
    }
}

static void clientfunc(void)
{
    std::queue<Audio::compressFrameBuffer> frameBuffer;
    Audio::OutputAudioManager output;
    network::AsioConnectionUDP<BUFF_SIZE> client(8081);
    Audio::compressFrameBuffer tmp;

    client.connect("127.0.0.1", 8080);
    while (1) {
        auto data = client.receive("127.0.0.1", 8080);

        std::cout << data.second << " == " << BUFF_SIZE << std::endl;
        if (data.second == BUFF_SIZE) {
            tmp.data = std::vector<unsigned char>(BUFF_SIZE);
            std::memset(tmp.data.data(), 0, BUFF_SIZE);
            std::memcpy(tmp.data.data(), data.first.data(), BUFF_SIZE - sizeof(int));
            std::memcpy(&tmp.encodedBit, data.first.data() + (BUFF_SIZE - sizeof(int)), sizeof(int));
            tmp.data.resize(tmp.encodedBit);
            frameBuffer.push(tmp);
            output.setFrameBuffer(frameBuffer);
            while (frameBuffer.size())
                frameBuffer.pop();
        } else {
            throw std::invalid_argument("Invalid buffer size");
        }
    }
}

int main(const int ac, const char **av)
{
    if (ac != 2)
        return 84;
    if (!std::strcmp(av[1], "server"))
        serverfunc();
    else if (!std::strcmp(av[1], "client"))
        clientfunc();
    else
        return 84;
    return 0;
}