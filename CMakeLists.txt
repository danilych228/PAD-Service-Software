cmake_minimum_required(VERSION 3.10)
project(MultiLanguageSDLProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2TTF REQUIRED SDL2_ttf)

# Define include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2IMAGE_LIBRARY_DIRS} ${SDL2TTF_LIBRARY_DIRS})

# Add subdirectories for each language implementation
add_subdirectory(src/c)
add_subdirectory(src/cpp)
add_subdirectory(src/asm)

# Set up installation rules
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/python/
        DESTINATION python_scripts
        FILES_MATCHING PATTERN "*.py" PATTERN "*.pyc" EXCLUDE)

# Package configuration
set(CPACK_PACKAGE_NAME "MultiLanguageSDLProject")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "developer@example.com")
set(CPACK_GENERATOR "TGZ;DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Developer")

# Include CPack module
include(CPack)