# CMake version string
cmake_minimum_required(VERSION 3.0)

# Project
project(jagcs_core)

# QGamepad option
option(WITH_GAMEPAD "Compile with QGamepad module for manual input")
if(WITH_GAMEPAD)
add_definitions(-DWITH_GAMEPAD)
find_package(Qt5 COMPONENTS
    Gamepad
REQUIRED)
endif(WITH_GAMEPAD)

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
add_library(${PROJECT_NAME} SHARED)

# Use qt5 modules
qt5_use_modules(${PROJECT_NAME}
    Core
    Gui
    Network
    SerialPort
    Bluetooth
    Sql
    Positioning
)

# Includes
HEADER_DIRECTORIES(INCLUDES "includes")
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# Internal includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES "sources")
target_include_directories(${PROJECT_NAME} PRIVATE ${INTERNAL_INCLUDES})

# Sources
file(GLOB_RECURSE SOURCES "sources/*.h" "sources/*.hpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# NOTE: temporary solution for Q_NAMESPACE
# qt5_generate_moc(sources/domain/types/vehicle_types.h ${MOC_SOURCES})
qt5_wrap_cpp(MOC_SOURCES sources/domain/types/vehicle_types.h)
target_sources(${PROJECT_NAME} PRIVATE ${MOC_SOURCES})

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
option(WITH_TESTS "Include tests")
if(WITH_TESTS)
    add_subdirectory(tests)
endif(WITH_TESTS)
