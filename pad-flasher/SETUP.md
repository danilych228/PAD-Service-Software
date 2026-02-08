# PAD-Flasher Environment Setup

## Overview
This document provides detailed instructions for setting up the development and runtime environment for PAD-Flasher.

## Development Environment Setup

### Prerequisites
- Git
- CMake 3.15 or higher
- C++17 compatible compiler (GCC 8+, Clang 7+, MSVC 2019+)
- Python 3.7+
- Required libraries (see INSTALL.md)

### Setting Up Development Environment

1. **Clone the Repository**
```bash
git clone https://github.com/pad-service/pad-flasher.git
cd pad-flasher
```

2. **Initialize Submodules**
```bash
git submodule update --init --recursive
```

3. **Create Virtual Environment (Recommended)**
```bash
python3 -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
pip install -r requirements-dev.txt
```

4. **Configure Build Environment**
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
```

## Runtime Environment Configuration

### System-Level Configuration

#### Linux
1. **Configure Permissions**
```bash
# Add user to necessary groups
sudo usermod -a -G dialout $USER
sudo usermod -a -G plugdev $USER
```

2. **Set up udev rules**
```bash
sudo cp contrib/99-pad-flasher.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
```

#### macOS
1. **Grant Serial Port Access**
   - Go to System Preferences > Security & Privacy > Privacy
   - Select Serial Port and add Terminal/IDE to allowed apps

2. **Install Drivers**
```bash
# For FTDI devices
brew install --cask ftdi-vcp-driver

# For Silicon Labs CP210x devices
brew install --cask cp210x-vcp-driver
```

#### Windows (WSL2)
1. **Configure WSL2 for Hardware Access**
```bash
# Add to /etc/wsl.conf
echo "[interop]" | sudo tee -a /etc/wsl.conf
echo "enabled = true" | sudo tee -a /etc/wsl.conf
echo "appendWindowsPath = false" | sudo tee -a /etc/wsl.conf

# Restart WSL2
wsl --shutdown
```

2. **Access USB Devices**
```bash
# Use USB/IP to connect host devices to WSL2
# Install USB/IP client on Windows host
# Connect device: usbipd wsl attach --busid <BUS_ID>
```

### Configuration Files

#### Main Configuration
Location: `~/.config/pad-flasher/config.ini`

```ini
[general]
# Logging configuration
log_level = INFO
log_file = ~/.local/share/pad-flasher/logs/main.log
log_max_size = 10MB
log_rotate_count = 5

# Operation timeouts
connection_timeout = 30
flash_timeout = 300
verification_timeout = 60

# Parallel operations
max_parallel_devices = 8
connection_retries = 3

[interfaces]
# Default interface settings
default_interface = swd
default_baudrate = 115200

# Interface-specific settings
uart_baudrates = 9600,19200,38400,57600,115200,230400,460800,921600
jtag_frequency = 1000000
swd_frequency = 2000000

[firmware]
# Firmware handling options
validate_after_flash = true
checksum_algorithm = crc32
backup_before_flash = true
auto_erase = true

# Supported formats
supported_formats = hex,bin,elf,srec
default_format = hex

[recovery]
# Recovery options
enabled = true
max_recovery_attempts = 3
reset_delay = 2
bootloader_delay = 5
```

#### Device Profiles
Location: `~/.config/pad-flasher/devices/`

Create device-specific configurations:
```ini
# Example: stm32f407ve.ini
[device]
name = STM32F407VE
family = STM32F4
flash_size = 524288
ram_size = 196608
flash_start = 0x08000000
ram_start = 0x20000000

[flash]
page_size = 16384
sector_size = 16384
write_timeout = 50
erase_timeout = 1000

[protocols]
supported = swd,jtag
default_protocol = swd
```

### Environment Variables

| Variable | Description | Default |
|----------|-------------|---------|
| `PAD_FLASHER_CONFIG` | Path to config file | `~/.config/pad-flasher/config.ini` |
| `PAD_FLASHER_LOG_LEVEL` | Logging level | `INFO` |
| `PAD_FLASHER_CACHE_DIR` | Cache directory | `~/.cache/pad-flasher` |
| `PAD_FLASHER_DATA_DIR` | Data directory | `~/.local/share/pad-flasher` |
| `PAD_FLASHER_TEMP_DIR` | Temp directory | System temp |
| `PAD_FLASHER_TIMEOUT` | Operation timeout | 30 seconds |

### Python Integration

If using PAD-Flasher as a Python module:

```bash
# Install in development mode
pip install -e .

# Or with extra dependencies
pip install -e ".[dev,test]"
```

Requirements file (`requirements.txt`):
```
pyyaml>=5.4.0
pyserial>=3.5
libusb1>=1.9.0
click>=8.0.0
```

### Docker Environment (Optional)

To run PAD-Flasher in a containerized environment:

1. **Build Docker Image**
```bash
docker build -t pad-flasher .
```

2. **Run with Device Access**
```bash
# For USB devices
docker run -it --device=/dev/bus/usb --group-add dialout pad-flasher

# For serial devices
docker run -it --device=/dev/ttyUSB0 --group-add dialout pad-flasher
```

Dockerfile example:
```dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libusb-1.0-0-dev \
    libftdi1-dev \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

COPY . /app
WORKDIR /app

RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make && \
    make install

ENTRYPOINT ["pad-flasher"]
```

### Testing Environment

1. **Unit Tests**
```bash
# Run unit tests
make test

# Run with coverage
make coverage
```

2. **Integration Tests**
```bash
# Requires connected hardware
make integration-test
```

3. **Hardware Simulator** (for testing without actual devices)
```bash
# Start simulator
./scripts/start-simulator.sh

# Run tests against simulator
make sim-test
```

### Troubleshooting Environment Issues

#### Common Problems:

1. **"Permission denied" accessing serial ports**
   - Add user to dialout group
   - Check udev rules
   - Restart shell after group changes

2. **"Device not found" errors**
   - Verify physical connections
   - Check device appears in `dmesg` output
   - Confirm correct interface type

3. **High CPU usage during operations**
   - Check for infinite loops in communication code
   - Verify proper timeout handling
   - Monitor system resources

#### Diagnostic Commands:
```bash
# Check environment variables
env | grep PAD

# Verify library paths
ldd $(which pad-flasher)

# Test communication with dummy device
pad-flasher --simulate --verbose
```