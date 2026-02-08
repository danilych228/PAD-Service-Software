# Memory Watchpoints Guide for PAD-Debugger

This document describes how to use memory watchpoints in PAD-Debugger for advanced debugging scenarios.

## Overview

Memory watchpoints allow you to monitor specific memory addresses for read, write, or read/write access. This is particularly useful for:
- Detecting buffer overflows
- Monitoring global variable changes
- Identifying memory corruption issues
- Tracking RTOS kernel data structures

## Types of Memory Watchpoints

### Hardware Watchpoints
- Implemented directly in the CPU's debug unit
- Limited number (typically 2-4 on ARM Cortex-M)
- Fastest execution speed
- Can only watch exact addresses

### Software Watchpoints
- Implemented by the debugger
- Virtually unlimited number
- Slower execution speed
- Can watch complex expressions

## Setting Memory Watchpoints

### Command Line Interface

```bash
# Watch a specific memory address for writes
pad-debugger --watch-write 0x20001000 --target firmware.elf

# Watch a memory range for reads
pad-debugger --watch-read 0x20001000-0x200010FF --target firmware.elf

# Watch a symbol for any access
pad-debugger --watch-access "global_variable" --target firmware.elf

# Set multiple watchpoints
pad-debugger --watch-write 0x20001000 --watch-access 0x20002000 --target firmware.elf
```

### In-Session Commands

Once in a debugging session, you can set watchpoints dynamically:

```
# Add a watchpoint for write access to an address
(pad-debugger) watch_write 0x20001000

# Add a watchpoint for read access to a variable
(pad-debugger) watch_read my_global_var

# Add a watchpoint for any access to a memory range
(pad-debugger) watch_access 0x20001000 32  # Watch 32 bytes starting at 0x20001000

# List all active watchpoints
(pad-debugger) watchpoints

# Remove a watchpoint
(pad-debugger) unwatch 1  # Remove watchpoint #1
```

## RTOS Integration

PAD-Debugger provides special watchpoint capabilities for RTOS debugging:

### FreeRTOS Integration
```bash
# Automatically watch FreeRTOS kernel data structures
pad-debugger --rtos freertos --watch-rtos --target firmware.elf

# Watch specific FreeRTOS objects
pad-debugger --watch-access "&xQueue1" --target firmware.elf
```

The debugger will automatically detect and set watchpoints on:
- Queue structures
- Semaphore structures
- Task control blocks
- Event groups

### ThreadX Integration
```bash
# Watch ThreadX kernel objects
pad-debugger --rtos threadx --watch-rtos --target firmware.elf
```

## Practical Examples

### Detecting Buffer Overflow

```c
// In your code
uint8_t buffer[10];
// Intentionally write beyond bounds to trigger watchpoint
buffer[15] = 0xFF;  // This will trigger the watchpoint
```

Set a watchpoint to catch this:
```bash
# Watch the memory area immediately after the buffer
pad-debugger --watch-write 0x2000100A --target firmware.elf
```

### Monitoring Global Variables

```c
// Global variable that changes unexpectedly
volatile int system_state = 0;
```

Monitor changes:
```bash
# Watch the variable for any write access
pad-debugger --watch-write "system_state" --target firmware.elf
```

### Stack Overflow Detection

```bash
# Watch the end of a task's stack
pad-debugger --watch-write 0x20002000 --target firmware.elf
```

## Watchpoint Conditions

You can add conditions to watchpoints to reduce noise:

```bash
# Only trigger when a specific value is written
(pad-debugger) watch_write 0x20001000 condition="value == 0xDEADBEEF"

# Only trigger when a specific register has a value
(pad-debugger) watch_access my_var condition="r0 == 0x12345678"

# Complex conditions using expressions
(pad-debugger) watch_write global_flag condition="(task_id == 5) && (critical_section == 1)"
```

## Performance Considerations

### Hardware vs Software Watchpoints
- Use hardware watchpoints when possible for better performance
- Software watchpoints require frequent context switches
- Some operations may become significantly slower with software watchpoints

### Memory Access Patterns
Watchpoints can significantly affect timing, especially:
- In interrupt handlers
- In time-critical code
- When watching frequently accessed memory

## Visualization Features

PAD-Debugger provides visual representations of watchpoint activity:

### Memory Map View
- Color-coded regions showing watched memory areas
- Real-time updates when watched memory is accessed
- Historical access patterns

### Timeline Integration
- Watchpoint hits shown on the task timeline
- Correlation with other debugging events
- Performance impact visualization

### Task Correlation
- Identify which task caused the watchpoint hit
- Track access patterns by different tasks
- Detect inter-task interference

## Troubleshooting

### Common Issues

1. **"Too many hardware watchpoints"**
   - Solution: Use software watchpoints or fewer hardware watchpoints
   - Use `--watch-soft` flag to force software watchpoints

2. **"Watchpoint not triggered"**
   - Check alignment of watched address
   - Verify memory region is accessible
   - Check if code runs from flash (may not trigger watchpoints)

3. **Performance degradation**
   - Reduce number of active watchpoints
   - Use hardware watchpoints when possible
   - Add conditions to reduce trigger frequency

### Limitations

- ARM Cortex-M: Maximum 4 hardware watchpoints
- Watchpoints may not work in exception handlers
- Some memory regions may not support watchpoints

## Best Practices

1. **Use specific addresses**: More efficient than watching large ranges
2. **Add conditions**: Reduce noise with conditional watchpoints
3. **Monitor critical sections**: Use watchpoints to detect race conditions
4. **Combine with RTOS awareness**: Leverage RTOS knowledge for better debugging
5. **Document watchpoints**: Keep track of why each watchpoint was set

## Advanced Usage

### Scripting Watchpoints

You can automate watchpoint setup with scripts:

```bash
#!/bin/bash
# watchpoint_setup.sh

pad-debugger \
  --watch-write "&critical_data" \
  --watch-access "&semaphore" \
  --watch-write "0x20001000" \
  --script "analyze_watchpoints.py" \
  --target firmware.elf
```

### Conditional Breakpoints

Combine watchpoints with conditional breakpoints:

```
(pad-debugger) watch_write my_var
(pad-debugger) break main.c:42 condition="watchpoint_hit == 1"
```

This approach allows you to break when a watched memory location is modified.