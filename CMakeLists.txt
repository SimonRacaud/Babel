cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CLIENT babel_client)
set(SERVER babel_server)

project(Babel VERSION 0.0.0 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_INCLUDE_PATH})

set(SRC_CLIENT client/src/)
set(SRC_SERVER server/src/)

include_directories(
    ./include/
    ./include/Interfaces/
)

############ CLIENT

## SOURCES
set(SRCS_CLIENT
    ${SRC_CLIENT}/main.cpp
)

add_executable(${CLIENT} ${SRCS_CLIENT})

## COMPILATION


if (MSVC)
    target_compile_options(${CLIENT} PRIVATE /W4 /WX)
else ()
    target_compile_options(${CLIENT} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()
set_target_properties(${CLIENT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

############ SERVER

## SOURCES
set(SRCS_SERVER
    ${SRC_SERVER}/main.cpp
)

add_executable(${SERVER} ${SRCS_SERVER})

## COMPILATION

if (MSVC)
    target_compile_options(${SERVER} PRIVATE /W4 /WX)
else ()
    target_compile_options(${SERVER} PRIVATE -Wall -Wextra -Wno-missing-field-initializers)
endif ()
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

# LDD conan
target_link_libraries(${CLIENT} PUBLIC ${CONAN_LIBS} opusTools portAudioTools)
target_link_libraries(${SERVER} PUBLIC ${CONAN_LIBS})