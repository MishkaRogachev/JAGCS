# CMake version string
cmake_minimum_required(VERSION 3.0)

# Windows libraries
set(LIBRARIES ${LIBRARIES} opengl32 PARENT_SCOPE)

# RC compiler
string(REPLACE "gcc" "windres" CMAKE_RC_COMPILER_INIT ${CMAKE_C_COMPILER})
enable_language(RC)
set(CMAKE_RC_COMPILE_OBJECT "<CMAKE_RC_COMPILER> -O coff -o <OBJECT> <SOURCE> -I ${CMAKE_SOURCE_DIR}/platforms/windows/")

configure_file(${CMAKE_SOURCE_DIR}/jagcs.rc.in ${CMAKE_CURRENT_BINARY_DIR}/jagcs.rc)
set(META_SOURCES jagcs.rc)
