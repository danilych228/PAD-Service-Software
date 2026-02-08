# Installation Guide for PAD-CoreBuilder

This document provides detailed instructions for installing PAD-CoreBuilder on various operating systems.

## System Requirements

### Minimum Requirements
- Operating System: Linux, macOS, or Windows
- Processor: Dual-core, 2 GHz or faster
- RAM: 2 GB
- Disk Space: 200 MB available space
- Internet connection: For downloading dependencies

### Recommended Requirements
- Processor: Quad-core or better
- RAM: 4 GB or more
- Disk Space: 500 MB available space
- Internet connection: Broadband for faster downloads

## Installing on Linux

### Ubuntu/Debian

#### Method 1: Using DEB Package
```bash
# Download the latest release
wget https://github.com/pad-service/pad-corebuilder/releases/latest/download/pad-corebuilder_amd64.deb

# Install the package
sudo dpkg -i pad-corebuilder_amd64.deb

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

# Install PAD-CoreBuilder
sudo apt install pad-corebuilder
```

### Fedora/RHEL/CentOS

#### Using RPM Package
```bash
# Download the latest release
wget https://github.com/pad-service/pad-corebuilder/releases/latest/download/pad-corebuilder.x86_64.rpm

# Install the package
sudo rpm -i pad-corebuilder.x86_64.rpm
```

#### Using YUM/DNF Repository
```bash
# Add the PAD Service repository
sudo curl -o /etc/yum.repos.d/pad-service.repo \
  https://yum.pad-service.ru/pad-service.repo

# Install PAD-CoreBuilder
sudo dnf install pad-corebuilder
```

### Arch Linux

#### Using AUR Package
```bash
# Clone the AUR package
git clone https://aur.archlinux.org/pad-corebuilder.git
cd pad-corebuilder

# Build and install
makepkg -si
```

## Installing on macOS

### Using Homebrew
```bash
# Tap the PAD Service repository
brew tap pad-service/tap

# Install PAD-CoreBuilder
brew install pad-corebuilder
```

### Using DMG Package
1. Download the `.dmg` file from the [releases page](https://github.com/pad-service/pad-corebuilder/releases)
2. Open the downloaded file
3. Drag the `PAD-CoreBuilder` application to your Applications folder
4. Launch from Applications or Terminal

## Installing on Windows

### Using MSI Installer
1. Download the `.msi` file from the [releases page](https://github.com/pad-service/pad-corebuilder/releases)
2. Run the installer as Administrator
3. Follow the installation wizard
4. Restart your computer if prompted

### Using Chocolatey
```powershell
# Install using Chocolatey
choco install pad-corebuilder
```

## Building from Source

### Prerequisites
- Git
- CMake (3.15 or later)
- GCC/Clang or MSVC compiler
- Python 3.7 or later (for build scripts)
- SDL2 development libraries

### Build Instructions

#### On Linux/macOS
```bash
# Clone the repository
git clone https://github.com/pad-service/pad-corebuilder.git
cd pad-corebuilder

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
git clone https://github.com/pad-service/pad-corebuilder.git
cd pad-corebuilder

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
    libyaml-cpp-dev libsdl2-dev pkg-config

# For macOS
brew install cmake libusb libftdi yaml-cpp sdl2 pkg-config

# For Windows (using vcpkg)
vcpkg install libusb libftdi1 yaml-cpp sdl2
```

## Post-Installation Setup

### Verify Installation
After installation, verify that PAD-CoreBuilder is properly installed:

```bash
# Check version
pad-corebuilder --version

# Get help
pad-corebuilder --help

# List available commands
pad-corebuilder
```

### Initial Configuration
PAD-CoreBuilder will create default configuration directories on first run. To initialize your workspace:

```bash
# Create a default configuration
pad-corebuilder init --directory ~/pad-corebuilder-workspace
```

## Updating PAD-CoreBuilder

### Package Managers
Updates are handled automatically by your package manager:

```bash
# On Ubuntu/Debian
sudo apt update && sudo apt upgrade pad-corebuilder

# On Fedora/RHEL
sudo dnf update pad-corebuilder

# On macOS with Homebrew
brew upgrade pad-corebuilder

# On Windows with Chocolatey
choco upgrade pad-corebuilder
```

### Manual Updates
Download the latest release from our [GitHub releases page](https://github.com/pad-service/pad-corebuilder/releases) and reinstall using the same method you used for the initial installation.

## Troubleshooting Installation

### Common Issues

#### Missing Dependencies
```bash
# On Ubuntu/Debian
sudo apt install libusb-1.0-0 libftdi1-2 libyaml-cpp0.6 libsdl2-2.0-0

# On Fedora/RHEL
sudo dnf install libusbx libftdi yaml-cpp SDL2

# On macOS
brew install libusb libftdi yaml-cpp sdl2
```

#### Path Issues
Ensure that the installation directory is in your PATH:

```bash
# Add to ~/.bashrc or ~/.zshrc
export PATH="/usr/local/bin:$PATH"  # Linux/macOS
export PATH="C:\Program Files\PAD-CoreBuilder;$PATH"  # Windows

# Reload shell configuration
source ~/.bashrc  # or source ~/.zshrc
```

#### Permission Issues (Linux)
```bash
# Ensure proper ownership of installation directory
sudo chown -R $USER:$USER ~/.pad-corebuilder
```

## Uninstalling

### Package Manager Removal
```bash
# On Ubuntu/Debian
sudo apt remove pad-corebuilder

# On Fedora/RHEL
sudo dnf remove pad-corebuilder

# On macOS with Homebrew
brew uninstall pad-corebuilder

# On Windows with Chocolatey
choco uninstall pad-corebuilder
```

### Manual Removal
If installed from source or using archives:
- Remove the executable from your system
- Remove any configuration files in `$HOME/.config/pad-corebuilder/`
- Remove any workspace directories created

## Configuration

PAD-CoreBuilder looks for configuration files in the following locations (in order):

1. Current working directory (`./pad-corebuilder.conf`)
2. User configuration directory (`$HOME/.config/pad-corebuilder/config.json` on Linux/macOS, `%APPDATA%\pad-corebuilder\config.json` on Windows)
3. System configuration directory (`/etc/pad-corebuilder/config.json` on Linux, `/usr/local/etc/pad-corebuilder/config.json` on macOS)

Example configuration file:
```json
{
  "general": {
    "verbosity": "info",
    "log_file": "pad-corebuilder.log",
    "max_log_size": "10MB",
    "max_log_files": 5
  },
  "paths": {
    "workspace_directory": "~/pad-corebuilder-workspace",
    "templates_directory": "~/.pad-corebuilder/templates",
    "cores_directory": "~/Arduino/hardware/custom"
  },
  "export": {
    "arduino_default_path": "~/Arduino/hardware",
    "platformio_default_path": "~/.platformio/platforms"
  },
  "gui": {
    "window_width": 1200,
    "window_height": 800,
    "theme": "dark"
  }
}
```

## Getting Started

After successful installation, refer to our [Quick Start Guide](./quickstart.md) to begin using PAD-CoreBuilder.