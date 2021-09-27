##
## PERSONAL PROJECT, 2021
## Babel Project
## File description:
## Babel CMake
##

cmake_minimum_required(VERSION 3.17)

# set(CMAKE_BUILD_TYPE Debug) # TEMPORARY

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CLIENT babel_client)
set(SERVER babel_server)

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

set(SRC_CLIENT client/src/)
set(SRC_SERVER server/src/)

include_directories(
        ${CMAKE_INCLUDE_PATH}
        ./include/
        ./include/Interfaces/
        ./client/src/
        ./client/include
)

############ CLIENT

set(CLIENT_SRCS src/Network/mainTestNetwork.cpp)
add_executable(${CLIENT} ${CLIENT_SRCS})

#set(SERVER_SRCS)
#add_executable(${SERVER} ${SERVER_SRCS})


target_include_directories(${CLIENT} BEFORE PUBLIC src)
target_include_directories(${CLIENT} BEFORE PUBLIC src/server)
target_include_directories(${CLIENT} BEFORE PUBLIC src/Network)

## Client includes (Qt)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/Account)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/AddContact)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/CallManager)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/MyContactList)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/Options)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/Window)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/Audio/InputAudioManager)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/Audio/OutputAudioManager)

## Server include
include_directories(server/include)

## COMPILATION FLAGS + DESTINATION
if (MSVC)
    target_compile_options(${CLIENT} PRIVATE /W4 /WX)
    #    target_compile_options(${SERVER} PRIVATE /W4 /WX)
else ()
    target_compile_options(${CLIENT} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
    #    target_compile_options(${SERVER} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
##set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

## OPUS
set(OPUS_TOOLS_DIR ${PROJECT_SOURCE_DIR}/libs/opus/)
add_subdirectory(${OPUS_TOOLS_DIR})
include_directories(${OPUS_TOOLS_DIR}/include)
include_directories(${OPUS_TOOLS_DIR}/src)

## PORTAUDIO
set(PORT_AUDIO_TOOLS_DIR ${PROJECT_SOURCE_DIR}/libs/portAudio/)
add_subdirectory(${PORT_AUDIO_TOOLS_DIR})
include_directories(${PORT_AUDIO_TOOLS_DIR}/include)
include_directories(${PORT_AUDIO_TOOLS_DIR}/src)

# LDD conan
target_link_libraries(${CLIENT} PUBLIC ${CONAN_LIBS} opusTools portAudioTools Qt5::Widgets Qt5::Network)
#target_link_libraries(${SERVER} PUBLIC ${CONAN_LIBS})