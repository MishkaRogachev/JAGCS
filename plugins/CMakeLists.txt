# CMake version string
cmake_minimum_required(VERSION 3.0)

# Various plugins

# MAVLink communication protocol plugin
option(WITH_MAPBOXGL "Compile with MAVLink communication protocol plugin")
if(WITH_MAPBOXGL)
add_definitions(-DWITH_MAPBOXGL)
endif(WITH_MAPBOXGL)

add_subdirectory(mavlink)
