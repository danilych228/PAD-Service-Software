# PAD-Scope

PAD-Scope is a virtual oscilloscope that uses your board's built-in logical analyzer capabilities to visualize signals. It provides trigger modes and protocol decoding for I2C, SPI, and UART communications.

## Features

- Virtual oscilloscope functionality via logical analyzer on your board
- Trigger modes for signal capture
- Protocol decoding for I2C, SPI, and UART
- Mathematical channel operations
- Export to CSV and WAV formats
- FFT analysis capabilities

## Documentation

Complete documentation is available in the [docs](./docs/) folder:
- [Quick Start Guide](./docs/quickstart.md)
- [Trigger Modes Guide](./docs/trigger_modes.md)
- [Protocol Decoding Guide](./docs/protocol_decoding.md)
- [Export Formats Guide](./docs/export_formats.md)
- [Troubleshooting](./docs/troubleshooting.md)

## Installation

See [Installation Guide](./docs/install.md) for detailed installation instructions.

## Usage

```
pad-scope --device /dev/ttyUSB0 --channels 0,1 --sample-rate 1000000
```

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.