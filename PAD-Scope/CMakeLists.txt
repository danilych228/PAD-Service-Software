cmake_minimum_required(VERSION 3.16)
project(PADScope VERSION 1.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

# Find SDL2 using pkg-config if available, otherwise find_package
if(PKG_CONFIG_FOUND)
    pkg_check_modules(SDL2 sdl2)
    pkg_check_modules(SDL2_IMAGE SDL2_image)
endif()

# If pkg-config didn't find SDL2, try find_package
if(NOT SDL2_FOUND)
    find_package(SDL2 REQUIRED)
endif()

# Define source files
set(SOURCES
    src/main.cpp
)

# Define header files
set(HEADERS
)

# Create executable
add_executable(pad-scope ${SOURCES})

# Add include directories
target_include_directories(pad-scope PRIVATE src)

# Link libraries
target_link_libraries(pad-scope PRIVATE 
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    m  # math library for sin/cos functions
)

# Add SDL2 include directories
target_include_directories(pad-scope PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Set compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(pad-scope PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(pad-scope PRIVATE /W4)
endif()

# Set properties for the executable
set_target_properties(pad-scope PROPERTIES
    OUTPUT_NAME pad-scope
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Installation
install(TARGETS pad-scope
    RUNTIME DESTINATION bin
)

# Package information
set(CPACK_PACKAGE_NAME "pad-scope")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "support@pad-service.ru")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PAD Service Team")

include(CPack)