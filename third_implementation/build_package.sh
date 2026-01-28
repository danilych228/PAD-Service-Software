#!/bin/bash

# Build script for Third Implementation

set -e  # Exit on any error

echo "Building Third Implementation..."

# Create build directory
mkdir -p build_test
cd build_test

# Run CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
make -j$(nproc)

# Create distribution package using CPack
cpack -G DEB .
cpack -G STGZ .

echo "Build and packaging completed successfully!"
echo "Output files:"
ls -la *.deb *.sh *.tar.*

# Go back to original directory
cd ..