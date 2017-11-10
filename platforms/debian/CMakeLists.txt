# CMake version string
cmake_minimum_required(VERSION 3.0)

# Install debian instructions
install(FILES "jagcs.sh" DESTINATION "/usr/local/bin/")
install(FILES "jagcs.desktop" DESTINATION "/usr/local/share/applications/")
install(FILES "../../resources/icons/jagcs.svg" DESTINATION "/usr/local/share/icons/")

# CPack generator type
set(CPACK_GENERATOR "DEB")

# Package information
set(CPACK_PACKAGE_NAME "JAGCS")
set(CPACK_PACKAGE_ICON "../../resources/icons/jagcs.svg")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Just Another Ground Control Station")
set(CPACK_PACKAGE_CONTACT "mishkarogachev@gmail.com")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/MishkaRogachev/JAGCS")
set(CPACK_DEBIAN_PACKAGE_SECTION "Science")

# Set package version
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})

# Scripts
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/postinst")

# This must always be last!
include(CPack)
