# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# Project
set(PROJECT jagcs)
project(${PROJECT})

# CMake modules
include(cmake/RecurseSubdirs.cmake)
include(cmake/GitRevision.cmake)

# Versions
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${VERSION_MINOR})
add_definitions(-DVERSION_PATCH=${VERSION_PATCH})
add_definitions(-DGIT_REVISION=${GIT_REVISION})

# Set default output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Add compiler flags
set (CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -fPIC)

# Enable globaly some Qt modules
find_package(Qt5 COMPONENTS
    Core
    Network
    SerialPort
    Sql
    Gui
    Quick
    LinguistTools
    Multimedia
    Positioning
    Location
    Charts
    QuickControls2
    Gamepad
REQUIRED)

set(LIBRARIES
# Libraries
)

# Sources and headrers
file(GLOB_RECURSE HEADERS "sources/*.h")
file(GLOB_RECURSE SOURCES "sources/*.cpp")
file(GLOB_RECURSE QML "sources/*.qml")
file(GLOB_RECURSE JS "sources/*.js")

# Includes
include_directories("3dparty/mavlink_v1")
include_directories("3dparty/mavlink_v1/ardupilotmega")

HEADER_DIRECTORIES(INCLUDES "sources")
include_directories(${INCLUDES})

# Translations
file(GLOB TS_FILES "translations/*.ts")

# Qt5 add translation sourses from translation files
qt5_add_translation(QM_FILES ${TS_FILES})

# Create translations QRC file
set(TRANSLATIONS_QRC "${CMAKE_CURRENT_BINARY_DIR}/jagcs_ts.qrc")
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

# Executable target
add_executable(${PROJECT} ${SOURCES} ${HEADERS} ${QML}
    ${JS} ${QRC_SOURCES} ${MOC_SOURCES})

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})

# Use qt5 modules
qt5_use_modules(${PROJECT}
    Core
    Network
    SerialPort
    Sql
    Gui
    Quick
    Multimedia
    Positioning
    Location
    Charts
    QuickControls2
    Gamepad
)

# Install instructions
install(TARGETS ${PROJECT} DESTINATION "/usr/bin")
install(FILES "debian/jagcs.desktop" DESTINATION "/usr/share/applications/")
install(FILES "resources/icons/jagcs.svg" DESTINATION "/usr/share/icons/")

# CPack Debian package
option(WITH_DEBIAN "Include instructions to make Debian package")
if (WITH_DEBIAN)
    add_subdirectory(debian)
endif (WITH_DEBIAN)
