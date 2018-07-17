# CMake version string
cmake_minimum_required(VERSION 3.2.1)

# Project
project(jagcs_mavlink)

# Version message
message(STATUS "Configuring plugin ${PROJECT_NAME}")

# Enable Qt modules
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Positioning
    LinguistTools
)

# Qt plugin definition
add_definitions(-DQT_PLUGIN)

# Dynamic library target
add_library(${PROJECT_NAME} SHARED "")

# MAVLink library includes
option(WITH_MAVLINK_V2 "MAVLink version 2 includes")
if(WITH_MAVLINK_V2)
    target_include_directories(${PROJECT_NAME} PRIVATE "3rdparty/mavlink_v2")
    target_include_directories(${PROJECT_NAME} PRIVATE "3rdparty/mavlink_v2/ardupilotmega")
    add_definitions(-DMAVLINK_V2)
else(WITH_MAVLINK_V2)
    target_include_directories(${PROJECT_NAME} PRIVATE "3rdparty/mavlink_v1")
    target_include_directories(${PROJECT_NAME} PRIVATE "3rdparty/mavlink_v1/ardupilotmega")
endif(WITH_MAVLINK_V2)

# Internal MAVLink plugin includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES "sources")
target_include_directories(${PROJECT_NAME} PRIVATE ${INTERNAL_INCLUDES})

# Internal MAVLink plugin sources and headers
file(GLOB_RECURSE SOURCES "includes/*.h" "sources/*.h" "sources/*.cpp" "sources/*.hpp" "*.json")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# MAVLink Plugin translations
file(GLOB TS_FILES "translations/*.ts")

# Qt5 add translation sourses from translation files
qt5_add_translation(QM_FILES ${TS_FILES})

# Create translations QRC file
set(TRANSLATIONS_QRC "${CMAKE_CURRENT_BINARY_DIR}/mavlink_ts.qrc")
file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n\t<qresource prefix=\"/\">")
foreach(QM_FILE ${QM_FILES})
    get_filename_component(QM_FILE_NAME ${QM_FILE} NAME)
    file(APPEND ${TRANSLATIONS_QRC} "\n\t\t<file alias=\"${QM_FILE_NAME}\">${QM_FILE_NAME}</file>")
endforeach()
file(APPEND ${TRANSLATIONS_QRC} "\n\t</qresource>\n</RCC>")
list(APPEND QRC_FILES ${TRANSLATIONS_QRC})

# Resources
file(GLOB_RECURSE QRC_FILES "*.qrc")
target_sources(${PROJECT_NAME} PRIVATE ${QRC_FILES})

# Add Qt libraries
set(QT_LIBRARIES
    Qt5::Core
    Qt5::Positioning
)

# Link Libraries
target_link_libraries(${PROJECT_NAME} ${CORE} ${QT_LIBRARIES})

# Tests
if(WITH_TESTS)
#    add_subdirectory(tests)
endif(WITH_TESTS)
