/*
** PERSONAL PROJECT, 2021
** tramFactory
** File description:
** tramFactory.hpp
*/

#ifndef TRAMFACTORY_HPP
#define TRAMFACTORY_HPP

#include <array>
#include <cstring>

template <typename tramType>
class tramFactory
{
    static tramFactory getTram(const void *data)
    {
        tramFactory tram;

        std::memset(&tram, 0, sizeof(tramFactory));
        std::memmove(&tram, data, sizeof(tramFactory));
        return tram;
    }

    static std::array<char, sizeof(tramType)> makeTram(const tramFactory &tram)
    {
        std::array<char, sizeof(tramType)> buff;

        std::memset(buff.data(), 0, sizeof(tramFactory));
        std::memmove(buff.data(), &tram, sizeof(tramFactory));
        return buff;
    }
};

#endif