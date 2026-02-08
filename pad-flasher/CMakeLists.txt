cmake_minimum_required(VERSION 3.15)
project(pad-flasher LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Define version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# Find required packages
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)

if(NOT WIN32)
    find_library(LIBUSB_LIBRARIES usb-1.0)
    find_library(LIBFTDI_LIBRARIES ftdi1)
    find_path(LIBUSB_INCLUDE_DIRS libusb-1.0/libusb.h)
    find_path(LIBFTDI_INCLUDE_DIRS NAMES ftdi.h PATH_SUFFIXES libftdi1 ftdi)
endif()

# Add executable targets
add_executable(pad-flasher-c src/c/main.c)
add_executable(pad-flasher-cpp src/cpp/main.cpp)

# For Python, we'll just copy the script
configure_file(src/python/main.py pad-flasher-python.py COPYONLY)

# For the assembly version, we need to handle it differently
# Since NASM is typically used for assembly files, we'll create a custom target
enable_language(ASM_NASM)
add_custom_target(pad-flasher-asm
    COMMAND nasm -f elf64 src/asm/flasher.asm -o ${CMAKE_BINARY_DIR}/flasher.o
    COMMAND ld ${CMAKE_BINARY_DIR}/flasher.o -o pad-flasher-asm -lc
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Building assembly version of pad-flasher"
)

# Set properties for the assembly executable
set_target_properties(pad-flasher-asm PROPERTIES
    OUTPUT_NAME pad-flasher-asm
)

# Link libraries for C version
target_link_libraries(pad-flasher-c 
    Threads::Threads
    ${CMAKE_DL_LIBS}
)

# Add include directories for C version
target_include_directories(pad-flasher-c PRIVATE
    ${LIBUSB_INCLUDE_DIRS}
    ${LIBFTDI_INCLUDE_DIRS}
)

# Link libraries for C++ version
target_link_libraries(pad-flasher-cpp 
    Threads::Threads
    ${CMAKE_DL_LIBS}
)

# Add include directories for C++ version
target_include_directories(pad-flasher-cpp PRIVATE
    ${LIBUSB_INCLUDE_DIRS}
    ${LIBFTDI_INCLUDE_DIRS}
)

# Set properties for executables
set_target_properties(pad-flasher-c pad-flasher-cpp PROPERTIES
    OUTPUT_NAME pad-flasher
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)

# Install targets
install(TARGETS pad-flasher-c
    RUNTIME DESTINATION bin
    RENAME pad-flasher
)

install(TARGETS pad-flasher-cpp
    RUNTIME DESTINATION bin
    RENAME pad-flasher-cpp
)

install(FILES ${CMAKE_BINARY_DIR}/pad-flasher-python.py
    DESTINATION bin
    RENAME pad-flasher-python
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
)

# Custom install for assembly version
install(CODE "
    execute_process(COMMAND cp ${PROJECT_BINARY_DIR}/pad-flasher-asm \${CMAKE_INSTALL_PREFIX}/bin/pad-flasher-asm)
")

# Documentation install
install(DIRECTORY docs/
    DESTINATION share/doc/pad-flasher
    FILES_MATCHING PATTERN "*.md"
)

install(FILES README.md INSTALL.md SETUP.md
    DESTINATION share/doc/pad-flasher
)

# Package configuration
set(CPACK_PACKAGE_NAME "pad-flasher")
set(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "support@pad-service.ru")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

include(CPack)