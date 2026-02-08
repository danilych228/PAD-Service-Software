# Troubleshooting Guide for PAD-Scope

This guide provides solutions for common issues encountered when using PAD-Scope.

## Common Issues

### Device Not Detected
**Symptoms**: PAD-Scope reports "Device not found" or "Connection failed"

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
   - Check physical connections
   - Verify voltage levels match (3.3V vs 5V)
   - Test with simple serial terminal first

### No Signal Capture
**Symptoms**: Flat line or no data on display

**Solutions**:
1. **Check channel selection**
   - Verify correct channels are selected
   - Ensure probe connections are secure
   - Check that input impedance is appropriate for your signal

2. **Sample rate issues**
   - Increase sample rate for high-frequency signals
   - Decrease sample rate for better resolution of slow signals
   - Verify the sample rate is at least 2x the highest frequency component

3. **Signal level problems**
   - Verify signal voltage is within acceptable range
   - Check for proper ground reference
   - Ensure signal amplitude is sufficient for detection

### Poor Signal Quality
**Symptoms**: Noisy or unstable waveform display

**Solutions**:
1. **Grounding issues**
   - Ensure common ground between PAD-Scope and the circuit under test
   - Use star grounding for complex systems
   - Keep ground leads as short as possible

2. **Noise reduction**
   - Apply hardware filtering near the signal source
   - Use twisted pairs for differential signals
   - Shield sensitive signals from interference

3. **Trigger adjustments**
   - Increase trigger hysteresis to reduce noise-induced triggers
   - Use a cleaner signal for triggering if available
   - Adjust trigger level to center of signal swing

## Protocol Decoding Issues

### UART Decoding Problems
**Symptoms**: Garbled or incorrect UART data

**Solutions**:
1. **Baud rate mismatch**
   - Verify correct baud rate is specified
   - Use auto-baud detection if available
   - Check for fractional baud rate requirements

2. **Signal integrity**
   - Verify clean signal edges
   - Check for reflections on long traces
   - Ensure proper termination for high-speed signals

3. **Configuration errors**
   - Verify data bits, stop bits, and parity settings
   - Check for inverted logic requirements
   - Confirm RX/TX channel assignment

### I2C Decoding Problems
**Symptoms**: Missing transactions or incorrect data

**Solutions**:
1. **Clock stretching**
   - Some devices stretch the clock, causing timing violations
   - Increase timing tolerance in settings
   - Check for devices with unusual timing requirements

2. **Pull-up resistor values**
   - Verify appropriate pull-up resistors for bus speed
   - Too weak: slow rise times, errors
   - Too strong: overshoot, increased power consumption

3. **Bus contention**
   - Check for multiple masters on the bus
   - Verify slave devices are properly addressed
   - Look for stuck bus lines

### SPI Decoding Problems
**Symptoms**: Misaligned frames or incorrect data

**Solutions**:
1. **Mode configuration**
   - Verify correct SPI mode (CPOL/CPHA settings)
   - Check that mode matches the master and slave devices
   - Consider that some devices use non-standard modes

2. **Signal timing**
   - Verify adequate setup and hold times
   - Check for signal integrity issues at high speeds
   - Confirm clock rate is within device specifications

3. **Chip select issues**
   - Verify CS is properly asserted for each transaction
   - Check for spurious CS transitions
   - Confirm CS polarity is correct

## Hardware-Specific Issues

### Limited Channel Count
- Some boards have fewer logical analyzer channels than desired
- Consider multiplexing inputs with analog switches
- Use multiple PAD-Scope devices for more channels

### Bandwidth Limitations
- Internal ADC or sampling limitations may restrict bandwidth
- Verify your board's specifications match your signal requirements
- Consider external sampling hardware for high-frequency signals

### Buffer Overflow
- High sample rates can quickly fill buffers
- Reduce sample rate if high-frequency components aren't needed
- Use streaming mode if available
- Increase trigger holdoff to reduce capture frequency

## Software Issues

### High CPU Usage
**Symptoms**: Slow response or dropped samples

**Solutions**:
1. **Reduce display updates**
   - Lower refresh rate in settings
   - Reduce number of displayed channels
   - Use faster rendering options

2. **Optimize capture settings**
   - Reduce sample rate where possible
   - Use smaller capture buffers
   - Disable unnecessary features (FFT, math channels, etc.)

3. **System resources**
   - Close other applications consuming CPU/memory
   - Ensure adequate RAM for large captures
   - Use faster storage for temporary files

### Memory Exhaustion
- Export large captures in segments rather than all at once
- Use binary formats for more efficient memory usage
- Close and reopen PAD-Scope if working with many large captures

## Export Problems

### Export Fails
**Symptoms**: Export stops unexpectedly or produces corrupted files

**Solutions**:
1. **Disk space**
   - Verify sufficient disk space for export
   - Check for disk quotas limiting file sizes
   - Use different drive if current one is full

2. **File permissions**
   - Ensure write permissions to destination directory
   - Check for read-only file systems
   - Verify destination directory exists

3. **Large file handling**
   - Some filesystems have file size limits (FAT32: 4GB)
   - Use filesystems supporting large files (NTFS, ext4, etc.)
   - Split exports into smaller segments if needed

## Calibration and Accuracy

### Voltage Measurement Errors
**Symptoms**: Measured voltages differ from expected values

**Solutions**:
1. **Reference voltage**
   - Calibrate against known voltage reference
   - Check for temperature effects on reference
   - Verify stable power supply

2. **Input divider accuracy**
   - Check tolerance of input resistors
   - Verify PCB trace resistance isn't affecting measurement
   - Consider loading effects of high-impedance signals

### Timing Measurement Errors
**Symptoms**: Incorrect frequency or period measurements

**Solutions**:
1. **Clock accuracy**
   - Verify system clock accuracy
   - Use external precision clock if available
   - Check for temperature effects on oscillator

2. **Sample rate precision**
   - Ensure exact sample rate matches specification
   - Consider fractional sample rate errors
   - Use hardware with better timing accuracy for precision work

## Diagnostic Commands

### Verbose Logging
```bash
pad-scope --device /dev/ttyUSB0 --channels 0,1 --verbose --log-level debug
```

### Connection Test Only
```bash
pad-scope --device /dev/ttyUSB0 --test-connection
```

### Self-Calibration
```bash
pad-scope --calibrate --reference-voltage 3.3
```

### Performance Test
```bash
pad-scope --benchmark --channels 4
```

## Log Analysis

PAD-Scope creates detailed logs that can help diagnose issues:

- Timestamps help identify timing-related problems
- Error codes indicate specific failure types
- Performance metrics show resource usage
- Buffer status indicates overflow conditions

## Hardware Recommendations

### Probing Techniques
- Use appropriate probe loading for high-impedance circuits
- Keep ground leads short to minimize loop area
- Use differential probes for floating measurements
- Shield probes in electrically noisy environments

### Signal Integrity
- Match impedances for high-frequency signals
- Use appropriate termination for transmission lines
- Minimize stub lengths to reduce reflections
- Consider controlled impedance PCB routing

## When to Contact Support

Contact support if you encounter:
- Consistent failures with known-good hardware
- Unexpected crashes or segmentation faults
- Issues with specific device models not covered here
- Feature requests or suggestions for improvements

Include the following information:
- PAD-Scope version (`pad-scope --version`)
- Operating system and version
- Board model and specifications
- Complete command used
- Full log output with verbose enabled
- Hardware setup description
- Screenshots showing the issue if applicable