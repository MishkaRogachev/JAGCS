# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT JAGCS)
project(${PROJECT})

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Set default output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Add compiler flags
add_compile_options(-std=c++11 -Wall -fPIC)

# Enable globaly some Qt modules
find_package(Qt5 COMPONENTS
    Core
    Network
    SerialPort
    Gui
    Quick
    Multimedia
    Positioning
    Location
    Charts
REQUIRED)

# Global libraries
set(LIBRARIES
# Qt5
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Gui
    Qt5::Quick
    Qt5::Multimedia
    Qt5::Positioning
    Qt5::Location
    Qt5::Charts
)

# Sources and headrers
file(GLOB_RECURSE HEADERS "sources/*.h")
file(GLOB_RECURSE SOURCES "sources/*.cpp")
file(GLOB_RECURSE QML "sources/*.qml")

# Includes
HEADER_DIRECTORIES(INCLUDES "sources")
include_directories(${INCLUDES})

# Resources
file(GLOB_RECURSE QRC_FILES "*.qrc")

# Qt5 add resources
qt5_add_resources(QRC_SOURCES ${QRC_FILES})

# Executable target
add_executable(${PROJECT} ${SOURCES} ${HEADERS} ${QML} ${QRC_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})
