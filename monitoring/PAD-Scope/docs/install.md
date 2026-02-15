# Installation Guide for PAD-Scope

This guide provides instructions for installing PAD-Scope on different operating systems.

## System Requirements

### Minimum Requirements
- Operating System: Linux (Ubuntu 18.04+, Debian 10+), macOS 10.14+, Windows 10+
- Processor: Modern x86/ARM processor with SSE2 support
- Memory: 1 GB RAM minimum
- Storage: 100 MB available space
- USB port: For connecting compatible hardware
- Graphics: OpenGL 2.1 capable GPU for GUI

### Recommended Requirements
- Operating System: Linux (Ubuntu 20.04+, Debian 11+), macOS 11+, Windows 11
- Processor: Multi-core processor (Intel i5 or equivalent)
- Memory: 4 GB RAM or more
- Storage: 500 MB available space
- USB 3.0 port: For high-speed data acquisition
- Graphics: Dedicated GPU with OpenGL 3.3+ support

## Linux Installation

### Ubuntu/Debian

#### Using APT Repository (Recommended)
```bash
# Add the PAD Service repository
curl -fsSL https://apt.pad-service.ru/pubkey.gpg | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/pad-service.gpg
echo "deb [arch=amd64] https://apt.pad-service.ru stable main" | sudo tee /etc/apt/sources.list.d/pad-service.list

# Update package list and install PAD-Scope
sudo apt update
sudo apt install pad-scope
```

#### Using DEB Package
```bash
# Download the latest .deb package
wget https://github.com/pad-service/pad-scope/releases/latest/download/pad-scope_amd64.deb

# Install the package
sudo dpkg -i pad-scope_amd64.deb
sudo apt-get install -f  # Fix any dependency issues
```

### CentOS/RHEL/Fedora

#### Using YUM/DNF Repository
```bash
# Add the PAD Service repository
sudo curl -fsSL -o /etc/yum.repos.d/pad-service.repo https://yum.pad-service.ru/pad-service.repo

# Install PAD-Scope
sudo dnf install pad-scope
# or for older systems:
# sudo yum install pad-scope
```

### Arch Linux
```bash
# Install from AUR
yay -S pad-scope
# or
paru -S pad-scope
```

## macOS Installation

### Using Homebrew (Recommended)
```bash
# Tap the PAD Service repository
brew tap pad-service/tools

# Install PAD-Scope
brew install pad-scope
```

### Using PKG Installer
1. Download the `.pkg` installer from the [releases page](https://github.com/pad-service/pad-scope/releases)
2. Double-click the downloaded file
3. Follow the installation wizard
4. The application will be installed in `/Applications/PAD-Scope`

### Using MacPorts
```bash
# Install using MacPorts
sudo port install pad-scope
```

## Windows Installation

### Using MSI Installer
1. Download the `.msi` installer from the [releases page](https://github.com/pad-service/pad-scope/releases)
2. Double-click the downloaded file
3. Follow the installation wizard
4. The application will be installed in `C:\Program Files\PAD-Scope`

### Using Chocolatey
```powershell
# Install using Chocolatey package manager
choco install pad-scope
```

### Using Scoop
```powershell
# Install using Scoop package manager
scoop bucket add pad-service https://github.com/pad-service/scoop-bucket
scoop install pad-scope
```

## Building from Source

### Prerequisites
- CMake 3.16 or higher
- GCC 7+ or Clang 6+
- Git
- OpenGL development libraries
- SDL2 development libraries
- Development libraries:
  - libusb-1.0-0-dev (Linux)
  - pkg-config (Linux)

### Clone and Build
```bash
# Clone the repository
git clone https://github.com/pad-service/pad-scope.git
cd pad-scope

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compile
make -j$(nproc)

# Install (optional)
sudo make install
```

## Post-Installation Setup

### Linux Permissions
On Linux, you may need to add your user to the dialout group to access USB devices:

```bash
sudo usermod -a -G dialout $USER
```

Log out and back in for changes to take effect.

### Udev Rules (Linux)
For automatic device recognition, copy the udev rules:

```bash
sudo cp 99-pad-scope.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

### Driver Installation (Windows)
Windows typically installs drivers automatically, but for some devices you may need:
- FTDI drivers for FT232 devices
- Silicon Labs drivers for CP210x devices
- Zadig for WinUSB driver installation

## Verification

Verify the installation by checking the version:

```bash
pad-scope --version
```

You should see output similar to:
```
PAD-Scope v1.1.0
Copyright (c) 2023 PAD Service
```

## Docker Installation

PAD-Scope can also be run in a Docker container:

```bash
# Pull the latest image
docker pull padservice/pad-scope:latest

# Run with USB access (Linux)
docker run --rm -it --device=/dev/bus/usb:/dev/bus/usb padservice/pad-scope:latest --version
```

Note: GUI applications in Docker require additional X11 forwarding configuration on Linux.

## Troubleshooting Installation

### Permission Denied
- Check if your user is in the dialout group (Linux)
- Run with elevated privileges (not recommended for regular use)

### Missing Dependencies
- Install build-essential (Ubuntu/Debian): `sudo apt install build-essential`
- Install graphics libraries: `sudo apt install libsdl2-dev libgl1-mesa-dev`
- Install development headers: `sudo apt install libusb-1.0-0-dev`

### Repository Access Issues
- Verify internet connectivity
- Check firewall settings
- Try direct download of packages if repositories are blocked

## Uninstallation

### Linux (APT)
```bash
sudo apt remove pad-scope
sudo apt autoremove  # Remove unused dependencies
```

### macOS (Homebrew)
```bash
brew uninstall pad-scope
brew cleanup
```

### Windows
Uninstall through "Add or Remove Programs" or run:
```
msiexec /x {product-code}
```

## Configuration After Installation

After installation, you can configure PAD-Scope by:
1. Creating a configuration file at `~/.config/pad-scope/config.json` (Linux/macOS) or `%APPDATA%\PAD-Scope\config.json` (Windows)
2. Using command-line options as needed
3. Setting up default parameters in your workflow scripts