##
## PERSONAL PROJECT, 2021
## opus Project
## File description:
## opus CMake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME opusTools)

project(${NAME} VERSION 0.0.0 LANGUAGES CXX)

## INCLUDES
include_directories(
    ./src/
    ./include/
    ../include/
)

## SOURCES
set(SRCS
    src/opusDecoder/opusDecoder.cpp
    src/opusEncoder/opusEncoder.cpp
)

add_library(${NAME} SHARED ${SRCS})
target_compile_options(${NAME} PRIVATE -Wall -Wextra)