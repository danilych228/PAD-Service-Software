# Installation Guide

This document provides instructions for installing PAD-Trace on your system.

## Prerequisites

- Linux, Windows, or macOS operating system
- Power monitoring hardware compatible with PAD-Trace
- CMake >= 3.10
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Libusb development libraries
- Git for version control

## Installation Steps

### On Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake libusb-1.0-0-dev
git clone https://github.com/pad-service/pad-trace.git
cd pad-trace
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### On Windows:
1. Install Visual Studio or MinGW with C++ support
2. Download and install CMake
3. Install libusb development libraries
4. Clone the repository:
   ```
   git clone https://github.com/pad-service/pad-trace.git
   ```
5. Build the project:
   ```
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

### On macOS:
```bash
brew install cmake libusb
git clone https://github.com/pad-service/pad-trace.git
cd pad-trace
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

## Post-installation

After successful compilation, the executable will be available in the `bin/` directory. You can copy it to a location in your PATH for easy access.

## Troubleshooting

See the [Troubleshooting](troubleshooting.md) section for solutions to common installation issues.