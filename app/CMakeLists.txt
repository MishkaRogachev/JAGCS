# CMake version string
cmake_minimum_required(VERSION 3.0)

# App sources 
file(GLOB_RECURSE APP_SOURCES "main.cpp")
set(SOURCES ${SOURCES} ${APP_SOURCES} PARENT_SCOPE)

set(APP_INCLUDES "")
set(INCLUDES ${INCLUDES} ${APP_INCLUDES} PARENT_SCOPE)
