#!/bin/bash

# Script to build and package the Multi-Language SDL Project

set -e  # Exit on any error

echo "Building Multi-Language SDL Project..."
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build all targets
echo "Building executables..."
make -j$(nproc)

echo "Build completed successfully!"
echo "Executables created:"
ls -la src/c/c_sdl_app src/cpp/cpp_sdl_app src/asm/asm_sdl_app

# Create installation package
echo "Creating installation package..."
make package

echo "Package creation completed!"
echo "Available packages:"
ls -la *.deb *.tar.* *.sh || echo "No packages found"

# Install dependencies for Python app
echo "Installing Python dependencies..."
pip3 install -r ../requirements.txt 2>/dev/null || echo "No requirements.txt found, installing pygame separately..."
pip3 install pygame

echo "To run the applications:"
echo "  C app: ./build/src/c/c_sdl_app"
echo "  C++ app: ./build/src/cpp/cpp_sdl_app" 
echo "  Assembly app: ./build/src/asm/asm_sdl_app"
echo "  Python app: python3 src/python/sdl_app.py"

cd ..