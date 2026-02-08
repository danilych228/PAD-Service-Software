# Task Timeline Visualization Guide for PAD-Debugger

This document describes how to use task timeline visualization in PAD-Debugger for analyzing RTOS-based applications.

## Overview

The task timeline visualization provides a graphical representation of task execution, scheduling, and interactions over time. This feature is particularly useful for:
- Analyzing task scheduling behavior
- Identifying timing issues
- Understanding resource contention
- Detecting priority inversion
- Visualizing interrupt interactions
- Monitoring RTOS overhead

## Supported RTOS

PAD-Debugger provides timeline visualization for:
- FreeRTOS
- Zephyr RTOS
- ThreadX
- embOS
- RT-Thread
- Custom RTOS implementations (with proper hooks)

## Timeline Views

### Task Execution Timeline
Shows individual tasks and their execution states over time:
- Running (green): Task actively executing on CPU
- Ready (yellow): Task ready to execute but waiting for CPU
- Blocked (red): Task blocked waiting for resources
- Suspended (gray): Task suspended

### Resource Timeline
Displays resource usage and contention:
- Semaphores and mutexes
- Queues and mailboxes
- Memory pools
- Timers and delays

### Interrupt Timeline
Shows interrupt service routine execution:
- ISR execution periods
- Interrupt nesting levels
- Interrupt impact on task execution

## Basic Usage

### Command Line Options

```bash
# Enable timeline visualization with RTOS support
pad-debugger --timeline --rtos freertos --target firmware.elf

# Set timeline resolution (higher resolution = more detail)
pad-debugger --timeline --timeline-resolution 1ms --target firmware.elf

# Save timeline to file for offline analysis
pad-debugger --timeline --timeline-save timeline.json --target firmware.elf

# Start with timeline view maximized
pad-debugger --timeline --timeline-fullscreen --target firmware.elf
```

### GUI Controls

The timeline view includes these interactive controls:
- Zoom in/out with mouse wheel or pinch gesture
- Pan horizontally to navigate through time
- Click on tasks to see detailed information
- Hover over elements to see tooltips
- Right-click for context menu with additional options

## RTOS Integration Details

### FreeRTOS Integration

PAD-Debugger leverages FreeRTOS trace hooks for timeline data:

```c
// Required trace hooks for FreeRTOS
extern "C" {
    void vApplicationIdleHook(void) {
        // Called during idle task execution
    }

    void vApplicationTickHook(void) {
        // Called during each RTOS tick
    }

    void traceTASK_SWITCHED_IN(void) {
        // Called when task switches in
    }

    void traceTASK_SWITCHED_OUT(void) {
        // Called when task switches out
    }

    void traceBLOCKING_ON_QUEUE_RECEIVE(xQueueHandle pxQueue) {
        // Called when blocking on queue receive
    }
}
```

### Zephyr RTOS Integration

For Zephyr applications, enable the following options:
```yaml
CONFIG_TRACING: y
CONFIG_TRACING_CPU_STATS: y
CONFIG_TRACING_SCHEDULER: y
```

## Timeline Analysis Features

### Task Statistics
- Execution time per task
- Average execution time
- Maximum execution time
- Task utilization percentage
- Number of context switches

### Timing Analysis
- Inter-task communication delays
- Resource acquisition times
- Deadline compliance checking
- Periodic task timing accuracy

### Deadlock Detection
PAD-Debugger can automatically detect potential deadlocks:
- Circular wait conditions
- Priority inversion scenarios
- Mutex contention patterns

### Performance Metrics
- Scheduler overhead
- Interrupt latency
- Task response time
- CPU utilization per task

## Advanced Timeline Features

### Filtering and Focus

You can filter the timeline view to focus on specific elements:

```bash
# Show only specific tasks
pad-debugger --timeline --show-tasks "task1,task2,task3" --target firmware.elf

# Hide idle tasks
pad-debugger --timeline --hide-idle --target firmware.elf

# Filter by priority range
pad-debugger --timeline --priority-range 1-10 --target firmware.elf
```

### Markers and Annotations

Add custom markers to the timeline:

```c
// Add custom markers in your code
#include "tracing.h"

void my_function(void) {
    trace_marker("START_FUNCTION");
    // Function implementation
    trace_marker("END_FUNCTION");
}
```

### Export and Reporting

Export timeline data for external analysis:

```bash
# Export as JSON for custom analysis
pad-debugger --timeline --export-json timeline.json --target firmware.elf

# Export as CSV for spreadsheet analysis
pad-debugger --timeline --export-csv timeline.csv --target firmware.elf

# Generate PDF report
pad-debugger --timeline --report-pdf timeline_report.pdf --target firmware.elf
```

## Visualization Options

### Color Coding

The timeline uses consistent color coding:
- Tasks: Each task has a unique color assigned automatically
- States: Green (running), Yellow (ready), Red (blocked), Gray (suspended)
- Resources: Blue for semaphores, Orange for queues, Purple for timers
- Interrupts: Red shades based on priority level

### Time Scales

Multiple time scales are available:
- Nanoseconds (for high-precision analysis)
- Microseconds (recommended for most RTOS analysis)
- Milliseconds (for longer-term behavior)
- Seconds (for very long-running processes)

## Troubleshooting Timeline Issues

### Common Problems

1. **Timeline not showing RTOS tasks**
   - Ensure RTOS trace hooks are properly implemented
   - Verify that RTOS symbols are not stripped from ELF file
   - Check that RTOS configuration enables tracing

2. **High CPU usage during timeline capture**
   - Reduce timeline resolution
   - Limit the number of tracked tasks
   - Use software buffering to reduce UI updates

3. **Missing timeline data**
   - Increase trace buffer size
   - Check that trace hooks are called in all relevant places
   - Verify that tracing is enabled in RTOS configuration

### Performance Tips

- Use hardware timestamps when available
- Buffer trace data in RAM before processing
- Limit the time window displayed in GUI
- Filter out low-priority tasks if not needed

## Integration with Other Debugging Features

The timeline integrates with other PAD-Debugger features:

- Combine with SWO tracing to correlate events
- Use with memory watchpoints to detect resource conflicts
- Integrate with breakpoint conditions for targeted analysis
- Link with call stack visualization for deeper insights

## Custom Timeline Scripts

Advanced users can create custom timeline analysis scripts:

```python
# timeline_analysis.py
import json

def analyze_timeline(timeline_file):
    with open(timeline_file, 'r') as f:
        data = json.load(f)
    
    # Custom analysis logic
    tasks = data['tasks']
    for task in tasks:
        print(f"Task {task['name']}: {task['utilization']}% utilization")
        
    return data
```

This allows for automated analysis and reporting of timeline data.