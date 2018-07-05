# CMake version string
cmake_minimum_required(VERSION 3.2.1)

# Project
project(jagcs_core)

# Version message
message(STATUS "Configuring ${PROJECT_NAME}")

# Enable Qt modules
find_package(Qt5 COMPONENTS
    Core
    Gui
    Network
    SerialPort
    Bluetooth
    Sql
    Positioning
    LinguistTools
REQUIRED)

# Dynamic library taget
add_library(${PROJECT_NAME} SHARED "")

# Includes
HEADER_DIRECTORIES(INCLUDES "includes")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# Internal includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES "sources")
target_include_directories(${PROJECT_NAME} PRIVATE ${INTERNAL_INCLUDES})

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

# Sources
file(GLOB_RECURSE SOURCES "includes/*.h" "sources/*.h" "sources/*.cpp" "sources/*.hpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# Translations
file(GLOB TS_FILES "translations/*.ts")

# Qt5 add translation sourses from translation files
qt5_add_translation(QM_FILES ${TS_FILES})

# Create translations QRC file
set(TRANSLATIONS_QRC "${CMAKE_CURRENT_BINARY_DIR}/core_ts.qrc")
file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n\t<qresource prefix=\"/\">")
foreach(QM_FILE ${QM_FILES})
    get_filename_component(QM_FILE_NAME ${QM_FILE} NAME)
    file(APPEND ${TRANSLATIONS_QRC} "\n\t\t<file alias=\"${QM_FILE_NAME}\">${QM_FILE_NAME}</file>")
endforeach()
file(APPEND ${TRANSLATIONS_QRC} "\n\t</qresource>\n</RCC>")
list(APPEND QRC_FILES ${TRANSLATIONS_QRC})

# Resources
file(GLOB_RECURSE QRC_FILES "*.qrc")

# Qt5 add resources
qt5_add_resources(QRC_SOURCES ${QRC_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${QRC_FILES})

# Tests
if(WITH_TESTS)
    add_subdirectory(tests)
endif(WITH_TESTS)
