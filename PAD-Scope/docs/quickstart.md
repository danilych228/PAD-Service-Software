# Quick Start Guide for PAD-Scope

This guide will help you get started with PAD-Scope in just 5 minutes.

## Prerequisites

- Linux/macOS/Windows system
- Compatible development board with logical analyzer capability
- USB cable to connect board to computer
- Signals to analyze connected to digital pins

## Installation

For detailed installation instructions, please see the [Installation Guide](./install.md).

## Basic Usage

1. Connect your board to the computer via USB
2. Connect the signals you want to analyze to digital pins on the board
3. Run PAD-Scope with basic parameters:

```bash
pad-scope --device /dev/ttyUSB0 --channels 0,1 --sample-rate 1000000
```

This command will:
- Connect to the board on `/dev/ttyUSB0`
- Monitor channels 0 and 1 (corresponding to digital pins)
- Sample at 1 MHz rate
- Display real-time oscilloscope view

## Channel Selection

Select channels to monitor based on your board's pin numbers:

```bash
# Monitor single channel
pad-scope --device /dev/ttyUSB0 --channels 3 --sample-rate 100000

# Monitor multiple channels
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --sample-rate 1000000

# Monitor all available channels
pad-scope --device /dev/ttyUSB0 --channels all --sample-rate 500000
```

## Basic Controls

Once PAD-Scope is running, you can use these keyboard controls:
- Arrow keys: Pan through the captured data
- +/-: Zoom in/out horizontally
- PgUp/PgDown: Adjust vertical scale
- T: Toggle trigger mode
- R: Refresh capture
- Q: Quit

## Trigger Modes

Set up triggering to capture specific events:

```bash
# Rising edge trigger on channel 0
pad-scope --device /dev/ttyUSB0 --channels 0,1 --trigger-channel 0 --trigger-type rising

# Falling edge trigger
pad-scope --device /dev/ttyUSB0 --channels 0,1 --trigger-channel 0 --trigger-type falling

# Level trigger at specific threshold
pad-scope --device /dev/ttyUSB0 --channels 0,1 --trigger-channel 0 --trigger-level 1.5
```

## Protocol Decoding

Decode common protocols directly in PAD-Scope:

```bash
# Decode UART communication on channels 0 (RX) and 1 (TX)
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol uart --uart-baud 115200

# Decode I2C on channels 0 (SDA) and 1 (SCL)
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol i2c

# Decode SPI on channels 0 (MOSI), 1 (MISO), 2 (SCK), 3 (CS)
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --protocol spi --spi-mode 0
```

## Exporting Data

Save your captures for later analysis:

```bash
# Export to CSV format
pad-scope --device /dev/ttyUSB0 --channels 0,1 --export-csv capture.csv

# Export to WAV audio format (for audio signals)
pad-scope --device /dev/ttyUSB0 --channels 0 --export-wav audio.wav

# Export with specific sample rate
pad-scope --device /dev/ttyUSB0 --channels 0,1 --sample-rate 1000000 --export-csv high_speed_capture.csv
```

## Next Steps

- Learn about advanced [Trigger Modes](./trigger_modes.md)
- Explore [Protocol Decoding](./protocol_decoding.md) options
- Discover [Export Formats](./export_formats.md) capabilities
- Check out [Troubleshooting Guide](./troubleshooting.md)