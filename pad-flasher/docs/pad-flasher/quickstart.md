# PAD-Flasher Quick Start Guide

## Overview
PAD-Flasher is a utility for mass flashing devices through UART/JTAG/SWD interfaces. This guide will help you get started with basic flashing operations.

## Prerequisites
- Linux/macOS/Windows system
- Compatible hardware interface (UART/JTAG/SWD)
- Device firmware file (.hex/.bin/.elf format)

## Installation
```bash
# Clone the repository
git clone https://github.com/pad-service/pad-flasher.git
cd pad-flasher

# Build the application
mkdir build && cd build
cmake ..
make

# Install globally (optional)
sudo make install
```

## Basic Usage
```bash
# Flash a single device
./pad-flasher -f firmware.hex -i uart -d /dev/ttyUSB0

# Flash multiple devices in parallel
./pad-flasher -f firmware.hex -i swd -n 8

# Validate checksum after flashing
./pad-flasher -f firmware.hex -i jtag --validate
```

## Configuration
Create a config file `flash.conf`:
```ini
[device]
interface = swd
baudrate = 115200
timeout = 30

[firmware]
file = firmware.hex
validate = true
recovery_mode = true
```

Then use it:
```bash
./pad-flasher -c flash.conf
```

## Next Steps
For advanced features and protocols, see the [Protocol Specifications](protocol-specs.md) and [Batch Mode Guide](batch-mode-guide.md).