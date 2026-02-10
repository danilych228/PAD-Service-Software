cmake_minimum_required(VERSION 3.16)
project(PADHealth VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source files
set(SOURCES
    src/main.cpp
    src/monitor.cpp
    src/sensor_reader.cpp
    src/threshold_manager.cpp
    src/alert_system.cpp
    src/stats_analyzer.cpp
)

# Define header files
set(HEADERS
    src/monitor.hpp
    src/sensor_reader.hpp
    src/threshold_manager.hpp
    src/alert_system.hpp
    src/stats_analyzer.hpp
)

# Create executable
add_executable(pad-health ${SOURCES})

# Add include directories
target_include_directories(pad-health PRIVATE src)

# Link libraries
target_link_libraries(pad-health PRIVATE pthread curl mosquitto)

# Set properties for the executable
set_target_properties(pad-health PROPERTIES
    OUTPUT_NAME pad-health
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Installation
install(TARGETS pad-health
    RUNTIME DESTINATION bin
)

# Package information
set(CPACK_PACKAGE_NAME "pad-health")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "support@pad-service.ru")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PAD Service Team")

include(CPack)