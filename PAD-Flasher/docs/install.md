# Installation Guide for PAD-Flasher

This guide provides instructions for installing PAD-Flasher on different operating systems.

## System Requirements

### Minimum Requirements
- Operating System: Linux (Ubuntu 18.04+, Debian 10+), macOS 10.14+, Windows 10+
- Processor: Any modern x86/ARM processor
- Memory: 512 MB RAM minimum
- Storage: 50 MB available space
- USB ports: As many as needed for connected devices

### Recommended Requirements
- Operating System: Linux (Ubuntu 20.04+, Debian 11+), macOS 11+, Windows 11
- Processor: Multi-core processor
- Memory: 2 GB RAM or more
- Storage: 100 MB available space
- USB ports: Multiple high-current ports for powering devices

## Linux Installation

### Ubuntu/Debian

#### Using APT Repository (Recommended)
```bash
# Add the PAD Service repository
curl -fsSL https://apt.pad-service.ru/pubkey.gpg | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/pad-service.gpg
echo "deb [arch=amd64] https://apt.pad-service.ru stable main" | sudo tee /etc/apt/sources.list.d/pad-service.list

# Update package list and install PAD-Flasher
sudo apt update
sudo apt install pad-flasher
```

#### Using DEB Package
```bash
# Download the latest .deb package
wget https://github.com/pad-service/pad-flasher/releases/latest/download/pad-flasher_amd64.deb

# Install the package
sudo dpkg -i pad-flasher_amd64.deb
sudo apt-get install -f  # Fix any dependency issues
```

### CentOS/RHEL/Fedora

#### Using YUM/DNF Repository
```bash
# Add the PAD Service repository
sudo curl -fsSL -o /etc/yum.repos.d/pad-service.repo https://yum.pad-service.ru/pad-service.repo

# Install PAD-Flasher
sudo dnf install pad-flasher
# or for older systems:
# sudo yum install pad-flasher
```

### Arch Linux
```bash
# Install from AUR
yay -S pad-flasher
# or
paru -S pad-flasher
```

## macOS Installation

### Using Homebrew (Recommended)
```bash
# Tap the PAD Service repository
brew tap pad-service/tools

# Install PAD-Flasher
brew install pad-flasher
```

### Using PKG Installer
1. Download the `.pkg` installer from the [releases page](https://github.com/pad-service/pad-flasher/releases)
2. Double-click the downloaded file
3. Follow the installation wizard
4. The application will be installed in `/Applications/PAD-Flasher`

### Using MacPorts
```bash
# Install using MacPorts
sudo port install pad-flasher
```

## Windows Installation

### Using MSI Installer
1. Download the `.msi` installer from the [releases page](https://github.com/pad-service/pad-flasher/releases)
2. Double-click the downloaded file
3. Follow the installation wizard
4. The application will be installed in `C:\Program Files\PAD-Flasher`

### Using Chocolatey
```powershell
# Install using Chocolatey package manager
choco install pad-flasher
```

### Using Scoop
```powershell
# Install using Scoop package manager
scoop bucket add pad-service https://github.com/pad-service/scoop-bucket
scoop install pad-flasher
```

## Building from Source

### Prerequisites
- CMake 3.16 or higher
- GCC 7+ or Clang 6+
- Git
- Development libraries:
  - libudev-dev (Linux)
  - libusb-1.0-0-dev (Linux)
  - pkg-config (Linux)

### Clone and Build
```bash
# Clone the repository
git clone https://github.com/pad-service/pad-flasher.git
cd pad-flasher

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
On Linux, you may need to add your user to the dialout group to access serial ports:

```bash
sudo usermod -a -G dialout $USER
```

Log out and back in for changes to take effect.

### Udev Rules (Linux)
For automatic device recognition, copy the udev rules:

```bash
sudo cp 99-pad-flasher.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

### Driver Installation (Windows)
Windows typically installs drivers automatically, but for some devices you may need:
- FTDI drivers for FT232 devices
- Silicon Labs drivers for CP210x devices
- CH340 drivers for CH340/CH341 devices

## Verification

Verify the installation by checking the version:

```bash
pad-flasher --version
```

You should see output similar to:
```
PAD-Flasher v1.2.3
Copyright (c) 2023 PAD Service
```

## Docker Installation

PAD-Flasher can also be run in a Docker container:

```bash
# Pull the latest image
docker pull padservice/pad-flasher:latest

# Run with USB access
docker run --rm -it --device=/dev/ttyUSB0 padservice/pad-flasher:latest --version
```

For multiple devices:
```bash
docker run --rm -it --device=/dev/ttyUSB0 --device=/dev/ttyUSB1 padservice/pad-flasher:latest pad-flasher --devices /dev/ttyUSB0,/dev/ttyUSB1 --help
```

## Troubleshooting Installation

### Permission Denied
- Check if your user is in the dialout group (Linux)
- Run with elevated privileges (not recommended for regular use)

### Missing Dependencies
- Install build-essential (Ubuntu/Debian): `sudo apt install build-essential`
- Install development headers: `sudo apt install libusb-1.0-0-dev libudev-dev`

### Repository Access Issues
- Verify internet connectivity
- Check firewall settings
- Try direct download of packages if repositories are blocked

## Uninstallation

### Linux (APT)
```bash
sudo apt remove pad-flasher
sudo apt autoremove  # Remove unused dependencies
```

### macOS (Homebrew)
```bash
brew uninstall pad-flasher
brew cleanup
```

### Windows
Uninstall through "Add or Remove Programs" or run:
```
msiexec /x {product-code}
```

## Configuration After Installation

After installation, you can configure PAD-Flasher by:
1. Creating a configuration file at `~/.config/pad-flasher/config.json` (Linux/macOS) or `%APPDATA%\PAD-Flasher\config.json` (Windows)
2. Using command-line options as needed
3. Setting up default parameters in your workflow scripts