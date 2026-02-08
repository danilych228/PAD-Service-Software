# Troubleshooting Guide for PAD-Flasher

This guide provides solutions for common issues encountered when using PAD-Flasher.

## Common Issues

### Device Not Detected
**Symptoms**: PAD-Flasher reports "Device not found" or "Connection failed"

**Possible Causes and Solutions**:
1. **Wrong port specified**
   - Check available ports: `ls /dev/ttyUSB*` or `ls /dev/ttyACM*`
   - On Windows: Check Device Manager for COM ports
   - Ensure user has permissions to access the port (add to dialout group on Linux)

2. **Driver issues**
   - Install appropriate USB-to-Serial drivers (FTDI, CH340, CP2102, etc.)
   - Check kernel logs: `dmesg | grep tty`
   - Verify device enumeration: `lsusb`

3. **Hardware connection**
   - Check physical connections (TX/RX cross-over if needed)
   - Verify voltage levels match (3.3V vs 5V)
   - Test with simple serial terminal first

### Protocol Errors
**Symptoms**: "Protocol sync failed", "Invalid response", "Unknown device"

**Solutions**:
1. **Baud rate mismatch**
   - Try different baud rates (9600, 115200, 230400, 460800, 921600)
   - Some devices auto-baud, others require specific rate

2. **Bootloader not active**
   - Reset device manually while starting flasher
   - Hold reset button during connection attempt
   - Check if device needs special sequence to enter bootloader mode

3. **Incorrect protocol selection**
   - Verify target device supports selected protocol (UART/JTAG/SWD)
   - Check documentation for proper pinout

### Checksum Validation Failure
**Symptoms**: "Checksum mismatch", "Verification failed"

**Solutions**:
1. **Timing issues**
   - Increase timeout values
   - Add delays between operations
   - Slower baud rate might help

2. **Corrupted data transmission**
   - Check cable quality
   - Ensure stable power supply
   - Try flashing smaller chunks

3. **Memory differences**
   - Verify flash memory layout matches target
   - Check for protected sectors
   - Some devices have different memory maps in bootloader vs app mode

## JTAG/SWD Specific Issues

### Chain Detection Problems
- Ensure proper pull-up/pull-down resistors on TCK/TMS
- Check voltage levels on JTAG pins
- Verify TAP state machine initialization sequence

### Slow Clock Speeds
- Start with lower frequencies (1-10kHz) for initial connection
- Gradually increase speed after successful connection
- Some devices require very low speeds in bootloader mode

## Recovery Mode Issues

### Bricked Device Won't Respond
1. **Try different protocols** (UART/SWD/JTAG)
2. **Power cycle the device** completely
3. **Use alternative recovery methods** (DFU mode, ISP pins)
4. **Check for fused devices** (locked bootloaders)

### Recovery Stalls
- Ensure proper power delivery during recovery
- Some recovery modes require specific timing
- Check if external reset is needed

## Batch Mode Problems

### Intermittent Failures in Parallel Flashes
- Reduce parallel count temporarily to identify problematic devices
- Check USB hub limitations (powered hubs recommended)
- Separate power supplies for devices (not USB bus powered)

### Resource Exhaustion
- Monitor system resources during large batches
- Adjust batch size based on host capabilities
- Close unnecessary applications during batch operations

## Diagnostic Commands

### Verbose Logging
```bash
pad-flasher --device /dev/ttyUSB0 --firmware firmware.bin --verbose --log-level debug
```

### Connection Test Only
```bash
pad-flasher --device /dev/ttyUSB0 --test-connection --protocol uart
```

### Protocol Detection
```bash
pad-flasher --device /dev/ttyUSB0 --detect-protocol
```

### Manual Control
```bash
pad-flasher --device /dev/ttyUSB0 --manual-mode
```

## Log Analysis

PAD-Flasher creates detailed logs that can help diagnose issues:

- Timestamps help identify timing-related problems
- Error codes indicate specific failure types
- Retry attempts show consistency of connections
- Buffer dumps can reveal data corruption

## Hardware Recommendations

### Reliable Connections
- Use shielded cables for longer distances
- Powered USB hubs for multiple devices
- Separate power supplies for target devices
- Proper grounding between systems

### Cable Quality
- Avoid very cheap USB cables (poor internal conductors)
- Check for intermittent connections
- Use appropriate voltage levels for signal integrity

## When to Contact Support

Contact support if you encounter:
- Consistent failures with known-good hardware
- Unexpected crashes or segmentation faults
- Issues with specific device models not covered here
- Feature requests or suggestions for improvements

Include the following information:
- PAD-Flasher version (`pad-flasher --version`)
- Operating system and version
- Target device model and specifications
- Complete command used
- Full log output with verbose enabled
- Hardware setup description