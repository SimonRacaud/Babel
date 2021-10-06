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
        both/include/
        both/include/Interfaces/
        both/include/Network/
        both/include/Network/Raws/
)

############ CLIENT

## SOURCES

set(CLIENT_SRCS
    ${SRC_CLIENT}/main.cpp
    ${SRC_CLIENT}/Audio/InputAudioManager/InputAudioManager.cpp
    ${SRC_CLIENT}/Audio/OutputAudioManager/OutputAudioManager.cpp
    ${SRC_CLIENT}/gui/Account/Account.cpp
    ${SRC_CLIENT}/gui/Account/Account.hpp
    ${SRC_CLIENT}/gui/AddContact/AddContact.cpp
    ${SRC_CLIENT}/gui/AddContact/AddContact.hpp
    ${SRC_CLIENT}/gui/CallManager/CallManager.hpp
    ${SRC_CLIENT}/gui/CallManager/CallManager.cpp
    ${SRC_CLIENT}/gui/MyContactList/MyContactList.cpp
    ${SRC_CLIENT}/gui/MyContactList/MyContactList.hpp
    ${SRC_CLIENT}/gui/MyContactList/Contact/Contact.hpp
    ${SRC_CLIENT}/gui/MyContactList/Contact/Contact.cpp
    ${SRC_CLIENT}/gui/Options/Options.cpp
    ${SRC_CLIENT}/gui/Options/Options.hpp
    ${SRC_CLIENT}/gui/Window/Window.cpp
    ${SRC_CLIENT}/gui/Window/Window.hpp
    ${SRC_CLIENT}/Network/Controller/Controller.cpp
    ${SRC_CLIENT}/Network/Controller/Controller.hpp
    ${SRC_CLIENT}/Network/Worker/NetworkWorker.hpp
    ${SRC_CLIENT}/Network/Worker/NetworkWorker.cpp
    ${SRC_CLIENT}/NetworkManager/NetworkManager.cpp
    ${SRC_CLIENT}/NetworkManager/NetworkManager.hpp
    ${SRC_CLIENT}/UDPAudio/UDPAudio.cpp
    ${SRC_CLIENT}/UDPAudio/tools/tramFactory.hpp
    ${SRC_CLIENT}/gui/Dialogue/DialogueBox.cpp
    ${SRC_CLIENT}/gui/Dialogue/DialogueBox.hpp
    both/src/TcpTram.cpp
)

add_executable(${CLIENT} ${CLIENT_SRCS})

set(SERVER_SRCS
    ${SRC_SERVER}/main.cpp
    ${SRC_SERVER}/SignalManager.cpp
    ${SRC_SERVER}/Database/DatabaseManager.cpp
    ${SRC_SERVER}/API/API.cpp
    ${SRC_SERVER}/API/Interpreters/User/UserInterpreter.cpp
    ${SRC_SERVER}/API/Interpreters/Contact/ContactInterpreter.cpp
    both/src/TcpTram.cpp
)
add_executable(${SERVER} ${SERVER_SRCS})

## Client includes (Qt)
target_include_directories(${CLIENT} BEFORE PUBLIC client/include)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/Account)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/AddContact)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/CallManager)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/MyContactList)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/Options)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/Window)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/Audio/InputAudioManager)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/Audio/OutputAudioManager)
target_include_directories(${CLIENT} BEFORE PUBLIC both/src/TCPTram)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/Network/Controller)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/Network/Worker)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/NetworkManager)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/UDPAudio)
target_include_directories(${CLIENT} BEFORE PUBLIC client/src/gui/Dialogue)

## Server include
target_include_directories(${SERVER} BEFORE PUBLIC server/include)
target_include_directories(${SERVER} BEFORE PUBLIC server/src/)
target_include_directories(${SERVER} BEFORE PUBLIC server/src/API)
target_include_directories(${SERVER} BEFORE PUBLIC server/src/API/Interpreters)
target_include_directories(${SERVER} BEFORE PUBLIC server/src/Database)

## COMPILATION FLAGS + DESTINATION
if (MSVC)
    target_compile_options(${CLIENT} PRIVATE /W4 /WX)
    target_compile_options(${SERVER} PRIVATE /W4 /WX)
else ()
    target_compile_options(${CLIENT} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
    target_compile_options(${SERVER} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
set_target_properties(${SERVER} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

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

## ASIO
set(ASIO_TOOLS_DIR ${PROJECT_SOURCE_DIR}/libs/asio/)
include_directories(${ASIO_TOOLS_DIR}/include)
target_include_directories(${SERVER} BEFORE PUBLIC ${ASIO_TOOLS_DIR}/include)
target_include_directories(${CLIENT} BEFORE PUBLIC ${ASIO_TOOLS_DIR}/include)

# LDD conan
target_link_libraries(${CLIENT} PUBLIC ${CONAN_LIBS} opusTools portAudioTools Qt5::Widgets Qt5::Network)
target_link_libraries(${SERVER} PUBLIC ${CONAN_LIBS})