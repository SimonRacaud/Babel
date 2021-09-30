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
    public:
        static tramType getTram(const void *data)
        {
            tramType tram;

            std::memmove(&tram, data, sizeof(tramType));
            return tram;
        }

        static std::array<char, sizeof(tramType)> makeTram(const tramType &tram)
        {
            std::array<char, sizeof(tramType)> buff;

            std::memset(buff.data(), 0, sizeof(tramType));
            std::memmove(buff.data(), &tram, sizeof(tramType));
            return buff;
        }
};

#endif