##
## PERSONAL PROJECT, 2021
## Babel Project
## File description:
## Babel CMake
##

cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug) # TEMPORARY

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(NAME_CLIENT babel_client)
set(NAME_SRV babel_server)

add_definitions("-fPIC")

project(Babel VERSION 0.0.0 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

## SOURCES
file(GLOB_RECURSE SRCS_CLIENT client/src/*)

add_executable(${NAME_CLIENT} ${SRCS_CLIENT} client/include/ICallManager.hpp client/include/IMyContactList.hpp client/include/IContact.hpp)

## Client includes (Qt)
include_directories(${CMAKE_INCLUDE_PATH} client/src/ client/include)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC client/src/gui/Account)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC client/src/gui/AddContact)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC client/src/gui/CallManager)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC client/src/gui/MyContactList)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC client/src/gui/Options)
target_include_directories(${NAME_CLIENT} BEFORE PUBLIC client/src/gui/Window)

## COMPILATION FLAGS
target_compile_options(${NAME_CLIENT} PRIVATE -Wall -Wextra) # -Werror
## Binary destination
set_target_properties(${NAME_CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

# LDD conan
#target_link_libraries(babel_server ${CONAN_LIBS})
target_link_libraries(${NAME_CLIENT} ${CONAN_LIBS} Qt5::Widgets Qt5::Network)
