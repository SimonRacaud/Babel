/*
 * EPITECH PROJECT, 2021
 * Interpreters
 * File description:
 * InterpreterTCP.cpp - Created: 27/09/2021
 */

#include "InterpretorTCP.hpp"

using namespace network;

template <size_t PACKETSIZE>
InterpreterTCP<PACKETSIZE>::InterpreterTCP(DatabaseManager &databaseManager) : _databaseManager(databaseManager)
{
}

template <size_t PACKETSIZE> void InterpreterTCP<PACKETSIZE>::operator()(const std::array<char, PACKETSIZE> &data, const size_t &size)
{
}

template <size_t PACKETSIZE> void InterpreterTCP<PACKETSIZE>::_get(const std::array<char, PACKETSIZE> &data, const size_t &size)
{
}

template <size_t PACKETSIZE> void InterpreterTCP<PACKETSIZE>::_post(const std::array<char, PACKETSIZE> &data, const size_t &size)
{
}

template <size_t PACKETSIZE> void InterpreterTCP<PACKETSIZE>::_delete(const std::array<char, PACKETSIZE> &data, const size_t &size)
{
}