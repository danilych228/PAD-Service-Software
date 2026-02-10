# Installation Guide

This document provides instructions for installing PAD-Scope on your system.

## Prerequisites

- Linux, Windows, or macOS operating system
- Logic analyzer compatible with PAD-Scope
- CMake >= 3.10
- C++17 compatible compiler (GCC, Clang, or MSVC)
- SDL2 development libraries
- Git for version control

## Installation Steps

### On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake libsdl2-dev libfftw3-dev
git clone https://github.com/pad-service/pad-scope.git
cd pad-scope
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### On Windows:
1. Install Visual Studio or MinGW with C++ support
2. Download and install CMake
3. Download and install SDL2 development libraries
4. Clone the repository:
   ```
   git clone https://github.com/pad-service/pad-scope.git
   ```
5. Build the project:
   ```
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

### On macOS:
```bash
brew install cmake sdl2 fftw
git clone https://github.com/pad-service/pad-scope.git
cd pad-scope
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

## Post-installation

After successful compilation, the executable will be available in the `bin/` directory. You can copy it to a location in your PATH for easy access.

## Troubleshooting

See the [Troubleshooting](troubleshooting.md) section for solutions to common installation issues.