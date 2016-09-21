cmake_minimum_required(VERSION 3.5)
project(feh)
set(PROJECT_NAME_CAPITALIZED "feh")

# Default CFLAGS
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

include(project.cmake)

message(STATUS "Building version: ${VERSION_STRING}")

add_subdirectory(man)
add_subdirectory(share/applications)
add_subdirectory(src)

install_programs(/bin FILES src/feh)
install_files(/man FILES man/feh.1)
install_files(/doc FILES AUTHORS LICENSE ChangeLog README.md TODO)
FILE(GLOB font_files "share/fonts/*")
FILE(GLOB image_files "share/images/*")
FILE(GLOB application_files "share/applications/*.desktop")
install_files(/share/fonts FILES ${font_files})
install_files(/share/images FILES ${image_files})
install_files(/share/applications FILES ${application_files})
FILE(GLOB example_files "examples/*")
install_files(/examples FILES ${example_files})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fast and light Imlib2-based image viewer")
set(CPACK_PACKAGE_VENDOR "Tin Svagelj")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_EXECUTABLES PROJECT_NAME PROJECT_NAME_CAPITALIZED)
include(CPack)
