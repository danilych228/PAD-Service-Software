# PAD-BootManager Quick Start Guide

This guide will help you get started with PAD-BootManager in just a few minutes.

## Installation

First, make sure you have PAD-BootManager installed on your system:

```bash
# Clone the repository
git clone https://github.com/pad-service/pad-bootmanager.git
cd pad-bootmanager

# Build the application
mkdir build && cd build
cmake ..
make

# Install the application (optional)
sudo make install
```

## Basic Usage

### Updating Firmware via DFU

To update firmware using DFU mode:

```bash
pad-bootmanager -d /dev/ttyACM0 -f firmware.bin -m dfu
```

### Updating Firmware via UF2

To update firmware using UF2 mode:

```bash
pad-bootmanager -f firmware.uf2 -m uf2
```

### Recovery Mode

If your device is bricked, use recovery mode:

```bash
pad-bootmanager -f firmware.bin -r
```

### Rollback to Previous Firmware

To rollback to a previous version:

```bash
pad-bootmanager -R
```

### Signature Verification

To verify a firmware signature without flashing:

```bash
pad-bootmanager -f firmware.bin -s signature.sig --check-signature
```

## Advanced Usage

### Secure Boot Configuration

Enable secure boot configuration:

```bash
pad-bootmanager -f firmware.bin --secure-boot
```

### List Connected Devices

Discover devices in bootloader mode:

```bash
pad-bootmanager --list-devices
```

### Custom Timeout

Set a custom timeout for operations:

```bash
pad-bootmanager -f firmware.bin -t 60
```

## Troubleshooting

### Device Not Found

If the device is not found, try these steps:

1. Check if the device is properly connected
2. Verify the device path with `ls /dev/tty*`
3. Make sure you have proper permissions to access the device
4. Try resetting the device to bootloader mode manually

### Signature Verification Failed

If signature verification fails:

1. Verify that the signature file matches the firmware
2. Check that the signing keys are properly configured
3. Ensure the device has the correct public key installed

## Next Steps

Now that you've completed the quick start, explore more features in our [User Guide](./user_guide.md) or check out the [API Reference](./api_reference.md).