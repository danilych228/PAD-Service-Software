# PAD-Flasher

PAD-Flasher is a utility for mass firmware flashing through UART/JTAG/SWD interfaces. It supports parallel flashing of 8+ devices with checksum validation and recovery modes.

## Features

- Parallel flashing of 8+ devices simultaneously
- Checksum validation
- Recovery mode for bricked devices
- Batch mode automation
- Protocol specifications support

## Quick Start

To get started with PAD-Flasher, see our [Quick Start Guide](./docs/quickstart.md).

## Documentation

Complete documentation is available in the [docs](./docs/) folder:
- [Quick Start](./docs/quickstart.md)
- [Protocol Specifications](./docs/protocol_specs.md)
- [Batch Mode Guide](./docs/batch_mode_guide.md)
- [Troubleshooting](./docs/troubleshooting.md)

## Installation

See [Installation Guide](./docs/install.md) for detailed installation instructions.

## Usage

```
pad-flasher --devices /dev/ttyUSB0,/dev/ttyUSB1 --firmware firmware.bin --protocol uart
```

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.