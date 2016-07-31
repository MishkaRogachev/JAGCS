# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT JAGCS)
project(${PROJECT})

# Set default output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)

# Add compiler flags
add_compile_options(-std=c++11 -Wall -fPIC)

# Sources and headrers
file(GLOB_RECURSE HEADERS "sources/*.h")
file(GLOB_RECURSE SOURCES "sources/*.cpp")

include_directories(${HEADERS})

add_executable(${PROJECT} ${SOURCES})
