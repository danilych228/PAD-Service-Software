# Protocol Specifications for PAD-Flasher

This document outlines the supported protocols and their specifications in PAD-Flasher.

## Supported Protocols

### UART Protocol
- Standard baud rates: 9600, 115200, 230400, 460800, 921600
- Data bits: 8
- Stop bits: 1
- Parity: None
- Flow control: Optional RTS/CTS
- Frame format: SLIP (Serial Line Internet Protocol) encapsulation
- Timeout: Configurable (default 5 seconds)

### JTAG Protocol
- Supports standard JTAG pinout: TCK, TDO, TDI, TMS, TRST
- Clock speeds: 1kHz to 25MHz
- Supports standard JTAG commands: IDCODE, BYPASS, EXTEST, SAMPLE
- Chain detection and device enumeration
- SVF (Serial Vector Format) file support

### SWD Protocol
- Two-wire interface: SWDIO, SWCLK
- SWD and SWD+ modes supported
- Standard ARM Cortex-M register access
- DP (Debug Port) and AP (Access Port) operations
- SWO (Single Wire Output) trace support

### SPI Protocol
- Standard 4-wire SPI: MOSI, MISO, SCK, CS
- Modes 0-3 supported (CPOL/CPHA combinations)
- Clock speeds: 10kHz to 50MHz
- Standard SPI flash commands supported
- Custom bootloader command sets

## Protocol Configuration

Protocols can be configured via command line or configuration files:

### Command Line Options
```
--protocol uart|jtag|swd|spi
--baudrate <rate> (for UART)
--clock-speed <freq> (for JTAG/SWD/SPI)
--connection-timeout <ms>
--retries <count>
```

### Configuration File Format
```json
{
  "protocol": "uart",
  "settings": {
    "baudrate": 115200,
    "databits": 8,
    "stopbits": 1,
    "parity": "none",
    "flowcontrol": false
  },
  "validation": {
    "checksum": true,
    "verify_after_flash": true
  }
}
```

## Error Handling

Each protocol implements specific error handling:
- Communication timeouts
- CRC/checksum failures
- Invalid responses
- Device identification mismatches

## Extending Protocols

New protocols can be added by implementing the ProtocolInterface class in the src/protocols directory.

## Security Considerations

- Authentication mechanisms for secure bootloaders
- Encrypted payload support
- Secure element integration for key storage