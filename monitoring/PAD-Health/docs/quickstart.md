# PAD-Health Quick Start Guide

This guide will help you get started with PAD-Health for monitoring the health of your embedded systems in just a few minutes.

## Installation

First, make sure you have PAD-Health installed on your system:

```bash
# Clone the repository
git clone https://github.com/pad-service/pad-health.git
cd pad-health

# Build the application
mkdir build && cd build
cmake ..
make

# Install the application (optional)
sudo make install
```

## Basic Usage

### Simple Monitoring

To start monitoring your device's health:

```bash
pad-health -d /dev/ttyUSB0
```

### Using a Configuration File

Create a configuration file and use it for monitoring:

```bash
pad-health -d /dev/ttyUSB0 -c health_config.json
```

Example `health_config.json`:

```json
{
  "thresholds": {
    "temperature": {
      "warning": 60,
      "critical": 70
    },
    "voltage": {
      "min_warning": 3.0,
      "max_warning": 3.6,
      "min_critical": 2.8,
      "max_critical": 3.8
    },
    "clock_stability": {
      "warning": 0.01,
      "critical": 0.1
    }
  },
  "polling_interval": 5,
  "alerting": {
    "mqtt": {
      "enabled": false,
      "server": "localhost",
      "port": 1883,
      "topic": "health/monitoring"
    },
    "email": {
      "enabled": false,
      "smtp_server": "smtp.example.com",
      "recipient": "admin@example.com"
    }
  }
}
```

### Different Output Formats

PAD-Health supports multiple output formats:

```bash
# JSON output (useful for integration with other tools)
pad-health -d /dev/ttyUSB0 -f json

# CSV output (useful for spreadsheet analysis)
pad-health -d /dev/ttyUSB0 -f csv

# Default text format
pad-health -d /dev/ttyUSB0 -f text
```

### Running as a Daemon

Run PAD-Health continuously in the background:

```bash
pad-health -d /dev/ttyUSB0 -D --daemon
```

### Adjusting Polling Interval

Change how frequently the device is polled:

```bash
# Poll every 10 seconds instead of the default 5
pad-health -d /dev/ttyUSB0 -i 10
```

## Advanced Usage

### Enable MQTT Publishing

Send health metrics to an MQTT broker:

```bash
pad-health --enable-mqtt --mqtt-server mqtt.example.com
```

### Enable Email Alerts

Configure email notifications for critical events:

```bash
pad-health --enable-email --email admin@example.com
```

### Monitor Specific Parameters Only

Focus on specific health metrics:

```bash
# Monitor only temperature
pad-health --temperature-only

# Monitor only voltage
pad-health --voltage-only

# Monitor only clock stability
pad-health --clock-only
```

### Generate Statistics Report

Produce a comprehensive health statistics report:

```bash
pad-health --stats-report
```

## Configuration Options

### Threshold Configuration

The following thresholds can be configured:

- **Temperature**: Warning and critical levels in degrees Celsius
- **Voltage**: Minimum and maximum acceptable values in volts
- **Clock Stability**: Acceptable drift percentage

### Alerting Configuration

PAD-Health supports two alerting mechanisms:

1. **MQTT**: Publish alerts to an MQTT topic
2. **Email**: Send email notifications to configured recipients

## Troubleshooting

### Device Connection Issues

If PAD-Health cannot connect to your device:

1. Verify the device path with `ls /dev/tty*`
2. Check that the device is properly connected
3. Ensure you have permission to access the device (may require sudo)
4. Confirm the device is in the correct mode for health monitoring

### High CPU Usage

If PAD-Health is consuming too much CPU:

1. Increase the polling interval (`-i` option)
2. Reduce the output verbosity
3. Consider monitoring only essential parameters

### Missing Alerts

If alerts are not being sent:

1. Verify MQTT/email settings in the configuration file
2. Check network connectivity to MQTT server or SMTP server
3. Ensure alert thresholds are appropriately set

## Next Steps

Now that you've completed the quick start, explore more features in our [User Guide](./user_guide.md) or check out the [API Reference](./api_reference.md).