# Recovery Procedures

This document outlines the recovery procedures for using PAD-BootManager to restore bricked devices.

## Understanding Device Bricking

A device becomes "bricked" when its firmware becomes corrupted or incompatible, preventing normal operation. PAD-BootManager provides several methods to recover these devices.

## Manual Recovery Process

### Step 1: Identify the Problem

First, determine if the device is truly bricked or just unresponsive:

```bash
# Test if the device responds normally
ping_device_response()
{
    # Attempt to communicate with the device
    # Look for expected response patterns
}
```

### Step 2: Enter Bootloader Mode

To initiate recovery, you need to force the device into bootloader mode:

#### Method A: Hardware Reset
1. Disconnect the device from power
2. Hold down the BOOT button (or equivalent)
3. Reconnect power while holding the button
4. Release the button after 2 seconds

#### Method B: Software Reset
1. Connect the device normally
2. Send a specific reset command:
   ```bash
   pad-bootmanager -f firmware.bin -r --device /dev/ttyUSB0
   ```

### Step 3: Verify Bootloader Access

Check if the device is accessible in bootloader mode:

```bash
# List devices in bootloader mode
pad-bootmanager --list-devices

# Expected output:
# Found 1 device in bootloader mode:
#   1. /dev/ttyACM0 - DFU mode - STM32F407VG
```

### Step 4: Perform Recovery Operation

Once the device is in bootloader mode, perform the recovery:

```bash
# Basic recovery
pad-bootmanager -f known_good_firmware.bin -r

# With extended timeout
pad-bootmanager -f known_good_firmware.bin -r -t 120

# With verbose output for diagnostics
pad-bootmanager -f known_good_firmware.bin -r -v
```

## Automated Recovery Script

For systematic recovery of multiple devices, use this script template:

```bash
#!/bin/bash
# automated_recovery.sh

DEVICE_LIST=("ttyACM0" "ttyACM1" "ttyACM2")
FIRMWARE_PATH="known_good_firmware.bin"

for device in "${DEVICE_LIST[@]}"; do
    echo "Attempting recovery on /dev/$device..."
    
    # Attempt recovery
    if pad-bootmanager -f "$FIRMWARE_PATH" -r --device "/dev/$device" -t 60; then
        echo "Recovery successful on /dev/$device"
    else
        echo "Recovery failed on /dev/$device"
        # Log failure for manual inspection
        echo "$(date): Recovery failed on $device" >> recovery_failures.log
    fi
    
    # Wait before proceeding to next device
    sleep 5
done
```

## Troubleshooting Recovery Issues

### Device Won't Enter Bootloader Mode

1. **Check physical connections**: Ensure USB cables are functioning properly
2. **Try different USB ports**: Some ports may not provide enough power
3. **Verify button sequence**: Double-check the hardware reset procedure for your specific device
4. **Use external programmer**: If built-in bootloader is also corrupted, use JTAG/SWD

### Recovery Times Out

1. **Increase timeout**: Use `-t` option with higher values (e.g., `-t 120`)
2. **Check for partial corruption**: The bootloader might be partially functional
3. **Verify firmware file**: Ensure the recovery firmware is valid and not corrupted
4. **Try different recovery mode**: Switch between DFU and UF2 modes

### Signature Verification Failure

During recovery, if signature verification fails:

1. **Disable signature check temporarily**:
   ```bash
   pad-bootmanager -f firmware.bin -r --secure-boot=false
   ```
2. **Update the signature after recovery**
3. **Verify the recovery firmware is properly signed**

## Prevention Strategies

### Backup Current Firmware

Before updating, always backup the current firmware:

```bash
# Create backup of current firmware
backup_current_firmware()
{
    local device=$1
    local backup_file="backup_$(date +%Y%m%d_%H%M%S).bin"
    
    echo "Creating backup: $backup_file"
    # Implementation would depend on specific device capabilities
}
```

### Staged Rollouts

For fleet deployments:

1. Update 5% of devices first
2. Monitor for issues over 24 hours
3. Proceed with 25% if no issues
4. Complete remaining devices if still no issues

### Validation Checks

After recovery, perform validation:

```bash
# Post-recovery validation
post_recovery_validation()
{
    local device=$1
    
    # Test basic functionality
    test_communication "$device" || return 1
    verify_firmware_integrity "$device" || return 1
    run_basic_functionality_test "$device" || return 1
    
    echo "Device $device passed all validation checks"
    return 0
}
```

## Emergency Recovery Procedures

In extreme cases where standard recovery fails:

1. **Physical programmer access**: Use JTAG/SWD programmer to directly flash bootloader
2. **Boot ROM mode**: Force entry to chip's built-in boot ROM if available
3. **Component replacement**: Last resort - replace the main controller

## Support Information

If recovery procedures fail, contact support with:

1. Device model and version
2. Firmware version before bricking
3. Exact steps taken before device became unresponsive
4. Terminal output from recovery attempts
5. Any modifications made to device configuration

Contact: support@pad-service.ru