# User Guide

This document provides instructions for using PAD-Scope effectively.

## Overview

PAD-Scope is a virtual oscilloscope that works with your logic analyzer to visualize digital and analog signals in real-time. It supports various trigger modes and protocol decoding for I2C, SPI, and UART communications.

## Getting Started

### Connecting Hardware

1. Connect your logic analyzer to your computer via USB
2. Connect the probes to the signals you want to monitor on your target device
3. Ensure proper ground connection between your analyzer and target device
4. Launch PAD-Scope

### Initial Configuration

1. Select your logic analyzer model from the device list
2. Set the sample rate (higher rates provide better resolution but consume more resources)
3. Configure voltage thresholds for digital signal recognition
4. Adjust timebase settings to fit your signal characteristics

## Main Interface

### Channel Configuration Panel

- Enable/disable individual channels
- Set channel names for easier identification
- Configure probe attenuation if needed
- Choose color coding for each channel

### Trigger Settings

PAD-Scope offers several trigger modes:

- **Edge Trigger**: Trigger on rising or falling edges
- **Pulse Width**: Trigger on pulses of specific width
- **Pattern Match**: Trigger when a specific pattern appears on multiple channels
- **Glitch Detection**: Trigger on unexpected short pulses

### Timebase Controls

- Horizontal scale adjustment (time per division)
- Trigger position control (left/right movement)
- Pre-trigger/post-trigger ratio adjustment

## Protocol Decoding

PAD-Scope supports decoding of common communication protocols:

### I2C Decoder
- Configurable SDA/SCL pins
- Address recognition
- Data packet visualization
- Error detection (NACK, arbitration loss)

### SPI Decoder
- Configurable CLK/MOSI/MISO/CS pins
- Clock polarity and phase settings
- Packet assembly
- Mode selection (0-3)

### UART Decoder
- Configurable TX/RX pins
- Baud rate detection
- Parity and stop bit settings
- ASCII/hexadecimal display options

## Advanced Features

### Mathematical Channels

Create mathematical expressions combining multiple channels:
- Addition, subtraction, multiplication, division
- Functions like sine, cosine, logarithms
- Integration and differentiation
- FFT-based operations

### Export Capabilities

PAD-Scope allows exporting captured data in multiple formats:
- CSV for spreadsheet analysis
- WAV for audio-related signals
- Custom formats for specialized applications

### FFT Analysis

Perform frequency-domain analysis of captured signals:
- Adjustable window functions (Hanning, Hamming, etc.)
- Frequency resolution control
- Spectrum averaging
- Peak detection and labeling

## Tips and Best Practices

- Always ensure proper grounding to avoid noise
- Use appropriate sample rates for your signal frequencies
- Save configurations for repeatable measurements
- Regularly calibrate your logic analyzer for accurate measurements