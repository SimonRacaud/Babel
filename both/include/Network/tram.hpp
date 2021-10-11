/*
 * EPITECH PROJECT, 2021
 * include
 * File description:
 * tram.hpp - Created: 27/09/2021
 */

#ifndef TRAM_HPP
#define TRAM_HPP

#include "utils.hpp"

namespace Network
{
    enum class TramAction
    {
        GET,
        POST,
        DELETE
    };

    enum class TramType
    {
        USER,
        CONTACT,
        STOP
    };

    const std::size_t TRAM_SIZE_SHIFT = sizeof(TramAction) + sizeof(TramType)
        + sizeof(bool) + sizeof(size_t);

    struct __attribute__((packed)) TramTCP {
        TramAction action;
        TramType type;
        bool error;
        size_t list_size;
        void *list;
    };
}; // namespace Network

#endif