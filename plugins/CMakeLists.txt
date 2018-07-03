# CMake version string
cmake_minimum_required(VERSION 3.0)

# MAVLink communication protocol plugin
option(WITH_MAVLINK "Compile with MAVLink communication protocol plugin")
if(WITH_MAVLINK)
add_definitions(-DWITH_MAVLINK)
add_subdirectory(mavlink)
endif(WITH_MAVLINK)

