cmake_minimum_required(VERSION 3.10)
project(SecondMultiLanguageSDLProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

# Find SDL2 libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf>=2.0.0)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# Link directories
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_IMAGE_LIBRARY_DIRS} ${SDL2_TTF_LIBRARY_DIRS})

# Add compile options
add_definitions(${SDL2_CFLAGS_OTHER} ${SDL2_IMAGE_CFLAGS_OTHER} ${SDL2_TTF_CFLAGS_OTHER})

# Add C executable
add_executable(c_second_app src/c/main.c)
target_link_libraries(c_second_app ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set_target_properties(c_second_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Add C++ executable
add_executable(cpp_second_app src/cpp/main.cpp)
target_link_libraries(cpp_second_app ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set_target_properties(cpp_second_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Add Assembly executable
enable_language(ASM_NASM)
add_executable(asm_second_app src/asm/main.asm src/asm/helper.c)
target_link_libraries(asm_second_app ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set_target_properties(asm_second_app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Install targets
install(TARGETS c_second_app cpp_second_app asm_second_app
    RUNTIME DESTINATION bin
)

# Package settings
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "Developer <developer@example.com>")
set(CPACK_GENERATOR "DEB;TGZ")

include(CPack)