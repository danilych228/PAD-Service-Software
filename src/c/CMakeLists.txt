# CMakeLists.txt for C SDL application
cmake_minimum_required(VERSION 3.10)
project(C_SDL_App)

# Add executable
add_executable(c_sdl_app main.c)

# Link SDL libraries
target_link_libraries(c_sdl_app ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Install rule
install(TARGETS c_sdl_app DESTINATION bin)