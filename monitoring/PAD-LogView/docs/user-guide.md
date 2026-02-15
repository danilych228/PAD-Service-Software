# User Guide

This document provides instructions for using PAD-LogView effectively.

## Overview

PAD-LogView is a log aggregation tool that collects logs from multiple devices over network/COM connections. It provides filtering, searching, and visualization capabilities for debugging distributed systems and embedded applications.

## Getting Started

### Connection Setup

1. Configure connection parameters for your target devices
2. Specify network addresses or COM port settings
3. Set up authentication if required
4. Launch PAD-LogView

### Initial Configuration

1. Define log formats for different device types
2. Set up color coding for different log levels
3. Configure automatic log rotation settings
4. Establish filter presets for common scenarios

## Main Interface

### Log Display Panel

The main panel shows aggregated logs from all connected devices:

- Timestamped entries with source identification
- Color-coded log levels (DEBUG, INFO, WARN, ERROR)
- Collapsible sections for better readability
- Live updating of incoming logs

### Filter Control Panel

- Text-based search with regular expression support
- Log level filtering controls
- Source/device filtering
- Time range selection
- Custom field filtering

## Core Features

### Multi-Device Aggregation

PAD-LogView can handle logs from multiple sources simultaneously:

- Network connections (TCP/UDP)
- Serial/COM port connections
- File-based log inputs
- Mixed connection types

### Advanced Filtering

Comprehensive filtering options:

- Regex pattern matching
- Boolean combinations (AND, OR, NOT)
- Field-specific filters (timestamp, level, source, etc.)
- Saved filter presets

### Search Capabilities

Powerful search functionality:

- Case-sensitive/insensitive options
- Full-text search across all fields
- Search highlighting in results
- Search history and bookmarks

## Visualization Options

### Timeline View

Visualize log events over time:

- Spaghetti diagrams showing concurrent activities
- Event density charts
- Time gap analysis
- Correlation views between devices

### Statistics Panel

Get insights from your logs:

- Log volume by level and source
- Frequency analysis of repeated messages
- Error rate tracking
- Performance metrics extraction

## Export and Storage

### Export Formats

PAD-LogView supports multiple export formats:

- Raw log files preserving original format
- Structured JSON for programmatic processing
- CSV for spreadsheet analysis
- Filtered exports with applied criteria

### Session Recording

Record entire sessions for later analysis:

- Capture current view with all filters applied
- Record raw incoming data stream
- Timestamped session archives
- Compressed storage for large datasets

## Integration

### ELK Stack Export

Export logs to Elasticsearch/Logstash/Kibana:

- Direct Elasticsearch indexing
- Logstash-compatible formatting
- Kibana dashboard templates
- Index lifecycle management

### Script Integration

Automate log processing:

- Command-line interface for scripting
- REST API for programmatic access
- Webhook notifications for specific events
- Plugin architecture for custom processing

## Tips and Best Practices

- Use structured logging formats when possible
- Implement consistent timestamp formats across devices
- Use meaningful source identifiers
- Regularly clean up old log files to maintain performance
- Utilize filter presets for common debugging scenarios
- Take advantage of regex capabilities for complex searches