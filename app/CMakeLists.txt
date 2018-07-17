# CMake version string
cmake_minimum_required(VERSION 3.2.1)

# Project
project(jagcs_app)

# Version message
message(STATUS "Configuring ${PROJECT_NAME}")

# QGamepad option
option(WITH_GAMEPAD "Compile with QGamepad module for manual input")
if(WITH_GAMEPAD)
    add_definitions(-DWITH_GAMEPAD)
    find_package(Qt5 COMPONENTS Gamepad REQUIRED)
endif(WITH_GAMEPAD)

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
find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    Svg
    Quick
    LinguistTools
    Multimedia
    Positioning
    Location
    Charts
    QuickControls2
)

# Enable Qt5 qml compiler
#find_package(Qt5QuickCompiler REQUIRED)

# Executable app target
add_executable(${PROJECT_NAME} "")

# Internal app includes
HEADER_DIRECTORIES(INTERNAL_INCLUDES "sources")
target_include_directories(${PROJECT_NAME} PRIVATE ${INTERNAL_INCLUDES})

# Industrial vendor sources
set(QML_IMPORT_PATH ${INDUSTRIAL_IMPORT_PATH} CACHE TYPE STRING)
target_sources(${PROJECT_NAME} PRIVATE ${INDUSTRIAL_SOURCES})

# Internal app sources and headers
file(GLOB_RECURSE SOURCES "includes/*.h" "sources/*.h" "sources/*.cpp" "sources/*.hpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# App translations
file(GLOB TS_FILES "translations/*.ts")

# Qt5 add translation sourses from translation files
qt5_add_translation(QM_FILES ${TS_FILES})

# Resources
file(GLOB_RECURSE QRC_FILES "resources/*.qrc")

# TODO: to macro 
# Create translations QRC file
set(TRANSLATIONS_QRC "${CMAKE_CURRENT_BINARY_DIR}/core_ts.qrc")
file(WRITE ${TRANSLATIONS_QRC} "<RCC>\n\t<qresource prefix=\"/\">")
foreach(QM_FILE ${QM_FILES})
    get_filename_component(QM_FILE_NAME ${QM_FILE} NAME)
    file(APPEND ${TRANSLATIONS_QRC} "\n\t\t<file alias=\"${QM_FILE_NAME}\">${QM_FILE_NAME}</file>")
endforeach()
file(APPEND ${TRANSLATIONS_QRC} "\n\t</qresource>\n</RCC>")
list(APPEND QRC_FILES ${TRANSLATIONS_QRC})

target_sources(${PROJECT_NAME} PRIVATE ${QRC_FILES})

# QML compile resources
file(GLOB_RECURSE QRC_QML_FILES "sources/presentation/qml/*.qrc")
#qtquick_compiler_add_resources(QRC_QML_SOURCES ${QRC_QML_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${QRC_QML_FILES})

# Add Qt libraries
set(QT_LIBRARIES
    Qt5::Core
    Qt5::Gui
    Qt5::Svg
    Qt5::Quick
    Qt5::Multimedia
    Qt5::Positioning
    Qt5::Location
    Qt5::Charts
    Qt5::QuickControls2
)

if(WITH_GAMEPAD)
    set(QT_LIBRARIES ${QT_LIBRARIES} Qt5::Gamepad)
endif(WITH_GAMEPAD)

# Link Libraries
target_link_libraries(${PROJECT_NAME} ${CORE} ${QT_LIBRARIES})

# Tests
if(WITH_TESTS)
#    add_subdirectory(tests)
endif(WITH_TESTS)
