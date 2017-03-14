# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT tests)
project(${PROJECT})

# Enable Qt modules
find_package(Qt5 COMPONENTS Test REQUIRED)

# Includes
HEADER_DIRECTORIES(TEST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${TEST_INCLUDES} ${INCLUDES})

# Test sources
file(GLOB_RECURSE TEST_SOURCES "*.h" "*.cpp" "../sources/data_source/*.cpp")

# Executable
add_executable(${PROJECT} ${TEST_SOURCES})
set_target_properties(${PROJECT} PROPERTIES AUTOMOC TRUE)

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})

# Use qt5 modules
qt5_use_modules(${PROJECT}
    Core
    Network
    SerialPort
    Sql
    Gui
    Multimedia
    Positioning
    Gamepad
    Test
)

# Tests
add_test (NAME ${PROJECT} COMMAND ${PROJECT})
