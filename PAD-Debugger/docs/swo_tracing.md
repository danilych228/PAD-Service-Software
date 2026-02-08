# SWO Tracing Guide for PAD-Debugger

This document describes how to use Serial Wire Output (SWO) tracing capabilities in PAD-Debugger for non-intrusive debugging and profiling.

## Overview

Serial Wire Output (SWO) is an ARM Cortex-M feature that allows real-time trace data to be output from the target microcontroller. PAD-Debugger provides comprehensive support for SWO including ITM (Instrumentation Trace Macrocell) and DWT (Data Watchpoint and Trace) trace data.

## Hardware Setup

### Required Hardware
- ARM Cortex-M microcontroller with SWO pin available
- Debug adapter supporting SWO (CMSIS-DAP v2+, J-Link, ST-Link v3, etc.)
- SWO pin connected to your debug adapter or logic analyzer
- Appropriate pull-up resistor on SWO line (typically 10kΩ to VCC)

### Pin Configuration
The SWO pin is usually:
- **STM32**: PA10 (STM32F0/1/3) or PB3 (STM32F4/L4/G4)
- **NXP Kinetis**: TDO/SWO pin
- **Nordic nRF**: PIN_USBD_SWO or dedicated SWO pin
- **Other manufacturers**: Refer to datasheet for SWO pin assignment

## Software Configuration

### Enabling SWO in Firmware

In your firmware, you'll need to enable SWO output:

```c
#include <stdio.h>

// Enable SWO output for printf-like functionality
void enable_swo(void) {
    // Enable trace in core debug register
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    
    // Configure TPIU to output at the desired baud rate
    TPIU->CSPSR = 1; // Single-pin trace output
    
    // Set prescaler for desired baud rate
    // Example: 8MHz SWO clock, 1MHz trace rate
    TPIU->ACPR = (8000000 / 1000000) - 1; // Adjust based on your SWO clock
    
    // Configure formatter to enable trace
    TPIU->FFCR &= ~TPIU_FFCR_ENFPOS_Msk;
    
    // Enable ITM
    ITM->TCR = ITM_TCR_TraceBusID_Msk | ITM_TCR_SWOENA_Msk | ITM_TCR_SYNCENA_Msk;
    ITM->TER = 0xFFFFFFFF; // Enable all stimulus ports
}

// Function to output trace data
static inline int swo_print_char(char c) {
    if (ITM->PORT[0].u32) {
        ITM->PORT[0].u8 = c;
        return 1;
    }
    return 0;
}

// Printf-like function for SWO output
int swo_printf(const char* format, ...) {
    // Implementation of printf that outputs to SWO
    // ...
}
```

### Configuring PAD-Debugger

```bash
# Enable SWO with specific baud rate
pad-debugger --swo 2000000 --target firmware.elf --interface swd

# Enable ITM decoder for formatted output
pad-debugger --swo 2000000 --itm-decoder --target firmware.elf

# Save trace data to file
pad-debugger --swo 2000000 --trace-file trace.log --target firmware.elf
```

## SWO Capabilities

### ITM (Instrumentation Trace Macrocell)
- Up to 32 stimulus ports (0-31)
- Supports 8-bit, 16-bit, and 32-bit writes
- Used for printf-style debugging and event tracing

### DWT (Data Watchpoint and Trace)
- PC sampling for profiling
- Watchpoint triggering
- Exception trace
- Interrupt trace

### Trace Analysis Features

PAD-Debugger provides several analysis features for SWO data:

1. **Real-time Console Output**
   - View printf-style output from target
   - Color-coded by stimulus port
   - Timestamped events

2. **Function Profiling**
   - Identify hotspots in code
   - Call frequency analysis
   - Execution time measurement

3. **Event Correlation**
   - Correlate trace events with source code
   - Visual timeline of events
   - Task switching visualization

## Advanced SWO Features

### Custom Trace Protocols

You can implement custom trace protocols:

```c
// Define custom trace messages
typedef enum {
    TRACE_EVENT_START = 1,
    TRACE_EVENT_END,
    TRACE_TASK_SWITCH,
    TRACE_ISR_ENTER,
    TRACE_ISR_EXIT,
} trace_event_t;

// Send structured trace data
void trace_event(trace_event_t event, uint32_t data) {
    uint32_t msg = ((uint32_t)event << 24) | (data & 0x00FFFFFF);
    ITM_SendWord(1, msg); // Use stimulus port 1 for structured data
}
```

### Real-time Analysis

PAD-Debugger supports real-time analysis of trace data:

```bash
# Monitor specific stimulus ports
pad-debugger --swo 2000000 --monitor-port 0 --target firmware.elf

# Filter trace by message type
pad-debugger --swo 2000000 --filter "event_type=TRACE_TASK_SWITCH" --target firmware.elf

# Generate performance reports
pad-debugger --swo 2000000 --profile --target firmware.elf
```

## Troubleshooting SWO

### Common Issues

1. **No SWO Data Received**
   - Verify SWO pin is properly connected
   - Check that SWO clock speed matches target configuration
   - Ensure firmware enables SWO output

2. **Garbled Trace Output**
   - Verify SWO baud rate matches between debugger and target
   - Check for signal integrity issues
   - Reduce SWO baud rate if necessary

3. **High CPU Overhead**
   - Minimize SWO output in performance-critical code
   - Use conditional compilation for trace code
   - Consider using DWT for profiling instead of ITM

### Performance Impact

SWO has minimal impact on target performance, but consider:

- Stimulus port writes have variable latency
- High-frequency trace output may affect real-time behavior
- Buffer overflow can cause lost trace data

## Integration with RTOS

PAD-Debugger can integrate SWO tracing with RTOS awareness:

```c
// FreeRTOS trace hooks
extern "C" {
    void vApplicationMallocFailedHook(void) {
        trace_event(TRACE_EVENT_START, 0);
    }
    
    void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
        trace_event(TRACE_TASK_SWITCH, (uint32_t)xTask);
    }
    
    void vApplicationTickHook(void) {
        // Send periodic tick information
        ITM_SendWord(31, 0x12345678); // High-priority stimulus
    }
}
```

This integration allows PAD-Debugger to visualize task scheduling, stack usage, and other RTOS events in real-time.