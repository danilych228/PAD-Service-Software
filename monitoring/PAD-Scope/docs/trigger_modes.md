# Trigger Modes Guide for PAD-Scope

This document describes the various trigger modes available in PAD-Scope for capturing specific signal events.

## Overview

Triggers allow you to capture signal data based on specific conditions, making it easier to analyze intermittent or rare events. PAD-Scope supports multiple trigger types and configurations.

## Trigger Types

### Edge Triggers

Edge triggers detect transitions in signal levels:

#### Rising Edge
Detects when a signal transitions from LOW to HIGH:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type rising
```

#### Falling Edge
Detects when a signal transitions from HIGH to LOW:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type falling
```

#### Either Edge
Triggers on either rising or falling edge:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type either
```

### Level Triggers

Level triggers activate when a signal reaches a specific voltage level:

```bash
# Trigger when signal crosses 1.65V (half of 3.3V logic)
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type level --trigger-level 1.65
```

### Pulse Width Triggers

Trigger on specific pulse characteristics:

#### Narrow Pulse
Triggers on pulses narrower than a specified duration:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type pulse-narrow --pulse-duration 10us
```

#### Wide Pulse
Triggers on pulses wider than a specified duration:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type pulse-wide --pulse-duration 1ms
```

## Trigger Configuration Options

### Trigger Level
For analog-like signals, specify the voltage level that activates the trigger:
```bash
--trigger-level 2.5  # Volts
```

### Trigger Hysteresis
Set hysteresis to prevent noise-triggered false triggers:
```bash
--trigger-hysteresis 0.1  # 0.1V hysteresis window
```

### Trigger Position
Specify where in the capture buffer the trigger event appears:
```bash
--trigger-position 50  # Trigger at 50% of capture buffer (middle)
```

### Trigger Holdoff
Set minimum time between triggers to avoid multiple detections of the same event:
```bash
--trigger-holdoff 100us  # Wait 100 microseconds between triggers
```

## Advanced Trigger Settings

### Digital Pattern Triggers

Trigger when a specific digital pattern occurs across multiple channels:
```bash
# Trigger when channels 0,1,2,3 show pattern 1010
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --trigger-pattern "1010"
```

### Glitch Detection

Detect short-duration glitches in signals:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type glitch --glitch-duration 10ns
```

### Timeout Triggers

Trigger if a signal doesn't transition within a specified time:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type timeout --timeout-duration 100ms
```

## Multiple Trigger Configuration

### Dual Trigger
Use two independent triggers on different channels:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0,1 \
  --trigger1-channel 0 --trigger1-type rising \
  --trigger2-channel 1 --trigger2-type falling
```

### Trigger AND Condition
Only trigger when both conditions are met:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0,1 \
  --trigger1-channel 0 --trigger1-type rising \
  --trigger2-channel 1 --trigger2-type falling \
  --trigger-condition AND
```

### Trigger OR Condition
Trigger when either condition is met:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0,1 \
  --trigger1-channel 0 --trigger1-type rising \
  --trigger2-channel 1 --trigger2-type falling \
  --trigger-condition OR
```

## Practical Examples

### Capturing UART Start Bit
```bash
# Trigger on falling edge of UART RX line (start bit)
pad-scope --device /dev/ttyUSB0 --channels 0 --trigger-channel 0 --trigger-type falling
```

### Capturing I2C Address Phase
```bash
# Trigger on SCL rising edge during I2C transaction
pad-scope --device /dev/ttyUSB0 --channels 0,1 --trigger-channel 1 --trigger-type rising
# Channel 0: SDA, Channel 1: SCL
```

### Capturing SPI Frame
```bash
# Trigger on CS falling edge to capture complete SPI frame
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --trigger-channel 3 --trigger-type falling
# Channels: 0=MOSI, 1=MISO, 2=SCK, 3=CS
```

## Trigger Sensitivity and Noise Reduction

### Debounce Filter
Apply digital debouncing to eliminate contact bounce or noise:
```bash
--trigger-debounce 10us  # Ignore transitions closer than 10 microseconds
```

### Anti-Glitch Filter
Filter out very short pulses that might be noise:
```bash
--trigger-antiglitch 100ns  # Ignore pulses shorter than 100 nanoseconds
```

## Troubleshooting Trigger Issues

### Trigger Not Firing
- Verify the channel is connected to an active signal
- Check that trigger level is within signal range
- Ensure sufficient hysteresis for noisy signals
- Confirm trigger type matches signal characteristics

### False Triggers
- Increase hysteresis to reduce sensitivity to noise
- Use debounce filtering for mechanical switches
- Lower trigger sensitivity
- Add holdoff time between triggers

### Unstable Trigger Point
- Use a more stable reference signal for triggering
- Adjust hysteresis settings
- Check for ground loops causing signal instability
- Ensure adequate signal amplitude

## GUI Configuration

When using the PAD-Scope GUI, trigger settings can be adjusted through:
- Trigger panel with visual representation of trigger level and hysteresis
- Real-time feedback on trigger status
- Presets for common protocols
- Waveform cursor to set trigger point graphically