# Multi-Language SDL Project

This project demonstrates implementations of the same SDL-based graphics application in multiple programming languages: C, C++, Assembly, and Python.

## Features

- SDL-based graphics applications in multiple languages
- Consistent visual output across all implementations
- Proper CMake build system integration
- Packaging support for distribution
- Composite application to orchestrate all implementations

## Languages Implemented

1. **C Implementation** (`src/c/`)
   - Uses standard SDL2 with C11
   - Renders a blue background with a red rectangle
   
2. **C++ Implementation** (`src/cpp/`)
   - Object-oriented approach using C++17
   - Renders a green background with a yellow circle-like shape
   
3. **Assembly Implementation** (`src/asm/`)
   - x86-64 NASM assembly mixed with C
   - Renders a purple background with a white triangle
   
4. **Python Implementation** (`src/python/`)
   - Uses pygame library as SDL equivalent
   - Renders an orange background with a blue star

## Building

```bash
# Make sure you have the required dependencies
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev nasm

# Build the project
./build_package.sh
```

## Executables Location

After building, executables are located at:
- C: `build/src/c/c_sdl_app`
- C++: `build/src/cpp/cpp_sdl_app`
- Assembly: `build/src/asm/asm_sdl_app`
- Python: `src/python/sdl_app.py` (run with python3)

## Packaging

The build script creates multiple package formats:
- Self-extracting shell script: `build/MultiLanguageSDLProject-1.0.0-Linux.sh`
- Debian package: `build/MultiLanguageSDLProject-1.0.0-Linux.deb`
- Tarball archives: `build/MultiLanguageSDLProject-1.0.0-Linux.tar.*`

## Composite Application

A composite Python application (`composite_app.py`) is provided to demonstrate and orchestrate all implementations:

```bash
python3 composite_app.py
```