# Pin Mapping Guide for PAD-CoreBuilder

This guide covers how to properly map and configure pins for custom boards using PAD-CoreBuilder.

## Understanding Pin Mapping

Pin mapping defines how the physical pins of your microcontroller connect to the functions available in your software. PAD-CoreBuilder provides flexible tools to configure pin assignments for different board layouts.

## Pin Types

PAD-CoreBuilder recognizes several pin types:

- `POWER` - Power supply pins (VDD, VSS, etc.)
- `GPIO` - General purpose input/output pins
- `ANALOG` - Analog input pins
- `CLOCK` - Clock input pins (XTAL, MCO, etc.)
- `RESET` - Reset pins
- `COMM` - Communication pins (UART, SPI, I2C)
- `TIMER` - Timer pins (PWM, capture, etc.)

## Board Configuration

Board definitions are stored in JSON format alongside MCU definitions:

```json
{
  "board_name": "Custom Dev Board",
  "mcu": "STM32F407VG",
  "variant": "CustomF4",
  "pins": [
    {
      "name": "LED_BUILTIN",
      "mcu_pin": "PC13",
      "type": "GPIO",
      "pullup": false,
      "pulldown": false
    },
    {
      "name": "BUTTON",
      "mcu_pin": "PA0",
      "type": "GPIO",
      "pullup": true,
      "pulldown": false
    },
    {
      "name": "UART_TX",
      "mcu_pin": "PA9",
      "type": "COMM",
      "function": "USART1_TX"
    },
    {
      "name": "UART_RX",
      "mcu_pin": "PA10",
      "type": "COMM",
      "function": "USART1_RX"
    }
  ]
}
```

## Pin Multiplexing

Many microcontrollers support pin multiplexing where a single physical pin can serve multiple functions. PAD-CoreBuilder handles this through alternate functions:

```json
{
  "name": "ARDUINO_D1",
  "mcu_pin": "PA9",
  "type": "COMM",
  "function": "USART1_TX",
  "alt_functions": [
    {"func": "TIM1_CH2", "af_num": 1},
    {"func": "I2C3_SCL", "af_num": 4},
    {"func": "UART4_TX", "af_num": 8}
  ]
}
```

## Creating Custom Pin Maps

### Step 1: Identify Physical Connections

Document how your board connects to the MCU:

```
Physical Header Pin -> MCU Pin -> Function
D0                  -> PA3     -> USART2_RX
D1                  -> PA2     -> USART2_TX
D2                  -> PA10    -> External Interrupt
D3                  -> PB0     -> PWM (Timer3 Channel 3)
```

### Step 2: Create Board Definition

Create a board definition file:

```json
{
  "board_name": "My Custom Board",
  "mcu": "STM32F407VG",
  "variant": "MyCustomBoard",
  "led_builtin": "PC13",
  "clock_source": "external",
  "xtal_freq": 8000000,
  "pins": [
    {
      "name": "D0",
      "mcu_pin": "PA3",
      "type": "COMM",
      "function": "USART2_RX",
      "aliases": ["RX", "SERIAL_RX"]
    },
    {
      "name": "D1",
      "mcu_pin": "PA2",
      "type": "COMM",
      "function": "USART2_TX",
      "aliases": ["TX", "SERIAL_TX"]
    },
    {
      "name": "D2",
      "mcu_pin": "PA10",
      "type": "GPIO",
      "function": "EXTI10",
      "aliases": ["INTERRUPT_PIN"]
    },
    {
      "name": "D3",
      "mcu_pin": "PB0",
      "type": "TIMER",
      "function": "TIM3_CH3",
      "aliases": ["PWM3", "SERVO3"]
    }
  ]
}
```

### Step 3: Validate Pin Mapping

Use the validation tool to ensure there are no conflicts:

```bash
pad-corebuilder validate --board my_custom_board.json
```

## Arduino Pin Compatibility

For Arduino compatibility, follow these conventions:

- Digital pins: D0, D1, D2, ... DX
- Analog pins: A0, A1, A2, ... AX
- PWM capable: Mark with `pwm_capable: true`
- External interrupts: Mark with `interrupt_capable: true`

## PlatformIO Configuration

When exporting for PlatformIO, additional board parameters can be specified:

```json
{
  "board_name": "My PlatformIO Board",
  "mcu": "STM32F407VG",
  "build": {
    "core": "stm32",
    "cpu": "cortex-m4",
    "f_cpu": "168000000L",
    "mcu": "stm32f407vgt6",
    "variant": "MY_CUSTOM_BOARD"
  },
  "upload": {
    "maximum_size": 1048576,
    "maximum_ram_size": 196608
  },
  "debug": {
    "jtag": ["jtag", "swd"]
  },
  "frameworks": ["arduino", "mbed", "stm32cube"],
  "pins": [...]
}
```

## Pin Assignment Best Practices

### 1. Consistent Naming
Use consistent and descriptive names for pins:
- Use standard names where possible (D0-D19, A0-A7)
- Use functional names for special-purpose pins
- Include aliases for common alternative names

### 2. Organize by Function
Group pins logically in your definition:
- Power pins first
- GPIO pins next
- Communication pins grouped together
- Analog pins in a separate section

### 3. Document Special Features
Include notes about special pin capabilities:
- PWM capable pins
- ADC resolution
- Maximum frequency for timer pins
- Special pull-up/pull-down requirements

## Advanced Pin Features

### Pin Groups
Organize related pins into groups:

```json
{
  "pin_groups": [
    {
      "name": "I2C_BUS",
      "pins": ["SDA", "SCL"],
      "properties": {
        "pullup_required": true,
        "max_frequency": 400000
      }
    },
    {
      "name": "SPI_HEADER",
      "pins": ["MOSI", "MISO", "SCK", "NSS"],
      "properties": {
        "signal_group": "spi1"
      }
    }
  ]
}
```

### Pin Constraints
Specify electrical and timing constraints:

```json
{
  "name": "HIGH_SPEED_SIGNAL",
  "mcu_pin": "PB6",
  "constraints": {
    "max_frequency": 50000000,
    "impedance": 50,
    "slew_rate": "high",
    "drive_strength": "medium"
  }
}
```

## Testing Pin Configurations

### Functional Tests
Create simple tests for each pin type:

1. **Digital I/O Test**
   ```cpp
   pinMode(testPin, OUTPUT);
   digitalWrite(testPin, HIGH);
   delay(1000);
   digitalWrite(testPin, LOW);
   delay(1000);
   ```

2. **Analog Input Test**
   ```cpp
   int value = analogRead(analogPin);
   Serial.println(value);
   ```

3. **Communication Test**
   ```cpp
   Serial.begin(9600);
   Serial.println("Communication test");
   ```

### Automated Validation
PAD-CoreBuilder includes validation tools:

```bash
# Validate pin assignments
pad-corebuilder validate --pins my_board.json

# Check for conflicts
pad-corebuilder check-conflicts --board my_board.json

# Generate pin report
pad-corebuilder report --pins --board my_board.json
```

## Troubleshooting Common Issues

### Pin Conflicts
- Two functions assigned to the same MCU pin
- Solution: Review alternate function assignments

### Electrical Issues
- Improper pull-ups/pull-downs
- Solution: Verify electrical requirements in MCU documentation

### Missing Functions
- Required peripheral not available on selected pin
- Solution: Check MCU reference manual for pin-peripheral mapping

## Exporting Pin Maps

### For Arduino IDE
```bash
pad-corebuilder export --format arduino --board my_board.json --output ~/Arduino/hardware/mycompany
```

### For PlatformIO
```bash
pad-corebuilder export --format platformio --board my_board.json --output ~/.platformio/platforms/myplatform
```

### As JSON Configuration
```bash
pad-corebuilder export --format json --board my_board.json --output my_pin_map.json
```

## Integration with Development Workflows

PAD-CoreBuilder pin maps can be integrated into your development workflow:

1. **CI/CD Pipelines**: Validate pin configurations automatically
2. **Hardware Verification**: Cross-reference with schematic designs
3. **Documentation**: Generate pinout diagrams automatically
4. **Code Generation**: Create board-specific header files