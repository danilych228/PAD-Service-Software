# CMakeLists.txt for PAD-LogView

cmake_minimum_required(VERSION 3.10)
project(PAD-LogView VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Boost REQUIRED COMPONENTS system thread)

# Source files
set(SOURCES
    src/main.cpp
    src/aggregator.cpp
    src/filter.cpp
    src/search.cpp
    src/visualizer.cpp
    src/exporter.cpp
    src/recorder.cpp
)

# Create executable
add_executable(pad-logview ${SOURCES})

# Link libraries
target_link_libraries(pad-logview 
    ${Boost_LIBRARIES}
    pthread
)

# Compiler-specific options
if(MSVC)
    target_compile_options(pad-logview PRIVATE /W4)
else()
    target_compile_options(pad-logview PRIVATE -Wall -Wextra -pedantic)
endif()

# Install target
install(TARGETS pad-logview DESTINATION bin)