#!/bin/bash

## Create build directory if it doesn't exist
if [ ! -d "./build" ]; then
   mkdir build
fi

## Build
cd build && conan install .. --build missing && cmake .. && make

