# CMake version string
cmake_minimum_required(VERSION 3.0)

# Project
project(jagcs)

# CMake modules
include(cmake/RecurseSubdirs.cmake)

# Versions
set(VERSION_MAJOR 0)
set(VERSION_MINOR 6)
set(VERSION_PATCH 0)

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

# Version message
message(STATUS "${PROJECT_NAME} ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}(${GIT_REVISION})")

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

# Targets
add_subdirectory(core)
#add_subdirectory(plugins)
#add_subdirectory(app)

# Windows stuff
if(WIN32)
    add_subdirectory(platforms/windows)
endif(WIN32)

# CPack Debian package
option(WITH_DEBIAN "Include instructions to make Debian package")
if(WITH_DEBIAN)
    # https://cmake.org/Bug/view.php?id=14444
    install(TARGETS ${PROJECT_NAME} DESTINATION "/usr/local/bin/")
    add_subdirectory(platforms/debian)
endif(WITH_DEBIAN)
