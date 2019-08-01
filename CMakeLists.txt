# CMake version string
cmake_minimum_required(VERSION 3.0)

# Project
set(PROJECT jagcs)
project(${PROJECT})

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Versions
set(VERSION_MAJOR 0)
set(VERSION_MINOR 5)
set(VERSION_PATCH 2)

# Get git revision hash
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REVISION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get version from git
add_definitions(-DVERSION_MAJOR=${VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${VERSION_MINOR})
add_definitions(-DVERSION_PATCH=${VERSION_PATCH})
add_definitions(-DGIT_REVISION="${GIT_REVISION}")

# Minimum Qt version
set(QT_REQUIRED_VERSION 5.9.0)

# Set default output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/result)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add compiler flags
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -fPIC)

# Enable globaly some Qt modules
find_package(Qt5 COMPONENTS
    Core
    Network
    SerialPort
    Bluetooth
    Sql
    Svg
    Gui
    Quick
    LinguistTools
    Multimedia
    Positioning
    Location
    Charts
    QuickControls2
REQUIRED)

# Common libraries
set(LIBRARIES
)

# QGamepad option
option(WITH_GAMEPAD "Compile with QGamepad module for manual input" OFF)
if(WITH_GAMEPAD)
add_definitions(-DWITH_GAMEPAD)
find_package(Qt5 COMPONENTS
    Gamepad
REQUIRED)
endif(WITH_GAMEPAD)

# Logger option
option(WITH_LOGGER "Compile with file logger instead console output")
if (WITH_LOGGER)
add_definitions(-DWITH_LOGGER)
endif(WITH_LOGGER)

# Mapbox GL option
option(WITH_MAPBOXGL "Compile with MapBox GL Qt Location plugin")
if(WITH_MAPBOXGL)
add_definitions(-DWITH_MAPBOXGL)
endif(WITH_MAPBOXGL)

# Windows stuff
if(WIN32)
set(LIBRARIES ${LIBRARIES} opengl32)
# RC compiler
string(REPLACE "gcc" "windres" CMAKE_RC_COMPILER_INIT ${CMAKE_C_COMPILER})
enable_language(RC)
set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> -O coff -o <OBJECT> <SOURCE> -I ${CMAKE_SOURCE_DIR}/platforms/windows/")

configure_file(${CMAKE_SOURCE_DIR}/platforms/windows/jagcs.rc.in ${CMAKE_CURRENT_BINARY_DIR}/jagcs.rc)
set(META_SOURCES jagcs.rc)
endif(WIN32)

# Android stuff
if(ANDROID)
find_package(Qt5AndroidExtras)
set(LIBS
    ${LIBS}
    Qt5::AndroidExtras
    android
# TODO: add to 3rd party openssl android library, avoid https://bugreports.qt.io/browse/QTBUG-57922
)
endif(ANDROID)

# 2ndparty libraries
include("${CMAKE_SOURCE_DIR}/2ndparty/industrial-controls/CMakeLists.txt")
include_directories(${INDUSTRIAL_CONTROLS_INCLUDES})

include("${CMAKE_SOURCE_DIR}/2ndparty/industrial-indicators/CMakeLists.txt")
include_directories(${INDUSTRIAL_INDICATORS_INCLUDES})

# Add Qt Creator import path
set(QML_IMPORT_PATH "${QML_IMPORT_DIRS}" CACHE STRING "Qt Creator extra qml import paths")
message(${QML_IMPORT_PATH})

# MAVLink includes
option(WITH_MAVLINK_V2 "MAVLink version 2 includes" ON)
if(WITH_MAVLINK_V2)
    include_directories("3rdparty/mavlink_v2")
    include_directories("3rdparty/mavlink_v2/ardupilotmega")
    add_definitions(-DMAVLINK_V2)
else(WITH_MAVLINK_V2)
    include_directories("3rdparty/mavlink_v1")
    include_directories("3rdparty/mavlink_v1/ardupilotmega")
endif(WITH_MAVLINK_V2)

# Internal sources
add_subdirectory(sources)

# NOTE: temporary solution for Q_NAMESPACE
# qt5_generate_moc(sources/domain/types/vehicle_types.h ${MOC_SOURCES})
qt5_wrap_cpp(MOC_SOURCES sources/domain/types/vehicle_types.h)

# Application sources
add_subdirectory(app)

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
#
# Resources
file(GLOB_RECURSE QRC_FILES "*.qrc")

# Qt5 add resources
qt5_add_resources(QRC_SOURCES
    ${QRC_FILES}
    ${INDUSTRIAL_CONTROLS_RESOURCES}
    ${INDUSTRIAL_INDICATORS_RESOURCES}
)

# Includes
include_directories(${INCLUDES})

# Target
if(ANDROID)
    include_directories(${ANDROID_SYSROOT}/usr/include)
    add_library(${PROJECT} SHARED ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${META_SOURCES}
        ${INDUSTRIAL_CONTROLS_SOURCES} ${INDUSTRIAL_INDICATORS_SOURCES})
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION
        ${VERSION_MAJOR} "." ${VERSION_MINOR} "." ${VERSION_PATCH})
else(ANDROID)
    add_executable(${PROJECT} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${META_SOURCES}
        ${INDUSTRIAL_CONTROLS_SOURCES} ${INDUSTRIAL_INDICATORS_SOURCES})
endif()

# Qt libraries
set(LIBRARIES ${LIBRARIES}
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Bluetooth
    Qt5::Sql
    Qt5::Svg
    Qt5::Gui
    Qt5::Quick
    Qt5::Multimedia
    Qt5::Positioning
    Qt5::Location
    Qt5::Charts
    Qt5::QuickControls2
)

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})

if(WITH_GAMEPAD)
qt5_use_modules(${PROJECT}
    Gamepad
)
endif(WITH_GAMEPAD)

if(ANDROID)
    set(QT_ANDROID_APP_NAME ${PROJECT_NAME})
    include(3rdparty/qt-android-cmake/AddQtAndroidApk.cmake)
    add_qt_android_apk(${PROJECT_NAME}_apk.
                        ${PROJECT_NAME}
                        NAME "JAGCS"
                        PACKAGE_NAME "mishkarogachev.jagcs"
                        PACKAGE_SOURCES ${CMAKE_SOURCE_DIR}/platforms/android
                        BUILDTOOLS_REVISION "23.0.3"
                        VERSION_CODE 5
)
endif()

# CPack Debian package
option(WITH_DEBIAN "Include instructions to make Debian package")
if(WITH_DEBIAN)
    # https://cmake.org/Bug/view.php?id=14444
    install(TARGETS ${PROJECT} DESTINATION "/usr/local/bin/")
    add_subdirectory(platforms/debian)
endif(WITH_DEBIAN)

# Tests
option(WITH_TESTS "Include tests")
if(WITH_TESTS)
    add_subdirectory(tests)
endif(WITH_TESTS)
