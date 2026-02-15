# CMakeLists.txt for PAD-Trace

cmake_minimum_required(VERSION 3.10)
project(PAD-Trace VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# Source files
set(SOURCES
    src/main.cpp
    src/monitor.cpp
    src/analyzer.cpp
    src/correlator.cpp
    src/reporter.cpp
    src/sleep_analyzer.cpp
    src/event_tracker.cpp
)

# Create executable
add_executable(pad-trace ${SOURCES})

# Link libraries
target_link_libraries(pad-trace 
    ${LIBUSB_LIBRARIES}
    pthread
)

# Compiler-specific options
if(MSVC)
    target_compile_options(pad-trace PRIVATE /W4)
else()
    target_compile_options(pad-trace PRIVATE -Wall -Wextra -pedantic)
endif()

# Install target
install(TARGETS pad-trace DESTINATION bin)