# PAD-Flasher Installation Guide

## System Requirements
- Operating System: Linux (Ubuntu 18.04+, Debian 10+), macOS 10.14+, Windows 10/11 (WSL2)
- Architecture: x86_64, ARM64
- RAM: Minimum 2GB recommended
- Storage: 50MB for core application + space for firmware files
- User privileges: Access to serial ports (UART) and GPIO (JTAG/SWD) interfaces

## Dependencies

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    git \
    libusb-1.0-0-dev \
    libftdi1-dev \
    libhidapi-dev \
    pkg-config \
    python3 \
    python3-pip \
    python3-venv
```

### CentOS/RHEL/Fedora
```bash
sudo dnf install -y \
    gcc gcc-c++ make \
    cmake \
    git \
    libusb-devel \
    libftdi-devel \
    hidapi-devel \
    python3 \
    python3-pip
```

### macOS
```bash
# Install Homebrew if not present
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install \
    cmake \
    libusb \
    libftdi \
    hidapi \
    python3
```

### Windows (WSL2)
```bash
# Enable WSL2 and install Ubuntu from Microsoft Store
# Then follow Ubuntu/Debian instructions above
```

## Installation Methods

### Method 1: From Source (Recommended)
```bash
# Clone the repository
git clone https://github.com/pad-service/pad-flasher.git
cd pad-flasher

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Compile the application
make -j$(nproc)

# Install system-wide (optional)
sudo make install

# Or install to custom location
cmake .. -DCMAKE_INSTALL_PREFIX=/path/to/custom/location
make install
```

### Method 2: Using Package Manager (Linux)

#### Debian/Ubuntu Package
```bash
# Download the latest .deb package from releases
wget https://github.com/pad-service/pad-flasher/releases/latest/download/pad-flasher_amd64.deb

# Install the package
sudo dpkg -i pad-flasher_amd64.deb

# Fix any dependency issues
sudo apt-get install -f
```

#### RPM Package (Fedora/CentOS)
```bash
# Download the latest .rpm package from releases
wget https://github.com/pad-service/pad-flasher/releases/latest/download/pad-flasher.x86_64.rpm

# Install the package
sudo rpm -i pad-flasher.x86_64.rpm
```

### Method 3: Python Package (Alternative)
```bash
# Create virtual environment
python3 -m venv pad-flasher-env
source pad-flasher-env/bin/activate  # On Windows: pad-flasher-env\Scripts\activate

# Install as Python package
pip install git+https://github.com/pad-service/pad-flasher.git
```

## Post-Installation Setup

### Add User to Required Groups (Linux)
```bash
# Add user to dialout group for serial port access
sudo usermod -a -G dialout $USER

# Add user to plugdev group for USB device access
sudo usermod -a -G plugdev $USER

# For systems without plugdev, use uucp instead
sudo usermod -a -G uucp $USER
```

### Udev Rules (Linux)
Create udev rules for automatic device permissions:
```bash
# Create udev rule file
sudo tee /etc/udev/rules.d/99-pad-flasher.rules << EOF
# Allow access to serial devices for flashing
SUBSYSTEM=="tty", ATTRS{idVendor}=="*", ATTRS{idProduct}=="*", MODE="0666"

# Allow access to USB devices for JTAG/SWD interfaces
SUBSYSTEM=="usb", ATTRS{idVendor}=="*", ATTRS{idProduct}=="*", MODE="0666", GROUP="plugdev"
EOF

# Reload udev rules
sudo udevadm control --reload-rules
sudo udevadm trigger
```

### Verify Installation
```bash
# Check if the command is available
pad-flasher --version

# Get help information
pad-flasher --help

# Test basic functionality
pad-flasher --list-interfaces
```

## Configuration

### Global Configuration File
PAD-Flasher looks for configuration in these locations (in order):
1. `./pad-flasher.conf` (current directory)
2. `~/.config/pad-flasher.conf` (user config)
3. `/etc/pad-flasher.conf` (system config)

Example configuration file:
```ini
[general]
log_level = INFO
timeout = 30
parallel_connections = 8

[interface]
default_baudrate = 115200
uart_timeout = 10
jtag_frequency = 1000000
swd_frequency = 1000000

[firmware]
validate_after_flash = true
checksum_algorithm = crc32
recovery_enabled = true
```

### Environment Variables
- `PAD_FLASHER_CONFIG`: Path to custom configuration file
- `PAD_FLASHER_LOG_LEVEL`: Override log level (DEBUG, INFO, WARNING, ERROR)
- `PAD_FLASHER_TIMEOUT`: Override timeout value in seconds

## Troubleshooting

### Common Issues

1. **Permission Denied Errors**
   - Ensure user is in dialout/plugdev groups
   - Check udev rules are properly installed
   - Restart session after adding user to groups

2. **Device Not Found**
   - Verify device is properly connected
   - Check device appears in `lsusb` or `dmesg` output
   - Confirm correct interface type and port

3. **Slow Flashing Speed**
   - Check connection quality
   - Try lower baudrate for UART
   - Verify stable power supply to target device

### Diagnostic Commands
```bash
# List available interfaces
pad-flasher --list-interfaces

# Scan for connected devices
pad-flasher --scan

# Show detailed version and build info
pad-flasher --version --verbose
```

## Uninstallation

### From Source Installation
```bash
# If installed with 'make install'
sudo make uninstall  # from build directory

# Or manually remove installed files
sudo rm /usr/local/bin/pad-flasher
sudo rm -rf /usr/local/share/pad-flasher
sudo rm /usr/local/man/man1/pad-flasher.1
```

### From Package Manager
```bash
# Debian/Ubuntu
sudo dpkg -r pad-flasher

# RPM-based systems
sudo rpm -e pad-flasher
```