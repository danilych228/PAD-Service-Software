# Export Formats Guide for PAD-Scope

This document describes the various export formats available in PAD-Scope for saving and sharing your signal captures.

## Available Export Formats

PAD-Scope supports multiple export formats for different use cases:

- CSV (Comma-Separated Values) - for spreadsheet analysis
- WAV (Waveform Audio File Format) - for audio signals
- BIN (Binary Format) - for raw data
- PNG (Portable Network Graphics) - for screenshots
- VCD (Value Change Dump) - for simulation tools
- MATLAB - for mathematical analysis

## CSV Export

CSV export saves captured digital and analog values in a tabular format suitable for spreadsheet applications and data analysis tools.

### Basic CSV Export
```bash
# Export all channels to CSV
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --export-csv capture.csv

# Export with specific sample rate
pad-scope --device /dev/ttyUSB0 --channels 0,1 --sample-rate 1000000 --export-csv high_speed.csv
```

### CSV Export Options
```bash
--export-csv <filename>           # Export to CSV format
--csv-sample-rate <rate>          # Override sample rate for export
--csv-include-time true           # Include timestamp column (default: true)
--csv-delimiter comma             # Delimiter: comma, semicolon, tab (default: comma)
--csv-headers true                # Include column headers (default: true)
--csv-precision 6                 # Decimal precision for floating point values
--csv-no-metadata                 # Exclude metadata from export
```

### CSV File Format
The CSV export includes:
- Time column (seconds or samples)
- Channel columns with voltage values
- Metadata in comments (unless disabled)
- Column headers describing each channel

Example CSV output:
```
# PAD-Scope CSV Export
# Date: 2023-06-15
# Sample Rate: 1000000 Hz
# Channels: 0,1
Time(s),Channel_0(V),Channel_1(V)
0.000000,0.000000,3.300000
0.000001,0.000000,3.300000
0.000002,0.000000,3.300000
0.000003,3.300000,3.300000
```

## WAV Export

WAV export converts digital signals to audio format, useful for analyzing audio signals or converting digital patterns to audible tones.

### Basic WAV Export
```bash
# Export single channel as audio
pad-scope --device /dev/ttyUSB0 --channels 0 --export-wav audio.wav

# Export with specific audio parameters
pad-scope --device /dev/ttyUSB0 --channels 0 --export-wav audio.wav --wav-sample-rate 44100 --wav-bits 16
```

### WAV Export Options
```bash
--export-wav <filename>           # Export to WAV format
--wav-sample-rate 44100           # Audio sample rate (default: 44100 Hz)
--wav-bits 16                     # Audio bit depth (default: 16 bits)
--wav-channel mono                # Channel mode: mono, stereo (default: mono)
--wav-scale auto                  # Scaling method: auto, linear, logarithmic
```

### WAV Applications
- Converting digital signals to audible form for analysis
- Sharing audio signal captures
- Integration with audio analysis tools
- Educational demonstrations

## Binary Export

Binary export saves raw sample data in compact binary format for efficient storage and fast loading.

### Basic Binary Export
```bash
# Export raw binary data
pad-scope --device /dev/ttyUSB0 --channels 0,1 --export-bin capture.bin

# Export with metadata
pad-scope --device /dev/ttyUSB0 --channels 0,1 --export-bin capture.bin --bin-with-metadata
```

### Binary Export Options
```bash
--export-bin <filename>           # Export to binary format
--bin-with-metadata               # Include metadata header (default: false)
--bin-sample-format int16         # Sample format: int8, int16, int32, float32
--bin-byte-order little           # Byte order: little, big (default: little)
```

## PNG Export

PNG export saves the current display view as an image file, useful for documentation and reports.

### Basic PNG Export
```bash
# Export current view to PNG
pad-scope --device /dev/ttyUSB0 --channels 0,1 --export-png screenshot.png

# Export with custom resolution
pad-scope --device /dev/ttyUSB0 --channels 0,1 --export-png waveform.png --png-width 1920 --png-height 1080
```

### PNG Export Options
```bash
--export-png <filename>           # Export to PNG format
--png-width 1024                  # Image width in pixels (default: 1024)
--png-height 768                  # Image height in pixels (default: 768)
--png-quality 95                  # JPEG quality (if applicable)
--png-transparent false           # Use transparent background (default: false)
--png-include-ui true             # Include UI elements in export (default: true)
```

## VCD Export

VCD export follows the IEEE 1364 Value Change Dump format, commonly used in digital design simulation.

### Basic VCD Export
```bash
# Export digital signals in VCD format
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --export-vcd simulation.vcd
```

### VCD Export Options
```bash
--export-vcd <filename>           # Export to VCD format
--vcd-timescale 1ns               # Time scale (default: 1ns)
--vcd-scope-module main           # Module name for VCD scope (default: main)
--vcd-vars-registers              # Variable types: registers, wires (default: wires)
```

## MATLAB Export

MATLAB export creates MAT files readable by MATLAB and Octave for advanced signal processing.

### Basic MATLAB Export
```bash
# Export to MATLAB format
pad-scope --device /dev/ttyUSB0 --channels 0,1 --export-mat data.mat
```

### MATLAB Export Options
```bash
--export-mat <filename>           # Export to MATLAB format
--mat-variable-prefix scope       # Prefix for variable names (default: scope)
--mat-compress true               # Compress the MAT file (default: true)
```

## Protocol-Specific Exports

### Export Decoded Protocol Data
```bash
# Export UART decoded data
pad-scope --device /dev/ttyUSB0 --channels 0 --protocol uart --export-protocol-txt uart_data.txt

# Export I2C transactions in table format
pad-scope --device /dev/ttyUSB0 --channels 0,1 --protocol i2c --export-protocol-csv i2c_transactions.csv

# Export SPI data in binary format
pad-scope --device /dev/ttyUSB0 --channels 0,1,2,3 --protocol spi --export-protocol-bin spi_frames.bin
```

## Batch Export

PAD-Scope supports exporting multiple segments or the entire capture history.

### Export Multiple Segments
```bash
# Export each trigger event as separate file
pad-scope --device /dev/ttyUSB0 --channels 0,1 --trigger-type rising --export-segments captures/

# Export time windows
pad-scope --device /dev/ttyUSB0 --channels 0,1 --export-windows 1s --export-dir captures/
```

### Batch Export Options
```bash
--export-segments <directory>     # Export each triggered segment to separate files
--export-windows <duration>       # Export fixed time windows
--export-dir <directory>          # Base directory for exports
--export-prefix <prefix>          # Filename prefix for exports
--export-numbered true            # Use numbered filenames (default: true)
```

## Export Configuration Files

Save export settings in configuration files for consistent output:

### Example Configuration File
```json
{
  "export": {
    "csv": {
      "include_time": true,
      "delimiter": "comma",
      "headers": true,
      "precision": 8
    },
    "png": {
      "width": 1280,
      "height": 720,
      "transparent": false
    },
    "wav": {
      "sample_rate": 48000,
      "bits": 24,
      "channel": "mono"
    }
  }
}
```

Use with:
```bash
pad-scope --device /dev/ttyUSB0 --channels 0,1 --config export_settings.json --export-csv capture.csv
```

## Performance Considerations

### Large Capture Files
- Use binary format for fastest export
- Consider exporting segments rather than entire capture
- Use appropriate sample rate to balance quality and file size

### Memory Usage
- Binary exports use less memory during creation
- CSV exports may require more memory for large captures
- Monitor system resources during export operations

### File Size Optimization
- Select only necessary channels for export
- Use appropriate sample rate for the signal being analyzed
- Consider compression options for binary formats

## Import Compatibility

### Spreadsheet Applications
- CSV exports are compatible with Excel, LibreOffice Calc, Google Sheets
- Use appropriate delimiter based on regional settings

### Analysis Tools
- WAV files work with audio analysis software
- Binary files can be read by custom analysis programs
- VCD files integrate with HDL simulators

### Programming Libraries
- CSV files easily parsed by Python pandas, NumPy
- Binary files efficiently read by C/C++, MATLAB
- WAV files supported by audio processing libraries