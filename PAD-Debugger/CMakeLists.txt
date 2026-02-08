cmake_minimum_required(VERSION 3.15)
project(pad-debugger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/main.cpp
    src/debugger_core.cpp
    src/rtos_integrator.cpp
)

# Create executable
add_executable(pad-debugger ${SOURCES})

# Link libraries
target_link_libraries(pad-debugger 
    ${SDL2_LIBRARIES}
    pthread
    usb-1.0
    ftdi1
)

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(pad-debugger PRIVATE -Wall -Wextra -O3)
elseif(MSVC)
    target_compile_options(pad-debugger PRIVATE /W4 /O2)
endif()

# Installation
install(TARGETS pad-debugger
    RUNTIME DESTINATION bin
)

# Package generation
set(CPACK_PACKAGE_NAME "pad-debugger")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "PAD-Debugger: RTOS-aware embedded debugging tool")
set(CPACK_PACKAGE_CONTACT "support@pad-service.ru")

# Determine system architecture
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE "x86_64")
else()
    set(ARCHITECTURE "x86")
endif()

# Set package file name based on system
if(WIN32)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-windows-${ARCHITECTURE}")
elseif(APPLE)
    set(CPACK_GENERATOR "TGZ")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-macos-${ARCHITECTURE}")
else()
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PAD Service <support@pad-service.ru>")
    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION}")
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${ARCHITECTURE})
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
    set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
    set(CPACK_RPM_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION}")
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-linux-${ARCHITECTURE}")
endif()

include(CPack)