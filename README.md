# Multi-Language SDL Project

This project demonstrates implementations of the same SDL-based graphics application in multiple programming languages: C, C++, Assembly, and Python.

## Features

- SDL-based graphics applications in multiple languages
- Consistent visual output across all implementations
- Proper CMake build system integration
- Packaging support for distribution
- Composite application to orchestrate all implementations

## Languages Implemented

### First Implementation (`src/`)
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

### Second Implementation (`second_implementation/`)
Same languages with different visual elements:
- C: Red background with cyan circle
- C++: Purple background with yellow star
- Python: Green background with red square
- Assembly: Blue background with orange diamond

### Third Implementation (`third_implementation/`)
Same languages with different visual elements:
- C: Cyan background with magenta rectangle
- C++: Lime green background with orange circle
- Python: Pink background with blue star
- Assembly: Yellow background with red diamond shape

## Building

```bash
# Make sure you have the required dependencies
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev nasm

# Build all implementations
./build_package.sh

# Or build individual implementations
cd third_implementation
./build_package.sh
```

## Executables Location

After building, executables are located at:
- First Implementation:
  - C: `build/src/c/c_sdl_app`
  - C++: `build/src/cpp/cpp_sdl_app`
  - Assembly: `build/src/asm/asm_sdl_app`
  - Python: `src/python/sdl_app.py` (run with python3)
- Second Implementation: `second_implementation/build_test/`
- Third Implementation: `third_implementation/build_test/`

## Packaging

The build script creates multiple package formats:
- Self-extracting shell script: `build/MultiLanguageSDLProject-1.0.0-Linux.sh`
- Debian package: `build/MultiLanguageSDLProject-1.0.0-Linux.deb`
- Third implementation packages: `third_implementation/build_test/MultiLanguageSDLProject-1.0.0-Linux.*`

## Composite Applications

Composite Python applications are provided to demonstrate and orchestrate implementations:

First implementation:
```bash
python3 composite_app.py
```

Third implementation:
```bash
python3 composite_third_app.py
```