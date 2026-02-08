# PAD-Flasher Protocol Specifications

## Overview
This document describes the communication protocols supported by PAD-Flasher for device flashing operations.

## Supported Interfaces

### UART Protocol
- Standard serial communication
- Configurable baud rates: 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600
- Data bits: 8, Stop bits: 1, Parity: None
- Flow control: Optional RTS/CTS

### JTAG Protocol
- Standard IEEE 1149.1 compliant interface
- Supports boundary scan operations
- TCK frequency configurable up to 10MHz
- Standard JTAG commands implemented:
  - BYPASS
  - IDCODE
  - SAMPLE/PRELOAD
  - EXTEST
  - CLAMP

### SWD Protocol
- Serial Wire Debug interface
- Two-wire communication (SWDIO, SWCLK)
- Supports SWD and JTAG modes
- Clock frequencies up to 12MHz
- Standard SWD commands:
  - DP Read/Write
  - AP Read/Write
  - SWD Sequence Interface

## Packet Structure

### Command Packets
```
[START_BYTE][CMD_TYPE][PAYLOAD_LENGTH][PAYLOAD][CHECKSUM][END_BYTE]
```

- START_BYTE: 0xAA
- CMD_TYPE: 1 byte command identifier
- PAYLOAD_LENGTH: 2 bytes, little-endian
- PAYLOAD: variable length data
- CHECKSUM: 1 byte XOR checksum
- END_BYTE: 0x55

### Response Packets
```
[START_BYTE][RESP_TYPE][PAYLOAD_LENGTH][PAYLOAD][CHECKSUM][END_BYTE]
```

### Command Types
| Code | Description |
|------|-------------|
| 0x01 | FLASH_INIT |
| 0x02 | FLASH_WRITE |
| 0x03 | FLASH_READ |
| 0x04 | FLASH_VERIFY |
| 0x05 | RESET_DEVICE |
| 0x06 | GET_STATUS |
| 0x07 | SET_BAUDRATE |
| 0x08 | ENTER_BOOTLOADER |

## Error Codes
| Code | Description |
|------|-------------|
| 0x00 | SUCCESS |
| 0x01 | COMMUNICATION_ERROR |
| 0x02 | INVALID_COMMAND |
| 0x03 | FLASH_ERROR |
| 0x04 | VERIFY_FAILED |
| 0x05 | TIMEOUT_ERROR |
| 0x06 | CHECKSUM_MISMATCH |
| 0x07 | INSUFFICIENT_MEMORY |
| 0x08 | DEVICE_LOCKED |

## Timing Requirements

### UART Interface
- Inter-byte gap: 1ms minimum
- Command response timeout: 5 seconds
- Bulk write timeout: 30 seconds per 64KB

### JTAG Interface
- TCK period: 100ns to 100ms
- TMS setup time: 50ns minimum
- TDO hold time: 10ns minimum
- Reset pulse width: 50 TCK cycles

### SWD Interface
- SWCLK period: 83ns to 100ms (12MHz to 10Hz)
- SWDIO setup time: 50ns minimum
- SWDIO hold time: 10ns minimum
- Line activity: 100ms timeout

## Recovery Mode Protocol
When a device enters recovery mode:

1. Host sends RECOVERY_ENTER command
2. Device responds with supported recovery methods
3. Host selects recovery method
4. Normal flashing proceeds

Recovery methods include:
- Mass erase
- Bootloader reset
- Hardware reset
- ISP entry sequence