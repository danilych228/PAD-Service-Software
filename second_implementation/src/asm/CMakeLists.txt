# CMakeLists.txt for Assembly SDL application
cmake_minimum_required(VERSION 3.10)
project(ASM_SDL_App)

# Enable assembly language support
enable_language(ASM_NASM)

# Check if NASM is available
find_program(NASM_FOUND nasm)
if(NOT NASM_FOUND)
    message(FATAL_ERROR "NASM assembler not found")
endif()

# Add executable for assembly program
# For x86-64 Linux, we'll create an assembly program that calls C functions
add_executable(asm_sdl_app main.asm helper.c)

# Link SDL libraries
target_link_libraries(asm_sdl_app ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Install rule
install(TARGETS asm_sdl_app DESTINATION bin)