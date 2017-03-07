# CMake version string
cmake_minimum_required(VERSION 2.8.11)

# CPack generator type
set(CPACK_GENERATOR "DEB")

# Package information
set(CPACK_PACKAGE_NAME "JAGCS")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Just Another Ground Control Station")
set(CPACK_PACKAGE_CONTACT "mishkarogachev@gmail.com")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/MishkaRogachev/JAGCS")

# Set package version
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# Scripts
#set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/postinst")

# This must always be last!
include(CPack)
