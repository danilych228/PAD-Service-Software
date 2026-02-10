# PAD-BootManager

PAD-BootManager is a utility for managing bootloaders (DFU/UF2) on embedded devices. It provides protection against bricking, firmware rollback capabilities, and digital signature verification for firmware images.

## Features

- DFU (Device Firmware Update) and UF2 bootloader management
- Protection against "bricking" during updates
- Firmware rollback capability
- Digital signature verification for firmware images
- Recovery procedures for corrupted devices
- Secure boot configuration

## Quick Start

To get started with PAD-BootManager, see our [Quick Start Guide](./docs/quickstart.md).

## Documentation

Complete documentation is available in the [docs](./docs/) folder:
- [Quick Start](./docs/quickstart.md)
- [Recovery Procedures](./docs/recovery_procedures.md)
- [Secure Boot Configuration](./docs/secure_boot_config.md)
- [Troubleshooting](./docs/troubleshooting.md)

## Installation

See [Installation Guide](./docs/install.md) for detailed installation instructions.

## Usage

```
pad-bootmanager --device /dev/ttyUSB0 --firmware firmware.bin --mode dfu
```

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.