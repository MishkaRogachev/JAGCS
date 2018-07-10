# CMake version string
cmake_minimum_required(VERSION 3.2.1)

# Plugins library path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/plugins)

# MAVLink communication protocol plugin
option(WITH_MAVLINK "Compile with MAVLink communication protocol plugin")
if(WITH_MAVLINK)
add_definitions(-DWITH_MAVLINK)
add_subdirectory(mavlink)
endif(WITH_MAVLINK)

