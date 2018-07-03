# CMake version string
cmake_minimum_required(VERSION 3.0)

# MAVLink includes
option(WITH_MAVLINK_V2 "MAVLink version 2 includes")
if(WITH_MAVLINK_V2)
    include_directories("3rdparty/mavlink_v2")
    include_directories("3rdparty/mavlink_v2/ardupilotmega")
    add_definitions(-DMAVLINK_V2)
else(WITH_MAVLINK_V2)
    include_directories("3rdparty/mavlink_v1")
    include_directories("3rdparty/mavlink_v1/ardupilotmega")
endif(WITH_MAVLINK_V2)

# Internal sources and headers
file(GLOB_RECURSE PLUGIN_SOURCES "*.h" "*.cpp" "*.hpp")
set(SOURCES ${SOURCES} ${PLUGIN_SOURCES} PARENT_SCOPE)

HEADER_DIRECTORIES(PLUGIN_INCLUDES ".")
set(INCLUDES ${INCLUDES} ${PLUGIN_INCLUDES} PARENT_SCOPE)
