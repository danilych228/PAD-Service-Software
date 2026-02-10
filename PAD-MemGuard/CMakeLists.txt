# CMakeLists.txt for PAD-MemGuard

cmake_minimum_required(VERSION 3.10)
project(PAD-MemGuard VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBDW REQUIRED libdw)
pkg_check_modules(BINUTILS REQUIRED binutils)

# Source files
set(SOURCES
    src/main.cpp
    src/tracker.cpp
    src/leak_detector.cpp
    src/overflow_protector.cpp
    src/visualizer.cpp
    src/reporter.cpp
    src/heap_analyzer.cpp
)

# Create executable
add_executable(pad-memguard ${SOURCES})

# Link libraries
target_link_libraries(pad-memguard 
    ${LIBDW_LIBRARIES}
    ${BINUTILS_LIBRARIES}
    pthread
)

# Compiler-specific options
if(MSVC)
    target_compile_options(pad-memguard PRIVATE /W4)
else()
    target_compile_options(pad-memguard PRIVATE -Wall -Wextra -pedantic)
endif()

# Install target
install(TARGETS pad-memguard DESTINATION bin)