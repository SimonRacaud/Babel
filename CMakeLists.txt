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

add_definitions("-fPIC")

project(${NAME} VERSION 0.0.0 LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*)
## SOURCES
#set(SRCS
#        src/main.cpp
#        src/gui/Window/Window.cpp
#        src/gui/MyContactList/MyContactList.cpp
#        src/gui/MyContactList/MyContactList.hpp
#        src/gui/MyContactList/Contact/Contact.cpp
#        src/gui/MyContactList/Contact/Contact.hpp
#        src/gui/AddContact/AddContact.cpp
#        src/gui/AddContact/AddContact.hpp
#        src/gui/Account/Account.cpp
#        src/gui/Account/Account.hpp
#        src/gui/CallManager/CallManager.cpp
#        src/gui/CallManager/CallManager.hpp
#        src/gui/Options/Options.cpp src/gui/Options/Options.hpp)

add_executable(${NAME} ${SRCS})

include_directories(${CMAKE_INCLUDE_PATH} ./src/)
target_include_directories(${NAME} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/src/gui/Account)
target_include_directories(${NAME} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/src/gui/AddContact)
target_include_directories(${NAME} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/src/gui/CallManager)
target_include_directories(${NAME} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/src/gui/MyContactList)
target_include_directories(${NAME} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/src/gui/Options)
target_include_directories(${NAME} BEFORE PUBLIC ${PROJECT_SOURCE_DIR}/src/gui/Window)

## COMPILATION
target_compile_options(${NAME} PRIVATE -Wall -Wextra) # -Werror

set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")

# LDD conan
#target_link_libraries(babel_client ${CONAN_LIBS})
#target_link_libraries(babel_server ${CONAN_LIBS})
target_link_libraries(${NAME} ${CONAN_LIBS} Qt5::Widgets Qt5::Network)
