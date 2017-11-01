# CMake version string
cmake_minimum_required(VERSION 3.0)

# Project
set(PROJECT jagcs)
project(${PROJECT})

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Versions
set(VERSION_MAJOR 0)
set(VERSION_MINOR 4)
set(VERSION_PATCH 1)

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
    Gamepad
REQUIRED)

# Common libraries
set(LIBRARIES
)

# Windows stuff
if (WIN32)

set(LIBRARIES
    ${LIBRARIES}
    opengl32
)

set(ICON_FILE "platforms/windows/jagcs.ico")

configure_file("platforms/windows/jagcs.rc.in" "jagcs.rc")
set(RC_FILE "jagcs.rc")
set(CMAKE_RC_COMPILER_INIT windres)
enable_language(RC)
set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> <FLAGS> -O coff <DEFINES> -i <SOURCE> -o <OBJECT>")

endif(WIN32)

# Android Qt extras
if (ANDROID)
    find_package(Qt5AndroidExtras)
    set(LIBS ${LIBS} Qt5::AndroidExtras android)
endif()

# Common includes
include_directories("3rdparty/mavlink_v2")
include_directories("3rdparty/mavlink_v2/ardupilotmega")

# Internal sources
add_subdirectory(sources)

# NOTE: temporary solution for Q_NAMESPACE
# qt5_generate_moc(sources/domain/types/modes.h ${MOC_SOURCES})
qt5_wrap_cpp(MOC_SOURCES sources/domain/types/modes.h)

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

# Resources
file(GLOB_RECURSE QRC_FILES "*.qrc")

# Qt5 add resources
qt5_add_resources(QRC_SOURCES ${QRC_FILES})

include_directories(${INCLUDES})

if(ANDROID)
    include_directories(${ANDROID_SYSROOT}/usr/include)
    add_library(${PROJECT} SHARED ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${META_SOURCES})
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION
        ${VERSION_MAJOR}"."${VERSION_MINOR}"."${VERSION_PATCH})
else(ANDROID)
    # Executable target
    add_executable(${PROJECT} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${META_SOURCES})
endif()

# Link Libraries
target_link_libraries (${PROJECT} ${LIBRARIES})

# Use qt5 modules
qt5_use_modules(${PROJECT}
    Core
    Network
    SerialPort
    Sql
    Svg
    Gui
    Quick
    Multimedia
    Positioning
    Location
    Charts
    QuickControls2
    Gamepad
)

if(ANDROID)
    set (QT_ANDROID_APP_NAME ${PROJECT_NAME})
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

# Install instructions
install(TARGETS ${PROJECT} DESTINATION "/usr/bin")
install(FILES "debian/jagcs.desktop" DESTINATION "/usr/share/applications/")
install(FILES "resources/icons/jagcs.svg" DESTINATION "/usr/share/icons/")

# CPack Debian package
option(WITH_DEBIAN "Include instructions to make Debian package")
if (WITH_DEBIAN)
    add_subdirectory(platforms/debian)
endif (WITH_DEBIAN)

# Tests
option(WITH_TESTS "Include tests")
if(WITH_TESTS)
    add_subdirectory(tests)
endif(WITH_TESTS)
