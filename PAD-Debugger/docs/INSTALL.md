# Installation Guide for PAD-Debugger

This document provides detailed instructions for installing PAD-Debugger on various operating systems.

## System Requirements

### Minimum Requirements
- Operating System: Linux, macOS, or Windows
- Processor: Dual-core, 2 GHz or faster
- RAM: 4 GB
- Disk Space: 200 MB available space
- USB Port: For connecting debugging hardware
- Graphics: OpenGL 2.1+ capable GPU for visualization features

### Recommended Requirements
- Processor: Quad-core or better
- RAM: 8 GB or more
- Disk Space: 500 MB available space
- USB 3.0 ports (for faster trace data transfer)
- Dedicated USB controller for debugging devices
- Graphics: OpenGL 3.3+ capable GPU with hardware acceleration

## Installing on Linux

### Ubuntu/Debian

#### Method 1: Using DEB Package
```bash
# Download the latest release
wget https://github.com/pad-service/pad-debugger/releases/latest/download/pad-debugger_amd64.deb

# Install the package
sudo dpkg -i pad-debugger_amd64.deb

# Fix any dependency issues
sudo apt-get install -f
```

#### Method 2: Using APT Repository
```bash
# Add the PAD Service repository
curl -fsSL https://apt.pad-service.ru/gpg.key | sudo gpg --dearmor -o /usr/share/keyrings/pad-service-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/pad-service-archive-keyring.gpg] https://apt.pad-service.ru/ stable main" | sudo tee /etc/apt/sources.list.d/pad-service.list

# Update package list
sudo apt update

# Install PAD-Debugger
sudo apt install pad-debugger
```

### Fedora/RHEL/CentOS

#### Using RPM Package
```bash
# Download the latest release
wget https://github.com/pad-service/pad-debugger/releases/latest/download/pad-debugger.x86_64.rpm

# Install the package
sudo rpm -i pad-debugger.x86_64.rpm
```

#### Using YUM/DNF Repository
```bash
# Add the PAD Service repository
sudo curl -o /etc/yum.repos.d/pad-service.repo \
  https://yum.pad-service.ru/pad-service.repo

# Install PAD-Debugger
sudo dnf install pad-debugger
```

### Arch Linux

#### Using AUR Package
```bash
# Clone the AUR package
git clone https://aur.archlinux.org/pad-debugger.git
cd pad-debugger

# Build and install
makepkg -si
```

## Installing on macOS

### Using Homebrew
```bash
# Tap the PAD Service repository
brew tap pad-service/tap

# Install PAD-Debugger
brew install pad-debugger
```

### Using DMG Package
1. Download the `.dmg` file from the [releases page](https://github.com/pad-service/pad-debugger/releases)
2. Open the downloaded file
3. Drag the `PAD-Debugger` application to your Applications folder
4. Launch from Applications or Terminal

### Using MacPorts
```bash
# Install using MacPorts
sudo port install pad-debugger
```

## Installing on Windows

### Using MSI Installer
1. Download the `.msi` file from the [releases page](https://github.com/pad-service/pad-debugger/releases)
2. Run the installer as Administrator
3. Follow the installation wizard
4. Restart your computer if prompted

### Using Chocolatey
```powershell
# Install using Chocolatey
choco install pad-debugger
```

### Using Scoop
```powershell
# Add the extras bucket if not already added
scoop bucket add extras

# Install PAD-Debugger
scoop install pad-debugger
```

## Building from Source

### Prerequisites
- Git
- CMake (3.15 or later)
- GCC/Clang or MSVC compiler
- Python 3.7 or later (for build scripts)
- SDL2 development libraries
- OpenGL development libraries
- libusb development libraries
- libftdi development libraries

### Build Instructions

#### On Linux/macOS
```bash
# Clone the repository
git clone https://github.com/pad-service/pad-debugger.git
cd pad-debugger

# Create build directory
mkdir build && cd build

# Configure the build
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compile
make -j$(nproc)

# Install (optional)
sudo make install
```

#### On Windows
```powershell
# Clone the repository
git clone https://github.com/pad-service/pad-debugger.git
cd pad-debugger

# Create build directory
mkdir build && cd build

# Configure the build (using Visual Studio Developer Command Prompt)
cmake .. -G "Visual Studio 16 2019" -A x64 -DCMAKE_BUILD_TYPE=Release

# Compile
cmake --build . --config Release

# Install (optional)
cmake --install .
```

### Additional Dependencies for Development
```bash
# For Linux
sudo apt install build-essential cmake libusb-1.0-0-dev libftdi1-dev \
    libsdl2-dev libgl1-mesa-dev pkg-config

# For macOS
brew install cmake libusb libftdi sdl2 pkg-config

# For Windows (using vcpkg)
vcpkg install libusb libftdi1 sdl2
```

## Post-Installation Setup

### Linux Permissions
To avoid needing sudo for each operation, add your user to the appropriate groups:

```bash
# Add user to dialout group for serial port access
sudo usermod -a -G dialout $USER

# Add user to plugdev group for USB device access
sudo usermod -a -G plugdev $USER

# Create udev rules for common debug adapters
sudo tee /etc/udev/rules.d/99-pad-debugger.rules << EOF
# CMSIS-DAP devices
SUBSYSTEM=="usb", ATTR{idVendor}=="0d28", ATTR{idProduct}=="0204", MODE="0666"
# J-Link devices
SUBSYSTEM=="usb", ATTR{idVendor}=="1366", ATTR{idProduct}=="*", MODE="0666"
# ST-Link devices
SUBSYSTEM=="usb", ATTR{idVendor}=="0483", ATTR{idProduct}=="3748", MODE="0666"
# Black Magic Probe
SUBSYSTEM=="usb", ATTR{idVendor}=="1d50", ATTR{idProduct}=="6018", MODE="0666"
EOF

# Reload udev rules
sudo udevadm control --reload-rules
sudo udevadm trigger

# Log out and back in for changes to take effect
```

### Windows Drivers
For certain debug adapters, you may need to install drivers:
- J-Link devices: Install SEGGER J-Link drivers
- ST-Link devices: Install STM32 ST-Link drivers
- CMSIS-DAP devices: Usually work without additional drivers
- Black Magic Probe: Install libusb drivers

## Verification

After installation, verify that PAD-Debugger is properly installed:

```bash
# Check version
pad-debugger --version

# Get help
pad-debugger --help

# List supported RTOS
pad-debugger --list-rtos
```

## Updating PAD-Debugger

### Package Managers
Updates are handled automatically by your package manager:

```bash
# On Ubuntu/Debian
sudo apt update && sudo apt upgrade pad-debugger

# On Fedora/RHEL
sudo dnf update pad-debugger

# On macOS with Homebrew
brew upgrade pad-debugger

# On Windows with Chocolatey
choco upgrade pad-debugger
```

### Manual Updates
Download the latest release from our [GitHub releases page](https://github.com/pad-service/pad-debugger/releases) and reinstall using the same method you used for the initial installation.

## Troubleshooting Installation

### Common Issues

#### Permission Errors on Linux
```bash
# Check current user groups
groups $USER

# Manually add to required groups
sudo usermod -a -G dialout,plugdev $USER

# Check udev rules
lsusb  # Look for your debug adapter
ls -la /dev/bus/usb/*/  # Check permissions
```

#### Missing Dependencies
```bash
# On Ubuntu/Debian
sudo apt install libusb-1.0-0 libsdl2-2.0-0 libgl1-mesa-glx

# On Fedora/RHEL
sudo dnf install libusbx SDL2 mesa-libGL

# On macOS
brew install libusb sdl2
```

#### Graphics Issues
If you experience graphics-related issues:
```bash
# Force software rendering
pad-debugger --software-rendering --target firmware.elf

# Check OpenGL version
glxinfo | grep "OpenGL version"
```

#### Path Issues
Ensure that the installation directory is in your PATH:

```bash
# Add to ~/.bashrc or ~/.zshrc
export PATH="/usr/local/bin:$PATH"  # Linux/macOS
export PATH="C:\\Program Files\\PAD-Debugger;$PATH"  # Windows

# Reload shell configuration
source ~/.bashrc  # or source ~/.zshrc
```

## Uninstalling

### Package Manager Removal
```bash
# On Ubuntu/Debian
sudo apt remove pad-debugger

# On Fedora/RHEL
sudo dnf remove pad-debugger

# On macOS with Homebrew
brew uninstall pad-debugger

# On Windows with Chocolatey
choco uninstall pad-debugger
```

### Manual Removal
If installed from source or using archives:
- Remove the executable from your system
- Remove any configuration files in `$HOME/.config/pad-debugger/`
- Remove any desktop integration files
- Remove udev rules if created during installation

## Configuration

PAD-Debugger looks for configuration files in the following locations (in order):

1. Current working directory (`./pad-debugger.conf`)
2. User configuration directory (`$HOME/.config/pad-debugger/config.yaml` on Linux/macOS, `%APPDATA%\pad-debugger\config.yaml` on Windows)
3. System configuration directory (`/etc/pad-debugger/config.yaml` on Linux, `/usr/local/etc/pad-debugger/config.yaml` on macOS)

Example configuration file:
```yaml
# config.yaml
debugger:
  interface: swd
  adapter: cmsis-dap
  speed: 4000
  swo_baudrate: 2000000
  rtos: freertos

target:
  elf_file: firmware.elf
  reset_strategy: hw_reset
  halt_after_reset: true

visualization:
  task_view_enabled: true
  timeline_resolution: 100ms
  memory_map_display: true
  software_rendering: false

logging:
  level: info
  file: pad-debugger.log
  max_size: 10MB
  max_files: 5
```

## Getting Started

After successful installation, refer to our [Quick Start Guide](./quickstart.md) to begin using PAD-Debugger.