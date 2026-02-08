cmake_minimum_required(VERSION 3.16)
project(PADFlasher VERSION 1.2.3 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files
set(SOURCES
    src/main.cpp
    src/protocols/uart.cpp
)

# Define header files
set(HEADERS
    src/protocols/uart.h
)

# Create executable
add_executable(pad-flasher ${SOURCES})

# Add include directories
target_include_directories(pad-flasher PRIVATE src)

# Link libraries
target_link_libraries(pad-flasher PRIVATE pthread)

# Set properties for the executable
set_target_properties(pad-flasher PROPERTIES
    OUTPUT_NAME pad-flasher
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Installation
install(TARGETS pad-flasher
    RUNTIME DESTINATION bin
)

# Package information
set(CPACK_PACKAGE_NAME "pad-flasher")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "support@pad-service.ru")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PAD Service Team")

include(CPack)