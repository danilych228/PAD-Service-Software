cmake_minimum_required(VERSION 3.16)
project(PADBootManager VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files
set(SOURCES
    src/main.cpp
    src/bootloader_handler.cpp
    src/dfu_handler.cpp
    src/uf2_handler.cpp
    src/signature_verifier.cpp
)

# Define header files
set(HEADERS
    src/bootloader_handler.hpp
    src/dfu_handler.hpp
    src/uf2_handler.hpp
    src/signature_verifier.hpp
)

# Create executable
add_executable(pad-bootmanager ${SOURCES})

# Add include directories
target_include_directories(pad-bootmanager PRIVATE src)

# Link libraries
target_link_libraries(pad-bootmanager PRIVATE pthread ssl crypto)

# Set properties for the executable
set_target_properties(pad-bootmanager PROPERTIES
    OUTPUT_NAME pad-bootmanager
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Installation
install(TARGETS pad-bootmanager
    RUNTIME DESTINATION bin
)

# Package information
set(CPACK_PACKAGE_NAME "pad-bootmanager")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "support@pad-service.ru")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PAD Service Team")

include(CPack)