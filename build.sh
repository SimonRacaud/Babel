#!/bin/bash

## Create build directory if it doesn't exist
if [ ! -d "./build" ]; then
   mkdir build
fi

## Build
if [[ "re" = $1 ]]; then
  cd build && conan install .. --build missing
  cmake .. && make
else
    make -C build
fi
