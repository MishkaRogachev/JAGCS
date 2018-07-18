# CMake version string
cmake_minimum_required(VERSION 3.2.1)

# Project
project(${CORE})

# Version message
message(STATUS "Configuring ${PROJECT_NAME}")

# Enable Qt modules
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    Network
    SerialPort
    Bluetooth
    Sql
    Positioning
    LinguistTools
)

# Dynamic library target
add_library(${PROJECT_NAME} SHARED "")

# Public core includes
HEADER_DIRECTORIES(INCLUDES "includes")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# Internal core includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES "sources")
target_include_directories(${PROJECT_NAME} PRIVATE ${INTERNAL_INCLUDES})

# Internal core sources and headers
file(GLOB_RECURSE SOURCES "includes/*.h" "sources/*.h" "sources/*.cpp" "sources/*.hpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# Resources
file(GLOB_RECURSE QRC_FILES "resources/*.qrc")

# Create translations QRC file
file(GLOB TS_FILES "translations/*.ts")
tr_to_qrc("${CMAKE_CURRENT_BINARY_DIR}/core_ts.qrc")

# Compile resources
target_sources(${PROJECT_NAME} PRIVATE ${QRC_FILES})

# Add Qt libraries
set(QT_LIBRARIES
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Qt5::SerialPort
    Qt5::Bluetooth
    Qt5::Sql
    Qt5::Positioning
)

# Link Libraries
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

# Tests
if(WITH_TESTS)
    add_subdirectory(tests)
endif(WITH_TESTS)
