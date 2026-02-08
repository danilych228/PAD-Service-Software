# Adding New MCU to PAD-CoreBuilder

This guide explains how to add support for a new microcontroller unit (MCU) in PAD-CoreBuilder.

## Prerequisites

- Access to the MCU datasheet and reference manual
- Knowledge of the MCU's memory map, registers, and peripherals
- Familiarity with JSON configuration files

## Step-by-Step Process

### 1. Create MCU Definition File

Create a new JSON file in the `mcus/` directory with the MCU's specifications:

```json
{
  "name": "NewMCU123",
  "family": "ARM Cortex-M4",
  "manufacturer": "Acme Corp",
  "core": "Cortex-M4F",
  "flash_size": 524288,
  "ram_size": 131072,
  "clock_speed": 168000000,
  "packages": [
    {
      "name": "LQFP64",
      "pins": 64
    }
  ],
  "peripherals": [
    {
      "name": "GPIOA",
      "base_address": "0x40020000",
      "registers": [
        {
          "name": "MODER",
          "offset": "0x00",
          "size": 4,
          "description": "Port mode register"
        }
      ]
    }
  ],
  "interrupts": [
    {
      "name": "NVIC_WWDG_IRQn",
      "number": 0,
      "description": "Window Watchdog interrupt"
    }
  ]
}
```

### 2. Define Pin Mapping

Create a pin mapping file that defines how the physical pins correspond to the MCU's internal signals:

```json
{
  "package": "LQFP64",
  "pin_map": [
    {
      "pin_number": 1,
      "pin_name": "PB9",
      "functions": ["GPIO", "I2C1_SDA", "TIM11_CH1"]
    },
    {
      "pin_number": 2,
      "pin_name": "PB8",
      "functions": ["GPIO", "I2C1_SCL", "TIM10_CH1"]
    }
  ]
}
```

### 3. Configure Peripheral Templates

Define templates for common peripherals to simplify their use in projects:

```json
{
  "template": "uart",
  "description": "Universal Asynchronous Receiver Transmitter",
  "registers": [
    {
      "name": "USART_BRR",
      "description": "Baud rate register",
      "default_value": 0x00000000
    }
  ],
  "dependencies": ["GPIO"],
  "examples": [
    {
      "name": "Basic UART",
      "code": "// Initialize UART with 115200 baudrate\nUART_Init(115200);"
    }
  ]
}
```

### 4. Validate Configuration

Use the validation tool to ensure your MCU definition is correct:

```bash
./pad-corebuilder validate --mcu NewMCU123
```

### 5. Generate Core Files

Generate the necessary files for Arduino IDE or PlatformIO:

```bash
./pad-corebuilder generate --mcu NewMCU123 --output /path/to/output/directory
```

## Testing the New MCU Support

1. Install the generated core in your development environment
2. Create a simple test project
3. Verify that basic functionality works (GPIO, timers, etc.)
4. Test peripheral configurations
5. Report any issues to the PAD-Service team

## Best Practices

- Follow the existing naming conventions
- Include comprehensive comments in your configuration files
- Provide example code for complex peripherals
- Test thoroughly before submitting for review