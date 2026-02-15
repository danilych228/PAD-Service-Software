# CMakeLists.txt for PAD Service Core Libraries

cmake_minimum_required(VERSION 3.16)
project(pad_core_libs VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define library targets
set(CORE_LIBS_SOURCES
    pad_common.c
    pad_serial.c
    pad_network.c
    pad_crypto.c
    pad_config.c
)

# Create static library
add_library(pad_core_static STATIC ${CORE_LIBS_SOURCES})

# Create shared library
add_library(pad_core_shared SHARED ${CORE_LIBS_SOURCES})

# Set properties for shared library
set_target_properties(pad_core_shared PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    OUTPUT_NAME pad_core
)

# Set properties for static library
set_target_properties(pad_core_static PROPERTIES
    OUTPUT_NAME pad_core
)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    set_target_properties(pad_core_shared PROPERTIES
        PREFIX ""
        IMPORT_PREFIX ""
        IMPORT_SUFFIX ".lib"
    )
    
    # Additional Windows libraries
    target_link_libraries(pad_core_shared PUBLIC ws2_32)
elseif(APPLE)
    # macOS-specific settings
    set_target_properties(pad_core_shared PROPERTIES
        MACOSX_RPATH TRUE
        INSTALL_NAME_DIR "@rpath"
    )
else()
    # Linux-specific settings
    set_target_properties(pad_core_shared PROPERTIES
        LINK_FLAGS "-Wl,-z,defs"
    )
endif()

# Install targets
install(TARGETS pad_core_static pad_core_shared
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin  # For Windows DLLs
)

# Install headers
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)