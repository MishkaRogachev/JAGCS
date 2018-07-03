# CMake version string
cmake_minimum_required(VERSION 3.0)

# Project
set(PROJECT jagcs_app)
project(${PROJECT})

# Mapbox GL option
option(WITH_MAPBOXGL "Compile with MapBox GL Qt Location plugin")
if(WITH_MAPBOXGL)
add_definitions(-DWITH_MAPBOXGL)
endif(WITH_MAPBOXGL)

# Logger option
option(WITH_LOGGER "Compile with file logger instead console output")
if (WITH_LOGGER)
add_definitions(-DWITH_LOGGER)
endif(WITH_LOGGER)

# Enable Qt modules
find_package(Qt5 COMPONENTS
    Core
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

# Internal sources and headers
file(GLOB_RECURSE APP_SOURCES "*.cpp")
set(SOURCES ${SOURCES} ${APP_SOURCES} PARENT_SCOPE)

HEADER_DIRECTORIES(APP_INCLUDES ".")
set(INCLUDES ${INCLUDES} ${APP_INCLUDES} PARENT_SCOPE)

include_directories(${INCLUDES})

# Target
if(ANDROID)
    find_package(Qt5AndroidExtras)
    include_directories(${ANDROID_SYSROOT}/usr/include)

    add_library(${PROJECT} SHARED ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${META_SOURCES})
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION
        ${VERSION_MAJOR} "." ${VERSION_MINOR} "." ${VERSION_PATCH})
    set(QT_ANDROID_APP_NAME ${PROJECT_NAME})

    include(../3rdparty/qt-android-cmake/AddQtAndroidApk.cmake)
    add_qt_android_apk(${PROJECT_NAME}_apk.
                        ${PROJECT_NAME}
                        NAME "JAGCS"
                        PACKAGE_NAME "mishkarogachev.jagcs"
                        PACKAGE_SOURCES ${CMAKE_SOURCE_DIR}/platforms/android
                        BUILDTOOLS_REVISION "23.0.3"
                        VERSION_CODE 5
    )
    set(LIBS ${LIBS} Qt5::AndroidExtras android)
    # TODO: add to 3rd party openssl android library, avoid https://bugreports.qt.io/browse/QTBUG-57922
else(ANDROID)
    add_executable(${PROJECT} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${META_SOURCES})
endif(ANDROID)

# Link Libraries
target_link_libraries(${PROJECT} ${LIBRARIES})

# Use qt5 modules
qt5_use_modules(${PROJECT}
    Core
    Svg
    Gui
    Quick
    Multimedia
    Positioning
    Location
    Charts
    QuickControls2
)

if(WITH_GAMEPAD)
qt5_use_modules(${PROJECT}
    Gamepad
)
endif(WITH_GAMEPAD)
