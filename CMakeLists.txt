##
## PERSONAL PROJECT, 2021
## Babel Project
## File description:
## Babel CMake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME Babel)

project(${NAME} VERSION 0.0.0 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

## SOURCES
set(SRCS
        src/main.cpp src/gui/Window/Window.cpp src/gui/MyContactList/MyContactList.cpp src/gui/MyContactList/MyContactList.hpp src/gui/MyContactList/Contact/Contact.cpp src/gui/MyContactList/Contact/Contact.hpp src/gui/AddContact/AddContact.cpp src/gui/AddContact/AddContact.hpp)

include_directories(${CMAKE_INCLUDE_PATH})
include_directories(./src/)

add_executable(${NAME} ${SRCS})

## COMPILATION
target_compile_options(${NAME} PRIVATE -Wall -Wextra) # -Werror

set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

# LDD conan
#target_link_libraries(babel_client ${CONAN_LIBS})
#target_link_libraries(babel_server ${CONAN_LIBS})
target_link_libraries(${NAME} ${CONAN_LIBS})