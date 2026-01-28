# Third Implementation

This is the third implementation of our multi-language SDL project. It follows the same architecture as the previous implementations but with different visual elements.

## Languages Implemented

1. **C** - Renders a cyan background with a magenta rectangle
2. **C++** - Renders a lime green background with an orange circle
3. **Python** - Renders a pink background with a blue star using pygame
4. **Assembly (NASM)** - Renders a yellow background with a red diamond shape

## Building

To build this implementation:

```bash
./build_package.sh
```

This will:
1. Create a build directory
2. Run CMake to generate build files
3. Compile all executables
4. Package them into distributable formats

## Architecture

Each language implementation follows the same basic pattern:
- Initialize the graphics library
- Create a window
- Render specific visual elements
- Handle events (with escape/quitting functionality)
- Clean up resources

## Files Structure

- `src/c/` - C implementation
- `src/cpp/` - C++ implementation
- `src/python/` - Python implementation
- `src/asm/` - Assembly implementation
- `build_package.sh` - Build and packaging script
- `CMakeLists.txt` - CMake build configuration