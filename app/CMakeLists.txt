# CMake version string
cmake_minimum_required(VERSION 3.0)

# Internal sources and headers
file(GLOB_RECURSE APP_SOURCES "*.cpp")
set(SOURCES ${SOURCES} ${APP_SOURCES} PARENT_SCOPE)

HEADER_DIRECTORIES(APP_INCLUDES ".")
set(INCLUDES ${INCLUDES} ${APP_INCLUDES} PARENT_SCOPE)
