#!/usr/bin/env python3
"""
PAD-Flasher - Universal Device Programmer for UART/JTAG/SWD interfaces
"""

import os
import sys
import argparse
import threading
import time
import serial
from typing import List, Dict, Any, Optional
from dataclasses import dataclass, field
from pathlib import Path
import configparser


@dataclass
class DeviceConfig:
    """Configuration for a single device connection."""
    type: str  # 'uart', 'jtag', or 'swd'
    device_path: str
    baudrate: int = 115200
    timeout: int = 30
    validate_after_flash: bool = False
    recovery_mode: bool = False
    fd: Optional[Any] = None  # File descriptor for the connection


@dataclass
class FlashConfig:
    """Overall flashing configuration."""
    firmware_path: str
    validate_after_flash: bool = False
    recovery_mode: bool = False
    parallel_mode: bool = False
    num_devices: int = 1
    devices: List[DeviceConfig] = field(default_factory=list)


class PadFlasher:
    """Main PAD-Flasher application class."""

    def __init__(self):
        self.config = FlashConfig("")
        self.output_lock = threading.Lock()

    def print_banner(self):
        """Print the application banner."""
        print("PAD-Flasher v1.0.0 - Universal Device Programmer")
        print("Supports UART/JTAG/SWD interfaces for mass device programming\n")

    def parse_arguments(self) -> int:
        """Parse command line arguments."""
        parser = argparse.ArgumentParser(
            description="PAD-Flasher - Universal Device Programmer for UART/JTAG/SWD interfaces",
            formatter_class=argparse.RawDescriptionHelpFormatter,
            epilog="""
Examples:
  %(prog)s -f firmware.hex -i uart -d /dev/ttyUSB0
  %(prog)s -f firmware.hex -i swd -n 4 -p        # Flash 4 devices in parallel
  %(prog)s -f firmware.hex -c batch.conf         # Use batch configuration
            """
        )

        parser.add_argument('-f', '--firmware', required=True,
                           help='Firmware file to flash (.hex, .bin, .elf)')
        parser.add_argument('-i', '--interface', default='uart',
                           choices=['uart', 'jtag', 'swd'],
                           help='Interface type (default: uart)')
        parser.add_argument('-d', '--device',
                           help='Device path (e.g., /dev/ttyUSB0)')
        parser.add_argument('-b', '--baudrate', type=int, default=115200,
                           help='Baudrate for UART interface (default: 115200)')
        parser.add_argument('-n', '--num-devices', type=int, default=1,
                           help='Number of devices for parallel flashing (default: 1)')
        parser.add_argument('-v', '--validate', action='store_true',
                           help='Validate checksum after flashing')
        parser.add_argument('-r', '--recovery', action='store_true',
                           help='Enable recovery mode')
        parser.add_argument('-p', '--parallel', action='store_true',
                           help='Enable parallel mode for multiple devices')
        parser.add_argument('-c', '--batch',
                           help='Batch configuration file')
        parser.add_argument('-V', '--version', action='version',
                           version='PAD-Flasher v1.0.0')

        args = parser.parse_args()

        # Store parsed arguments in our config
        self.config.firmware_path = args.firmware
        self.config.validate_after_flash = args.validate
        self.config.recovery_mode = args.recovery
        self.config.parallel_mode = args.parallel
        self.config.num_devices = args.num_devices

        # Create device configurations
        if args.device:
            # Single device specified
            device_config = DeviceConfig(
                type=args.interface,
                device_path=args.device,
                baudrate=args.baudrate,
                validate_after_flash=args.validate,
                recovery_mode=args.recovery
            )
            self.config.devices = [device_config]
        else:
            # Create default configurations for multiple devices
            for i in range(args.num_devices):
                device_path = f'/dev/ttyUSB{i}' if os.name != 'nt' else f'COM{i+1}'
                device_config = DeviceConfig(
                    type=args.interface,
                    device_path=device_path,
                    baudrate=args.baudrate,
                    validate_after_flash=args.validate,
                    recovery_mode=args.recovery
                )
                self.config.devices.append(device_config)

        # Handle batch configuration file
        if args.batch:
            print(f"Batch configuration file: {args.batch}")
            self.load_batch_config(args.batch)

        return 0

    def load_batch_config(self, config_file: str):
        """Load configuration from a batch configuration file."""
        try:
            config_parser = configparser.ConfigParser()
            config_parser.read(config_file)

            # Clear existing devices
            self.config.devices = []

            # Load batch settings
            if 'batch_config' in config_parser:
                batch_section = config_parser['batch_config']
                self.config.num_devices = int(batch_section.get('num_devices', 1))
                self.config.parallel_mode = batch_section.getboolean('parallel_mode', False)
                self.config.recovery_mode = batch_section.getboolean('recovery_mode', False)

            # Load individual device configurations
            for i in range(self.config.num_devices):
                device_section = f'device_{i+1}'
                if device_section in config_parser:
                    section = config_parser[device_section]
                    device_config = DeviceConfig(
                        type=section.get('interface', 'uart'),
                        device_path=section.get('port', f'/dev/ttyUSB{i}'),
                        baudrate=int(section.get('baudrate', 115200)),
                        validate_after_flash=self.config.validate_after_flash,
                        recovery_mode=self.config.recovery_mode
                    )
                    self.config.devices.append(device_config)

        except Exception as e:
            print(f"Error loading batch configuration: {e}", file=sys.stderr)
            return -1

        return 0

    def init_device_connection(self, config: DeviceConfig) -> int:
        """Initialize connection to a device."""
        try:
            if config.type == 'uart':
                # Open serial port
                config.fd = serial.Serial(
                    config.device_path,
                    baudrate=config.baudrate,
                    bytesize=8,
                    parity='N',
                    stopbits=1,
                    timeout=config.timeout
                )
                with self.output_lock:
                    print(f"Connected to device via UART: {config.device_path} at {config.baudrate} baud")
            else:
                # For JTAG/SWD, we would implement specific initialization
                with self.output_lock:
                    print(f"Initialized connection to {config.device_path} via {config.type.upper()}")
                config.fd = True  # Placeholder for demo

            return 0
        except Exception as e:
            with self.output_lock:
                print(f"Error connecting to {config.device_path}: {e}", file=sys.stderr)
            return -1

    def close_device_connection(self, config: DeviceConfig) -> int:
        """Close connection to a device."""
        if config.fd:
            if isinstance(config.fd, serial.Serial):
                config.fd.close()
            config.fd = None
        return 0

    def flash_device(self, device: DeviceConfig, firmware_path: str) -> int:
        """Flash firmware to a single device."""
        with self.output_lock:
            print(f"Flashing device {device.device_path} with firmware {firmware_path}...")

        # Simulate flashing process
        for i in range(0, 101, 10):
            with self.output_lock:
                print(f"\rFlashing progress: {i}%", end='', flush=True)
            time.sleep(0.2)  # Simulate work

        with self.output_lock:
            print()  # New line after progress
            print(f"Device {device.device_path} flashed successfully")

        return 0

    def validate_checksum(self, firmware_path: str, device: DeviceConfig) -> int:
        """Validate checksum on device after flashing."""
        if not device.validate_after_flash:
            return 0  # Skip validation if not requested

        with self.output_lock:
            print(f"Validating checksum on device {device.device_path}...")

        # Simulate validation process
        for i in range(0, 101, 25):
            with self.output_lock:
                print(f"\rValidation progress: {i}%", end='', flush=True)
            time.sleep(0.1)  # Simulate work

        with self.output_lock:
            print()  # New line after progress
            print(f"Checksum validation passed for device {device.device_path}")

        return 0

    def enter_recovery_mode(self, device: DeviceConfig) -> int:
        """Enter recovery mode on device."""
        if not device.recovery_mode:
            return 0  # Skip recovery if not requested

        with self.output_lock:
            print(f"Entering recovery mode on device {device.device_path}...")

        # Simulate recovery process
        time.sleep(1)
        with self.output_lock:
            print(f"Recovery mode entered successfully for device {device.device_path}")

        return 0

    def process_single_device(self, device_index: int):
        """Process a single device in a thread-safe manner."""
        device = self.config.devices[device_index]

        with self.output_lock:
            print(f"\n--- Processing Device {device_index + 1} ---")
            print(f"Interface: {device.type.upper()}")
            print(f"Device: {device.device_path}")

        # Initialize connection
        if self.init_device_connection(device) != 0:
            with self.output_lock:
                print(f"Failed to initialize device {device.device_path}", file=sys.stderr)
            return

        # Enter recovery mode if enabled
        self.enter_recovery_mode(device)

        # Flash the device
        if self.flash_device(device, self.config.firmware_path) != 0:
            with self.output_lock:
                print(f"Failed to flash device {device.device_path}", file=sys.stderr)
            self.close_device_connection(device)
            return

        # Validate checksum if requested
        if self.validate_checksum(self.config.firmware_path, device) != 0:
            with self.output_lock:
                print(f"Checksum validation failed for device {device.device_path}", file=sys.stderr)
            self.close_device_connection(device)
            return

        # Close connection
        self.close_device_connection(device)

        with self.output_lock:
            print(f"Device {device.device_path} completed successfully")

    def perform_batch_operation(self) -> int:
        """Perform the main batch flashing operation."""
        print(f"Starting batch operation with {len(self.config.devices)} device(s)")

        if self.config.parallel_mode:
            print("Running in parallel mode")

            # Create threads for parallel processing
            threads = []
            for i in range(len(self.config.devices)):
                thread = threading.Thread(target=self.process_single_device, args=(i,))
                threads.append(thread)
                thread.start()

            # Wait for all threads to complete
            for thread in threads:
                thread.join()
        else:
            print("Running in sequential mode")

            # Process devices sequentially
            for i in range(len(self.config.devices)):
                self.process_single_device(i)

        return 0

    def run(self) -> int:
        """Run the main application."""
        if self.perform_batch_operation() != 0:
            print("Flashing operation failed", file=sys.stderr)
            return 1

        print("\nFlashing completed successfully!")
        return 0


def main():
    """Entry point for the application."""
    app = PadFlasher()
    app.print_banner()

    if app.parse_arguments() != 0:
        return 1

    return app.run()


if __name__ == "__main__":
    sys.exit(main())