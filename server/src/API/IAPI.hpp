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

namespace network
{
    template <size_t PACKETSIZE> class IAPI {
      public:
        virtual IAPI(IConnection &network, DatabaseManager &databaseManager) = 0;

        virtual void operator()(const std::array<char, PACKETSIZE> &data, const string &ip = "", const size_t port = 0) = 0;
    };
}; // namespace network

#endif