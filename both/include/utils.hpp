/*
 * EPITECH PROJECT, 2021
 * include
 * File description:
 * utils.hpp - Created: 23/09/2021
 */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Network.hpp"
#include <fstream>

#define EXIT_SUCCESS 0
#define EXIT_ERROR   84
#define UNUSED       [[maybe_unused]]

typedef std::string string;
typedef std::size_t size_t;
typedef std::stringstream stringstream;
typedef std::fstream fstream;
typedef std::ofstream ofstream;
typedef std::ifstream ifstream;
#define myToString(str)  std::to_string(str)
#define toInteger(str) std::stoi(str)
#define toSize_t(str)  std::stoul(str)

#endif