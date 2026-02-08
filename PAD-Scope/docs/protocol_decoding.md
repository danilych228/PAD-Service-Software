# Protocol Decoding Guide for PAD-Scope

This document details how to decode various communication protocols using PAD-Scope's built-in decoders.

## Supported Protocols

PAD-Scope includes decoders for commonly used communication protocols:

- UART/RS232
- I2C (Inter-Integrated Circuit)
- SPI (Serial Peripheral Interface)
- CAN (Controller Area Network)
- 1-Wire
- Manchester Encoding
- PWM (Pulse Width Modulation) decoding

## UART Protocol Decoding

UART is the most commonly decoded protocol. To decode UART signals:

### Basic UART Decoding
```bash
# Decode UART on channel 0 (typically RX line)
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol uart --uart-baud 9600

# Decode both RX and TX on separate channels
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol uart --uart-baud 115200
# Channel 0: RX, Channel 1: TX
```

### UART Configuration Options
```bash
--uart-baud 115200           # Baud rate (default: 9600)
--uart-data-bits 8           # Data bits (default: 8)
--uart-stop-bits 1           # Stop bits (default: 1)
--uart-parity none           # Parity: none, odd, even (default: none)
--uart-inverted false        # Inverted logic (default: false)
--uart-show-frames true      # Show frame boundaries (default: true)
```

### UART Troubleshooting
Common UART decoding issues:
- Incorrect baud rate - use the auto-baud feature to detect rate
- Signal inversion - try `--uart-inverted true`
- Noise - add hysteresis with `--trigger-hysteresis 0.1`

## I2C Protocol Decoding

I2C protocol requires two channels: SDA (data) and SCL (clock).

### Basic I2C Decoding
```bash
# Decode I2C on channels 0 (SDA) and 1 (SCL)
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol i2c --i2c-frequency 100000
```

### I2C Configuration Options
```bash
--i2c-frequency 100000       # Bus frequency in Hz (default: 100000)
--i2c-address-format 7       # Address format: 7 or 10 bit (default: 7)
--i2c-show-addresses true    # Show device addresses (default: true)
--i2c-show-data true         # Show data bytes (default: true)
--i2c-deglitch 50ns          # Deglitch time for noisy signals
```

### I2C Advanced Features
```bash
# Decode specific I2C devices
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol i2c --i2c-decode-device 0x50
# This will only decode traffic to/from device at address 0x50

# Show timing measurements
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol i2c --i2c-show-timing true
```

## SPI Protocol Decoding

SPI requires at minimum 3 channels (MOSI, MISO, SCK) and optionally CS.

### Basic SPI Decoding
```bash
# Decode SPI with 4 wires (MOSI, MISO, SCK, CS)
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --protocol spi --spi-mode 0
# Channel 0: MOSI, Channel 1: MISO, Channel 2: SCK, Channel 3: CS
```

### SPI Configuration Options
```bash
--spi-mode 0                 # SPI mode (0-3, default: 0)
--spi-frequency 1000000      # Clock frequency in Hz (default: 1000000)
--spi-bits 8                 # Bits per transfer (default: 8)
--spi-msb-first true         # Most significant bit first (default: true)
--spi-clock-phase 0          # Clock phase (0 or 1, derived from mode)
--spi-clock-polarity 0       # Clock polarity (0 or 1, derived from mode)
--spi-show-cs true           # Show chip select activity (default: true)
```

### SPI Mode Definitions
- Mode 0: CPOL=0, CPHA=0 (clock idle low, sample on leading edge)
- Mode 1: CPOL=0, CPHA=1 (clock idle low, sample on trailing edge)
- Mode 2: CPOL=1, CPHA=0 (clock idle high, sample on leading edge)
- Mode 3: CPOL=1, CPHA=1 (clock idle high, sample on trailing edge)

## CAN Protocol Decoding

CAN protocol decoding requires a single channel for the differential signal.

### Basic CAN Decoding
```bash
# Decode CAN on channel 0
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol can --can-bitrate 500000
```

### CAN Configuration Options
```bash
--can-bitrate 500000         # Bit rate in bps (default: 500000)
--can-sample-point 75        # Sample point percentage (default: 75)
--can-show-ids true          # Show message IDs (default: true)
--can-show-data true         # Show data bytes (default: true)
--can-filter-id 0x123        # Only show messages with specific ID
```

## 1-Wire Protocol Decoding

1-Wire protocol uses a single bidirectional data line.

### Basic 1-Wire Decoding
```bash
# Decode 1-Wire on channel 0
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol onewire
```

### 1-Wire Configuration Options
```bash
--onewire-suppress-reset true  # Suppress reset/presence packets (default: false)
--onewire-family-filter 0x28   # Filter by device family (e.g., DS18B20)
```

## Manchester Encoding Decoding

Manchester encoding is commonly used in RFID and wireless protocols.

### Basic Manchester Decoding
```bash
# Decode Manchester-encoded signal
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol manchester --manchester-bitrate 10000
```

### Manchester Configuration Options
```bash
--manchester-bitrate 10000     # Bit rate in bps (default: 10000)
--manchester-inverted false    # Inverted encoding (default: false)
--manchester-clock-recovery true # Auto clock recovery (default: true)
```

## PWM Decoding

PWM decoding measures pulse width and period for servo control or power applications.

### Basic PWM Decoding
```bash
# Decode PWM signal
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol pwm --pwm-measure-duty-cycle true
```

### PWM Configuration Options
```bash
--pwm-measure-duty-cycle true   # Measure duty cycle (default: true)
--pwm-measure-frequency true    # Measure frequency (default: true)
--pwm-threshold 1.65           # Threshold voltage for digitalization
```

## Protocol Decoder Settings

### General Protocol Options
```bash
--protocol <name>              # Specify protocol to decode
--show-decoded true            # Show decoded protocol data (default: true)
--decode-start-time 0s         # Time to start decoding (default: 0s)
--decode-end-time 10s          # Time to end decoding (default: end of capture)
--protocol-highlight true      # Highlight protocol events on waveform (default: true)
```

### Protocol Filtering
```bash
# Show only valid frames
--protocol-show-invalid false  # Hide invalid frames (default: true)

# Filter by specific addresses or IDs
--filter-address 0x50          # Only show traffic to specific address
--filter-device temp_sensor    # Filter by device nickname
```

## Advanced Protocol Analysis

### Protocol Statistics
```bash
# Generate protocol statistics
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol i2c --generate-stats

# Export protocol statistics to file
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol uart --export-stats uart_stats.txt
```

### Protocol Comparison
```bash
# Compare two protocol captures
pad-scope --compare-capture capture1.csv capture2.csv --protocol uart
```

## Custom Protocol Decoding

PAD-Scope allows for custom protocol definitions:

### DBC Files for CAN
For CAN buses, you can import DBC files to decode specific message formats:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol can --dbc-file vehicle.dbc
```

### Custom UART Definitions
Define custom UART packet structures:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol uart-custom --custom-definition my_protocol.json
```

## Exporting Protocol Data

Protocol data can be exported in various formats:

### Export Decoded Data
```bash
# Export UART data as text
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol uart --export-protocol-data uart_output.txt

# Export I2C data in CSV format
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol i2c --export-protocol-csv i2c_data.csv

# Export SPI data in binary format
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --protocol spi --export-protocol-bin spi_data.bin
```

## Troubleshooting Protocol Decoding

### Common Issues and Solutions

#### Wrong Baud Rate (UART)
- Use auto-baud detection: `--uart-autobaud true`
- Try different common baud rates: 9600, 115200, 230400, 460800, 921600

#### Noise-Induced Errors (Any Protocol)
- Increase trigger hysteresis: `--trigger-hysteresis 0.2`
- Use deglitching: `--deglitch 100ns`
- Lower sample rate to reduce noise

#### Misaligned Frames
- Adjust trigger position: `--trigger-position 25`
- Use different trigger type (rising/falling edge)
- Verify signal integrity

#### Protocol Not Recognized
- Check channel assignments
- Verify signal voltage levels
- Ensure sufficient sample rate (at least 10x the protocol bitrate)
- Confirm correct protocol settings (polarity, mode, etc.)

### Performance Optimization
- For high-speed protocols, use dedicated hardware decoders if available
- Reduce number of displayed channels to improve performance
- Use protocol-specific sample rate recommendations