# CMake version string
cmake_minimum_required(VERSION 3.0)

# Internal sources and headers
file(GLOB_RECURSE INTERNAL_SOURCES "sources/*.h" "sources/*.cpp" "sources/*.hpp")
set(SOURCES ${SOURCES} ${INTERNAL_SOURCES} PARENT_SCOPE)

HEADER_DIRECTORIES(INTERNAL_INCLUDES "sources")
set(INCLUDES ${INCLUDES} ${INTERNAL_INCLUDES} PARENT_SCOPE)

# NOTE: temporary solution for Q_NAMESPACE
# qt5_generate_moc(sources/domain/types/vehicle_types.h ${MOC_SOURCES})
qt5_wrap_cpp(MOC_SOURCES sources/domain/types/vehicle_types.h)

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

# Tests
option(WITH_TESTS "Include tests")
if(WITH_TESTS)
    add_subdirectory(tests)
endif(WITH_TESTS)
