# CMakeLists.txt for C++ SDL application
cmake_minimum_required(VERSION 3.10)
project(CPP_SDL_App)

# Add executable
add_executable(cpp_sdl_app main.cpp)

# Link SDL libraries
target_link_libraries(cpp_sdl_app ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# Install rule
install(TARGETS cpp_sdl_app DESTINATION bin)