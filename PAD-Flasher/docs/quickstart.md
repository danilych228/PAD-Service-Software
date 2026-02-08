# Quick Start Guide for PAD-Flasher

This guide will help you get started with PAD-Flasher in just 5 minutes.

## Prerequisites

- Linux/macOS/Windows system
- USB-to-Serial adapter or JTAG/SWD programmer
- Target device with accessible UART/JTAG/SWD pins
- Firmware binary file (.bin or .hex format)

## Installation

For detailed installation instructions, please see the [Installation Guide](./install.md).

## Basic Usage

1. Connect your device(s) to the computer via UART/JTAG/SWD interface(s)
2. Identify the communication port(s):
   - Linux: `/dev/ttyUSB0`, `/dev/ttyACM0`, etc.
   - macOS: `/dev/tty.usbserial-*`, `/dev/cu.usbserial-*`, etc.
   - Windows: `COM1`, `COM2`, etc.
3. Run the flasher with basic parameters:

```bash
pad-flasher --device /dev/ttyUSB0 --firmware my_firmware.bin --protocol uart
```

## Parallel Flashing

To flash multiple devices simultaneously:

```bash
pad-flasher --devices /dev/ttyUSB0,/dev/ttyUSB1,/dev/ttyUSB2 --firmware my_firmware.bin --protocol uart
```

## Protocol Selection

PAD-Flasher supports multiple protocols:
- `uart` - Standard UART bootloader protocol
- `jtag` - JTAG interface protocol
- `swd` - Serial Wire Debug protocol
- `spi` - SPI bootloader protocol

Example with JTAG:
```bash
pad-flasher --device /dev/ttyUSB0 --firmware my_firmware.bin --protocol jtag
```

## Validation

By default, PAD-Flasher validates the flashed content against the original firmware. To skip validation:
```bash
pad-flasher --device /dev/ttyUSB0 --firmware my_firmware.bin --protocol uart --skip-validation
```

## Recovery Mode

In case of a bricked device, use recovery mode:
```bash
pad-flasher --device /dev/ttyUSB0 --firmware my_firmware.bin --protocol uart --recovery
```

## Next Steps

- Learn about [Protocol Specifications](./protocol_specs.md)
- Explore [Batch Mode Guide](./batch_mode_guide.md)
- Check out [Troubleshooting Guide](./troubleshooting.md)