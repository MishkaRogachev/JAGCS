# CMake version string
cmake_minimum_required(VERSION 3.2.1)

# Project
project(${CORE})

# Version message
message(STATUS "Configuring ${PROJECT_NAME}")

# Enable Qt modules
find_package(Qt5 COMPONENTS
    Core
    Gui
    Quick
    Qml
    Network
    SerialPort
    Bluetooth
    Sql
    Positioning
    LinguistTools
REQUIRED)

# Enable Qt5 qml compiler
#find_package(Qt5QuickCompiler REQUIRED)

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

# Core translations
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
file(GLOB_RECURSE QRC_FILES "resources/*.qrc")
qt5_add_resources(QRC_SOURCES ${QRC_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${QRC_SOURCES})

# QML compile resources
file(GLOB_RECURSE QRC_QML_FILES "sources/presentation/qml/*.qrc")
#qtquick_compiler_add_resources(QRC_QML_SOURCES ${QRC_QML_FILES})
qt5_add_resources(QRC_QML_SOURCES ${QRC_QML_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${QRC_QML_SOURCES})

# Add Qt libraries
set(QT_LIBRARIES
    Qt5::Core
    Qt5::Gui
    Qt5::Quick
    Qt5::Qml
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
