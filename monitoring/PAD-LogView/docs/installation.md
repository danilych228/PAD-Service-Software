# Installation Guide

This document provides instructions for installing PAD-LogView on your system.

## Prerequisites

- Linux, Windows, or macOS operating system
- CMake >= 3.10
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Boost.Asio libraries (for networking)
- Git for version control

## Installation Steps

### On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake libboost-all-dev
git clone https://github.com/pad-service/pad-logview.git
cd pad-logview
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### On Windows:
1. Install Visual Studio or MinGW with C++ support
2. Download and install CMake
3. Install Boost libraries
4. Clone the repository:
   ```
   git clone https://github.com/pad-service/pad-logview.git
   ```
5. Build the project:
   ```
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

### On macOS:
```bash
brew install cmake boost
git clone https://github.com/pad-service/pad-logview.git
cd pad-logview
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

## Post-installation

After successful compilation, the executable will be available in the `bin/` directory. You can copy it to a location in your PATH for easy access.

## Troubleshooting

See the [Troubleshooting](troubleshooting.md) section for solutions to common installation issues.