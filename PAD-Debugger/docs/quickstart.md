# Quick Start Guide for PAD-Debugger

This guide will help you get started with PAD-Debugger in just 5 minutes.

## Prerequisites

- Linux/macOS/Windows operating system
- Debug adapter (CMSIS-DAP, J-Link, ST-Link, etc.)
- Target board with debugging interface enabled
- ELF firmware file for debugging
- At least 4GB free disk space
- User permissions to access USB devices

## Installation

1. Download the latest release from our [releases page](https://github.com/pad-service/pad-debugger/releases)
2. Extract the archive to your preferred location
3. Add the executable to your PATH or run directly from the extracted folder

For Linux/macOS:
```bash
tar -xf pad-debugger-x.x.x.tar.gz
cd pad-debugger
sudo ./install.sh
```

For Windows:
1. Run the installer executable as Administrator
2. Follow the installation wizard

## Basic Usage

### Connect to Target Device

```bash
# Connect using SWD interface with CMSIS-DAP adapter
pad-debugger --target firmware.elf --interface swd --adapter cmsis-dap

# Connect using JTAG interface
pad-debugger --target firmware.elf --interface jtag --adapter jlink

# Connect with specific serial number
pad-debugger --target firmware.elf --adapter "J-Link serial=123456789"
```

### Start Debugging Session

```bash
# Load firmware and start debugging
pad-debugger --load --target firmware.elf --interface swd --adapter cmsis-dap

# Start debugging without loading firmware
pad-debugger --attach --target firmware.elf --interface swd --adapter cmsis-dap
```

### RTOS Support

```bash
# Enable FreeRTOS awareness
pad-debugger --rtos freertos --target firmware.elf --interface swd

# Enable Zephyr RTOS awareness
pad-debugger --rtos zephyr --target firmware.elf --interface swd
```

### SWO Tracing

```bash
# Enable SWO with 2MHz baudrate
pad-debugger --swo 2000000 --target firmware.elf --interface swd

# Decode ITM channels
pad-debugger --swo 2000000 --itm-decoder --target firmware.elf --interface swd
```

## Configuration

Create a configuration file to store common parameters:

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
```

Then use it with:
```bash
pad-debugger --config config.yaml
```

## Troubleshooting

### Common Issues

1. **Permission denied accessing USB device**
   - On Linux: Add your user to the dialout group (`sudo usermod -a -G dialout $USER`)
   - Check udev rules for your debugger

2. **Target not responding**
   - Check physical connections
   - Verify correct interface type
   - Try power cycling the target device

3. **RTOS symbols not detected**
   - Ensure RTOS kernel symbols are not stripped from ELF file
   - Check that RTOS configuration matches your firmware

## Next Steps

- Read the [SWO Tracing Guide](swo_tracing.md) for advanced trace analysis
- Learn about [Memory Watchpoints](memory_watchpoints.md) for memory debugging
- Explore [Task Timeline Visualization](task_timeline.md) for RTOS debugging
- Check the [Troubleshooting Guide](troubleshooting.md) for complex issues