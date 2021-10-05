/*
 * EPITECH PROJECT, 2021
 * src
 * File description:
 * signal_manager.c - Created: 05/10/2021
 */

#include <signal.h>

#include "utils.hpp"

static void activatorSwitch(bool *activatorPtr)
{
    static bool *ptr = nullptr;

    if (activatorPtr != nullptr) {
        ptr = activatorPtr;
        *ptr = true;
    } else if (ptr != nullptr) {
        *ptr = false;
    }
}

static void signalHandler(UNUSED int signum)
{
    activatorSwitch(nullptr);
}

void signalManager(const int &signum, bool &activatorPtr)
{
    activatorSwitch(&activatorPtr);
    auto signalValue = signal(signum, &signalHandler);

    if (signalValue == SIG_ERR)
        throw std::runtime_error("signal error");
}