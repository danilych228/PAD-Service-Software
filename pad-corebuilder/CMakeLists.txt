cmake_minimum_required(VERSION 3.12)
project(pad-corebuilder)

# Default to C11
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable targets
add_executable(c_pad_corebuilder src/c/main.c)
add_executable(cpp_pad_corebuilder src/cpp/main.cpp)
add_executable(python_pad_corebuilder src/python/main.py)

# Set properties for Python executable
set_target_properties(python_pad_corebuilder PROPERTIES
    LINKER_LANGUAGE C  # This tells CMake not to try to link anything to the Python script
)

# Add any necessary include directories
target_include_directories(c_pad_corebuilder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/c)
target_include_directories(cpp_pad_corebuilder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp)

# Link libraries if needed (for future expansion)
target_link_libraries(c_pad_corebuilder)
target_link_libraries(cpp_pad_corebuilder)

# Installation rules
install(TARGETS c_pad_corebuilder cpp_pad_corebuilder
    RUNTIME DESTINATION bin
)

# Install Python script
install(PROGRAMS src/python/main.py
    DESTINATION bin
    RENAME pad-corebuilder-python
)

# Add custom target to build all versions
add_custom_target(build_all
    DEPENDS c_pad_corebuilder cpp_pad_corebuilder
)