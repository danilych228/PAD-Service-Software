# PAD-Health

PAD-Health is a monitoring tool for temperature, voltage, and clock stability on embedded devices. It provides threshold configuration and alerting capabilities via MQTT and email.

## Features

- Temperature monitoring
- Voltage monitoring
- Clock stability tracking
- Threshold configuration
- Alerting via MQTT and email
- Crystal degradation graph
- Failure prediction based on statistics

## Quick Start

To get started with PAD-Health, see our [Quick Start Guide](./docs/quickstart.md).

## Documentation

Complete documentation is available in the [docs](./docs/) folder:
- [Quick Start](./docs/quickstart.md)
- [Threshold Configuration](./docs/threshold_config.md)
- [Alerting Setup](./docs/alerting_setup.md)
- [Troubleshooting](./docs/troubleshooting.md)

## Installation

See [Installation Guide](./docs/install.md) for detailed installation instructions.

## Usage

```
pad-health --device /dev/ttyUSB0 --config health_config.json
```

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.