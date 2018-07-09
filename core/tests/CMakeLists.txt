# CMake version string
cmake_minimum_required(VERSION 3.0)

# Project
project(core_tests)

# Version message
message(STATUS "Configuring ${PROJECT_NAME}")

# Enable Qt modules
find_package(Qt5 COMPONENTS Test REQUIRED)

# Includes
HEADER_DIRECTORIES(TEST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${TEST_INCLUDES})

# Test sources
file(GLOB_RECURSE TEST_SOURCES "*.h" "*.cpp")

# Executable
add_executable(${PROJECT_NAME} "")
#set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

# Includes
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

# Internal includes
HEADER_DIRECTORIES(TEST_INCLUDES "./")
target_include_directories(${PROJECT_NAME} PRIVATE ${TEST_INCLUDES})

# Sources
file(GLOB_RECURSE TEST_SOURCES "*.cpp" "*.hpp")
target_sources(${PROJECT_NAME} PRIVATE ${TEST_SOURCES})

# Add Qt test library
set(QT_LIBRARIES ${QT_LIBRARIES} Qt5::Test)

# Link Libraries
target_link_libraries(${PROJECT_NAME} ${CORE} ${QT_LIBRARIES})

# Tests
add_test (NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
