# Batch Mode Guide for PAD-Flasher

This guide explains how to use PAD-Flasher's batch mode for mass production scenarios.

## Overview

Batch mode enables simultaneous flashing of multiple devices with automatic validation and logging. It's designed for manufacturing environments where hundreds or thousands of units need to be programmed efficiently.

## Batch Configuration File

Create a batch configuration file in JSON format:

```json
{
  "batch_id": "production_run_001",
  "firmware_file": "./firmwares/device_v1.2.3.bin",
  "protocol": "uart",
  "parallel_devices": 8,
  "validation_enabled": true,
  "logging": {
    "log_file": "./logs/batch_run.log",
    "log_level": "info",
    "results_csv": "./results/batch_results.csv"
  },
  "devices": [
    {
      "port": "/dev/ttyUSB0",
      "baudrate": 115200,
      "timeout": 10000,
      "pre_flight_check": ["voltage_check", "connection_test"]
    },
    {
      "port": "/dev/ttyUSB1",
      "baudrate": 115200,
      "timeout": 10000,
      "pre_flight_check": ["voltage_check", "connection_test"]
    }
    // ... additional devices up to parallel_devices count
  ],
  "recovery_mode": {
    "enabled": true,
    "max_retries": 3,
    "fallback_protocol": "swd"
  },
  "checksum_validation": {
    "algorithm": "crc32",
    "block_size": 1024
  }
}
```

## Running Batch Mode

To run in batch mode:

```bash
pad-flasher --batch-config ./configs/batch_config.json --batch-mode
```

Or using command line parameters:

```bash
pad-flasher --devices /dev/ttyUSB0,/dev/ttyUSB1,/dev/ttyUSB2,/dev/ttyUSB3 \
            --firmware ./firmwares/device.bin \
            --protocol uart \
            --batch-mode \
            --parallel-jobs 4 \
            --log-file ./batch_results.log
```

## Pre-flight Checks

PAD-Flasher performs several checks before flashing:

- Connection test: Verifies communication with device
- Voltage check: Ensures proper power levels
- Device identification: Validates target device type
- Bootloader detection: Confirms bootloader availability

## Results and Reporting

After batch execution, PAD-Flasher generates:

- Detailed log file with timestamps and error messages
- CSV report with device-specific results
- Summary statistics (success rate, average time, etc.)
- Failed devices list for rework

Example CSV output:
```
Device,Port,StartTime,EndTime,Status,ErrorCode,Notes
1,/dev/ttyUSB0,2023-06-15T10:00:00,2023-06-15T10:00:45,Success,,Flashed successfully
2,/dev/ttyUSB1,2023-06-15T10:00:01,2023-06-15T10:00:46,Failure,CHECKSUM_ERR,Checksum mismatch
3,/dev/ttyUSB2,2023-06-15T10:00:02,2023-06-15T10:00:30,Success,,Flashed successfully
```

## Advanced Batch Features

### Conditional Flashing
Skip devices that already have the correct firmware version:
```bash
pad-flasher --batch-config config.json --conditional-flash --current-version-field 0x100
```

### Power Cycling
Automatically cycle power to devices before flashing:
```bash
pad-flasher --batch-config config.json --power-cycle-pin 18 --power-cycle-delay 1000
```

### Custom Validation
Run custom validation scripts after flashing:
```bash
pad-flasher --batch-config config.json --post-flash-script ./validate_device.sh
```

## Troubleshooting Batch Operations

### Slow Performance
- Reduce parallel device count if host system resources are limited
- Increase timeouts for slower devices
- Check USB bandwidth limitations

### Intermittent Failures
- Add extra delay between operations
- Implement retry logic in configuration
- Check for electrical interference between devices

### Resource Limits
- Monitor system resources during large batches
- Use external power supplies instead of USB bus power
- Consider staggering device activation to reduce peak current draw