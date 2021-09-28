/*
 * EPITECH PROJECT, 2021
 * API
 * File description:
 * API.hpp - Created: 27/09/2021
 */

#ifndef API_INTERFACE_HPP
#define API_INTERFACE_HPP

#include "DatabaseManager.hpp"
#include "INetwork.hpp"
#include "utils.hpp"

namespace Network
{
    template <size_t PACKETSIZE> class IAPI {
      public:
        virtual void operator()(const std::array<char, PACKETSIZE> &data, const string &ip = "", const size_t port = 0) = 0;
    };
}; // namespace Network

#endif