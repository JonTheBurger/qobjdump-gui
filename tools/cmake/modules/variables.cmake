# Set project-wide variables
include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CPACK_PACKAGE_VENDOR "jontheburger")
set(CPACK_PACKAGE_CONTACT "${CPACK_PACKAGE_VENDOR} <${CPACK_PACKAGE_VENDOR}@gmail.com>")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_STRIP_FILES ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT AND ${PROJECT_NAME}_DEVELOPER_MODE)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "")
endif()

# PACKAGING: DEB
string(TOLOWER "${PROJECT_NAME}" CPACK_DEBIAN_PACKAGE_NAME)
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
