# Troubleshooting

This document provides solutions to common issues encountered when using PAD-Trace.

## Installation Issues

### Missing Dependencies
**Problem:** CMake fails to find required libraries during build
**Solution:** Install the missing dependencies:
```bash
# On Ubuntu/Debian
sudo apt install libusb-1.0-0-dev

# On macOS
brew install libusb
```

### Compilation Errors
**Problem:** Build fails with compilation errors
**Solution:** 
1. Ensure your compiler supports C++17
2. Check that all dependencies are properly installed
3. Update your build tools (CMake, compiler)

## Hardware Connection Issues

### Power Monitor Not Detected
**Problem:** PAD-Trace cannot detect the power monitoring hardware
**Solution:**
1. Check physical USB connection to the power monitor
2. Verify USB permissions (on Linux: add user to `plugdev` or `dialout` group)
3. Try different USB cable or port
4. Check if another application is using the device
5. Run with elevated privileges if necessary

### Inconsistent Measurements
**Problem:** Power measurements are inconsistent or erratic
**Solution:**
1. Check for proper grounding between devices
2. Verify power path connections
3. Allow time for measurement stabilization
4. Check for electromagnetic interference

## Software Issues

### Application Crashes
**Problem:** PAD-Trace crashes during operation
**Solution:**
1. Update system libraries
2. Run with reduced measurement channels initially
3. Check system memory availability
4. Review logs for specific error patterns

### High Resource Usage
**Problem:** Excessive CPU or memory usage during profiling
**Solution:**
1. Reduce sampling rate if high precision isn't required
2. Limit the duration of capture sessions
3. Disable real-time visualization during long captures
4. Close other resource-intensive applications

## Measurement Accuracy

### Inaccurate Power Readings
**Problem:** Measured power doesn't match expected values
**Solution:**
1. Calibrate the power measurement hardware
2. Verify proper shunt resistor values in configuration
3. Check for correct voltage/current scaling factors
4. Compare against a known accurate meter

### Noise in Measurements
**Problem:** Power readings show excessive noise
**Solution:**
1. Check for proper grounding of measurement setup
2. Add filtering capacitors if appropriate
3. Reduce sample rate to average out high-frequency noise
4. Verify clean power supply to the DUT

## Correlation Issues

### Poor Code-Event Correlation
**Problem:** Power events don't align well with code execution markers
**Solution:**
1. Verify proper instrumentation in target code
2. Check synchronization between target and PAD-Trace
3. Adjust timing offset if needed
4. Ensure consistent timestamps between systems

### Missing Events
**Problem:** Expected power events aren't being recorded
**Solution:**
1. Verify instrumentation is properly placed in code
2. Check that event reporting is enabled
3. Increase buffer sizes if events are being dropped
4. Verify communication channel between target and PAD-Trace

## Data Export Problems

### Export Fails
**Problem:** Export to file formats fails
**Solution:**
1. Check write permissions for the target directory
2. Verify available disk space
3. Ensure the file is not open in another application
4. Try a different file format

### Data Corruption in Export
**Problem:** Exported files contain corrupted data
**Solution:**
1. Verify that the export process completed successfully
2. Check for adequate buffer sizes during export
3. Try exporting smaller portions of the data
4. Re-export with different settings

## Performance Issues

### Slow Response Times
**Problem:** UI responsiveness decreases during long captures
**Solution:**
1. Reduce real-time visualization complexity
2. Use lower resolution for initial exploration
3. Process data in chunks rather than all at once
4. Close unnecessary applications to free up resources

### Dropped Samples
**Problem:** Power samples are being lost during capture
**Solution:**
1. Reduce sampling rate to match system capabilities
2. Increase buffer sizes in configuration
3. Close other applications consuming resources
4. Use faster storage for temporary data

## Support

For additional help, contact our support team at support@pad-service.ru with:
- Description of the problem
- Operating system and version
- PAD-Trace version
- Steps to reproduce the issue
- Any relevant error messages
- Hardware setup information