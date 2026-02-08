# Quick Start Guide for PAD-CoreBuilder

This guide will help you get started with PAD-CoreBuilder in just 5 minutes.

## Prerequisites

- Linux/macOS/Windows operating system
- Arduino IDE or PlatformIO installed
- At least 2GB free disk space
- C++ compiler toolchain

## Installation

1. Download the latest release from our [releases page](https://github.com/pad-service/pad-corebuilder/releases)
2. Extract the archive to your preferred location
3. Add the executable to your PATH or run directly from the extracted folder

For Linux/macOS:
```bash
tar -xf pad-corebuilder-x.x.x.tar.gz
cd pad-corebuilder
sudo ./install.sh
```

For Windows:
1. Run the installer executable as Administrator
2. Follow the installation wizard

## Basic Usage

### Generate a New Core

```bash
pad-corebuilder create --mcu stm32f407vg --name MySTM32Core --author "Your Name"
```

### Add Peripherals Using Drag-and-Drop Interface

Launch the GUI interface:
```bash
pad-corebuilder gui
```

In the interface:
1. Select your target MCU from the list
2. Drag peripherals from the library panel to your core canvas
3. Configure each peripheral's registers and settings
4. Preview the generated code
5. Export your core configuration

### Export Core to Arduino IDE

```bash
pad-corebuilder export --format arduino --config mycore.json --output ~/Arduino/hardware/mycompany
```

### Export Core to PlatformIO

```bash
pad-corebuilder export --format platformio --config mycore.json --output ~/.platformio/platforms/myplatform
```

## Configuration

Create a configuration file to store common parameters:

```json
{
  "core_name": "MyCustomCore",
  "mcu_family": "ARM Cortex-M",
  "mcu_type": "STM32F407VG",
  "clock_speed": 168000000,
  "flash_size": 1048576,
  "ram_size": 196608,
  "peripherals": [
    {
      "name": "USART1",
      "registers": ["CR1", "CR2", "CR3", "BRR", "SR", "DR"],
      "pins": ["PA9", "PA10"]
    },
    {
      "name": "GPIOA",
      "registers": ["MODER", "OTYPER", "OSPEEDR", "PUPDR", "IDR", "ODR", "BSRR", "LCKR", "AFRL", "AFRH"],
      "pins": ["PA0", "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7", "PA8", "PA9", "PA10", "PA11", "PA12", "PA13", "PA14", "PA15"]
    }
  ]
}
```

Then use it with:
```bash
pad-corebuilder build --config config.json
```

## Troubleshooting

### Common Issues

1. **Missing dependencies**
   - Install build-essential on Linux: `sudo apt install build-essential`
   - Install Xcode command line tools on macOS: `xcode-select --install`

2. **Permission denied accessing hardware folders**
   - Ensure proper ownership of Arduino hardware folders
   - Check PlatformIO permissions

3. **Export fails due to existing files**
   - Use the `--force` flag to overwrite existing files
   - Backup existing cores before exporting

## Next Steps

- Read the [Adding New MCUs Guide](adding_new_mcus.md) for advanced usage
- Learn about [Pin Mapping](pin_mapping.md) for custom board layouts
- Explore [Peripheral Templates](peripheral_templates.md) for rapid development
- Check out [Troubleshooting Guide](troubleshooting.md) for complex issues