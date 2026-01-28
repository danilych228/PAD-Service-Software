#!/bin/bash

# Script to build and package the second multi-language SDL project

set -e  # Exit immediately if a command exits with a non-zero status

echo "Building Second Multi-Language SDL Project..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
echo "Building the project..."
make -j$(nproc)

# Create packaging directory if it doesn't exist
mkdir -p ../packages

# Run CPack to create packages
echo "Creating packages..."
cpack -G DEB .
cpack -G TGZ .

# Move packages to packages directory
mv *.deb ../packages/ 2>/dev/null || true
mv *.tar.gz ../packages/ 2>/dev/null || true

echo "Build and packaging completed!"
echo "Executables are in the 'build/bin' directory"
echo "Packages are in the 'packages' directory"

# List created packages
echo "Created packages:"
ls -la ../packages/ 2>/dev/null || echo "No packages created"