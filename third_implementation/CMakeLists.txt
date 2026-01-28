cmake_minimum_required(VERSION 3.10)
project(ThirdImplementation)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})

# Add C implementation
add_executable(c_third_app src/c/main.c)
target_link_libraries(c_third_app ${SDL2_LIBRARIES})

# Add C++ implementation
add_executable(cpp_third_app src/cpp/main.cpp)
target_link_libraries(cpp_third_app ${SDL2_LIBRARIES})

# Add Assembly implementation
enable_language(ASM_NASM)
find_program(ASM_NASM_COMPILER nasm)
if(NOT ASM_NASM_COMPILER)
    message(FATAL_ERROR "NASM assembler not found")
endif()

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/main_asm.o
    COMMAND ${ASM_NASM_COMPILER} -f elf64 ${CMAKE_CURRENT_SOURCE_DIR}/src/asm/main.asm -o ${CMAKE_CURRENT_BINARY_DIR}/main_asm.o
    DEPENDS src/asm/main.asm
    COMMENT "Assembling main.asm"
)

add_executable(asm_third_app ${CMAKE_CURRENT_BINARY_DIR}/main_asm.o src/asm/sdl_helper.c)
set_target_properties(asm_third_app PROPERTIES LINK_FLAGS "-no-pie")
target_link_libraries(asm_third_app ${SDL2_LIBRARIES})

# Install targets
install(TARGETS c_third_app cpp_third_app asm_third_app
    RUNTIME DESTINATION bin
)

# Enable CPack
set(CPACK_PACKAGE_NAME "MultiLanguageSDLProject")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "developer@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Developer Name")
include(CPack)