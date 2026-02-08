# PAD-Flasher Batch Mode Guide

## Overview
This guide covers the batch mode functionality of PAD-Flasher for mass device programming.

## Batch Mode Features

### Parallel Programming
PAD-Flasher supports programming up to 8 devices simultaneously:
- Each device connected to separate interface (UART/JTAG/SWD)
- Independent configuration per device
- Shared firmware image
- Real-time status monitoring

### Configuration Files
Create batch configuration files to define multiple devices:

```ini
[batch_config]
num_devices = 4
parallel_mode = true
timeout = 60

[device_1]
interface = uart
port = /dev/ttyUSB0
baudrate = 115200
firmware = firmware_v1.hex

[device_2]
interface = uart
port = /dev/ttyUSB1
baudrate = 115200
firmware = firmware_v1.hex

[device_3]
interface = swd
port = /dev/swd0
firmware = firmware_v1.hex

[device_4]
interface = jtag
port = /dev/jtag0
firmware = firmware_v1.hex
```

## Running Batch Operations

### Basic Batch Command
```bash
./pad-flasher --batch batch_config.ini --parallel
```

### Advanced Batch Options
```bash
# Run with validation
./pad-flasher --batch batch_config.ini --validate --parallel

# Run with recovery mode enabled
./pad-flasher --batch batch_config.ini --recovery --parallel

# Run with custom logging
./pad-flasher --batch batch_config.ini --log-file batch_results.log --parallel
```

## Status Monitoring

### Console Output
During batch operations, PAD-Flasher provides real-time status:
```
[DEVICE 1] CONNECTED -> INITIALIZING -> FLASHING (45%) -> VERIFIED -> COMPLETE
[DEVICE 2] CONNECTED -> INITIALIZING -> ERROR: TIMEOUT
[DEVICE 3] CONNECTED -> INITIALIZING -> FLASHING (20%) -> ...
[DEVICE 4] WAITING FOR CONNECTION...
```

### Progress Indicators
- Green: Operation completed successfully
- Yellow: In progress
- Red: Error occurred
- Blue: Waiting/idle

### Log File Format
Batch operations generate detailed logs:
```
[2023-06-15 10:30:15] BATCH STARTED - 4 devices
[2023-06-15 10:30:16] DEV1: Connected via UART (/dev/ttyUSB0)
[2023-06-15 10:30:17] DEV1: Firmware loaded (firmware_v1.hex - 128KB)
[2023-06-15 10:30:18] DEV1: Flashing started
[2023-06-15 10:30:45] DEV1: Flashing complete (27s)
[2023-06-15 10:30:46] DEV1: Verification started
[2023-06-15 10:30:48] DEV1: Verification successful
[2023-06-15 10:30:48] DEV1: COMPLETED SUCCESSFULLY
```

## Checksum Validation

### Automatic Validation
In batch mode, checksum validation occurs after each flash operation:
1. Calculate expected checksum from firmware file
2. Read back flashed memory
3. Calculate actual checksum
4. Compare and report result

### Validation Methods
- CRC32 (default)
- SHA256 (for security-sensitive applications)
- MD5 (legacy support)

### Error Handling
If validation fails:
1. Mark device as FAILED in results
2. Attempt recovery procedure
3. Optionally retry flashing (configurable)
4. Continue with other devices

## Recovery Procedures

### Automatic Recovery
When a device fails to respond:
1. Issue hardware reset
2. Try alternative connection methods
3. Enter bootloader mode
4. Reinitialize communication

### Recovery Configuration
Add to batch config:
```ini
[recovery]
enabled = true
max_attempts = 3
reset_delay = 2
bootloader_delay = 5
```

## Reporting

### Summary Report
After batch completion, PAD-Flasher generates a summary:
```
BATCH OPERATION SUMMARY
=======================
Total devices: 4
Successfully programmed: 3
Failed: 1
Success rate: 75%
Total time: 5 minutes 23 seconds
Average time per device: 1 minute 20 seconds

FAILED DEVICES:
- Device 2: Timeout during flashing
```

### Detailed Reports
For each device, a detailed report includes:
- Connection parameters
- Firmware information
- Timing breakdown
- Error details (if any)
- Validation results

## Troubleshooting

### Common Issues
1. **Device Not Detected**
   - Check physical connections
   - Verify interface selection
   - Test with single device mode first

2. **Timing Out During Flash**
   - Reduce baudrate for UART
   - Check power supply stability
   - Verify firmware size fits device memory

3. **Validation Errors**
   - Check for power fluctuations during flash
   - Verify correct firmware for device type
   - Retry with slower interface speeds

### Performance Tips
- Use faster interfaces (SWD > JTAG > UART) when possible
- Group similar devices together in config
- Pre-validate firmware files before batch operation
- Monitor system resources during parallel operations