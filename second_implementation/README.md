# Second Multi-Language SDL Project

This is the second implementation of a multi-language SDL project demonstrating graphics programming in different languages.

## Overview

This project demonstrates how to create SDL applications in multiple programming languages, including C, C++, Assembly, and Python. Each implementation creates a visual pattern using SDL2 graphics.

## Languages and Implementations

- **C**: Creates a cyan background with a magenta cross
- **C++**: Creates a light green background with a blue diamond shape
- **Assembly**: Creates a dark gray background with a colorful grid pattern
- **Python**: Creates a light blue background with a colorful spiral

## Prerequisites

- SDL2 development libraries
- SDL2_image development libraries
- SDL2_ttf development libraries
- CMake 3.10 or higher
- NASM assembler (for Assembly implementation)
- Python 3 with pygame library

### Installing Dependencies

On Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev nasm cmake build-essential
pip3 install pygame
```

On macOS:
```bash
brew install sdl2 sdl2_image sdl2_ttf nasm cmake
pip3 install pygame
```

## Building

To build the project:

```bash
mkdir build
cd build
cmake ..
make
```

## Running

After building, you can run the individual implementations:

```bash
# Run C implementation
./bin/c_second_app

# Run C++ implementation
./bin/cpp_second_app

# Run Assembly implementation
./bin/asm_second_app

# Run Python implementation
python3 src/python/sdl_app.py
```

## Architecture

Each implementation follows a similar structure:
- Initializes SDL
- Creates a window and renderer
- Runs a main loop that handles events and renders graphics
- Cleans up resources upon exit

The Assembly implementation uses a combination of NASM assembly and C helper functions, since SDL is a C library.