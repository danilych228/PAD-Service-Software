# Adding New MCUs to PAD-CoreBuilder

This guide explains how to add support for new microcontrollers to PAD-CoreBuilder.

## Overview

PAD-CoreBuilder supports adding new MCUs through a flexible configuration system. Each MCU definition includes essential parameters, pin mappings, and peripheral specifications.

## MCU Definition Structure

MCU definitions are stored in JSON format with the following structure:

```json
{
  "mcu_name": "STM32F407VG",
  "family": "ARM Cortex-M",
  "manufacturer": "STMicroelectronics",
  "core": "Cortex-M4",
  "max_clock_speed": 168000000,
  "flash_size": 1048576,
  "ram_size": 196608,
  "package": "LQFP100",
  "pins": [
    {
      "name": "VDD",
      "type": "POWER",
      "position": 1
    },
    {
      "name": "PA0",
      "type": "GPIO",
      "position": 2,
      "functions": ["GPIO", "ADC1_IN0", "TIM2_CH1_ETR", "USART2_CTS", "ETH_MII_CRS"]
    },
    {
      "name": "PA1",
      "type": "GPIO",
      "position": 3,
      "functions": ["GPIO", "ADC1_IN1", "TIM2_CH2", "USART2_RTS", "ETH_RMII_REF_CLK"]
    }
  ],
  "peripherals": [
    {
      "name": "RCC",
      "base_address": "0x40023800",
      "registers": [
        {
          "name": "CR",
          "offset": "0x00",
          "size": 32,
          "description": "Clock control register"
        }
      ]
    }
  ]
}
```

## Adding an MCU Step-by-Step

### Step 1: Gather MCU Specifications

Before adding an MCU, collect the following information:

- Complete datasheet and reference manual
- Pinout diagram
- Memory map
- Register definitions for all peripherals
- Clock tree information
- Power consumption specifications
- Package information

### Step 2: Create the MCU Definition File

Create a new JSON file in the `mcus/` directory:

```bash
# Example
touch mcus/my_new_mcu.json
```

### Step 3: Define Basic Properties

Start with basic MCU properties:

```json
{
  "mcu_name": "MY_NEW_MCU",
  "family": "ARM Cortex-M",
  "manufacturer": "MyCompany",
  "core": "Cortex-M3",
  "max_clock_speed": 72000000,
  "flash_size": 524288,
  "ram_size": 65536,
  "package": "LQFP48"
}
```

### Step 4: Map Pins

Define all pins with their functions:

```json
{
  "pins": [
    {
      "name": "VDD",
      "type": "POWER",
      "position": 1,
      "description": "Supply voltage"
    },
    {
      "name": "PB6",
      "type": "GPIO",
      "position": 2,
      "functions": ["GPIO", "I2C1_SCL", "TIM4_CH1"],
      "description": "General purpose I/O pin with alternate functions"
    }
  ]
}
```

### Step 5: Define Peripherals

List all available peripherals with their base addresses and registers:

```json
{
  "peripherals": [
    {
      "name": "GPIOB",
      "base_address": "0x40020400",
      "registers": [
        {
          "name": "MODER",
          "offset": "0x00",
          "size": 32,
          "description": "Port mode register"
        },
        {
          "name": "OTYPER",
          "offset": "0x04",
          "size": 32,
          "description": "Port output type register"
        }
      ]
    }
  ]
}
```

### Step 6: Validate Your Definition

Use the validation tool to check your definition:

```bash
pad-corebuilder validate --mcu my_new_mcu.json
```

### Step 7: Test the Core Generation

Generate a core using your new MCU definition:

```bash
pad-corebuilder create --mcu MY_NEW_MCU --name TestCore
```

## Peripheral Template System

PAD-CoreBuilder includes a template system for common peripherals:

### GPIO Template

```json
{
  "name": "GPIO",
  "template": "gpio_base",
  "instances": ["GPIOA", "GPIOB", "GPIOC"],
  "base_address_offset": "0x400",
  "register_template": {
    "MODER": {
      "offset": "0x00",
      "size": 32
    },
    "OTYPER": {
      "offset": "0x04",
      "size": 32
    }
  }
}
```

### Timer Template

```json
{
  "name": "TIM",
  "template": "timer_advanced",
  "instances": ["TIM1", "TIM2", "TIM3"],
  "base_address_offset": "0x400",
  "features": ["PWM", "Input Capture", "One Pulse Mode"]
}
```

## Pin Multiplexing

Many MCUs support pin multiplexing where a single physical pin can serve multiple functions. Define this in the pin configuration:

```json
{
  "name": "PA9",
  "type": "GPIO",
  "position": 45,
  "functions": [
    {"name": "GPIO", "af": -1},
    {"name": "USART1_TX", "af": 7},
    {"name": "I2C3_SCL", "af": 4},
    {"name": "TIM1_CH2", "af": 1}
  ]
}
```

## Memory Regions

Define memory regions for the linker:

```json
{
  "memory_regions": [
    {
      "name": "FLASH",
      "origin": "0x08000000",
      "length": "1024K",
      "type": "rom"
    },
    {
      "name": "RAM",
      "origin": "0x20000000",
      "length": "128K",
      "type": "ram"
    }
  ]
}
```

## Clock Configuration

Specify the clock tree and configuration options:

```json
{
  "clock_tree": {
    "hsi_freq": 16000000,
    "hse_freq": 8000000,
    "pll_configurable": true,
    "max_sysclk": 168000000,
    "peripheral_clocks": {
      "APB1": {
        "max_freq": 42000000,
        "peripherals": ["USART2", "SPI2"]
      },
      "APB2": {
        "max_freq": 84000000,
        "peripherals": ["USART1", "SPI1"]
      }
    }
  }
}
```

## Testing New MCU Definitions

After defining your MCU, test it thoroughly:

1. Generate a basic core
2. Create simple projects using different peripherals
3. Verify pin mappings are correct
4. Test clock configuration
5. Validate memory layout

## Contributing New MCUs

If you've successfully added support for a popular MCU, consider contributing it back to the main repository:

1. Fork the repository
2. Add your MCU definition to the appropriate folder
3. Include documentation and example projects
4. Submit a pull request with your changes

## Troubleshooting

### Common Issues

1. **Incorrect base addresses**: Verify addresses in the reference manual
2. **Pin function conflicts**: Check for overlapping alternate functions
3. **Memory region overlaps**: Ensure regions don't overlap
4. **Clock configuration errors**: Verify PLL and prescaler calculations

### Validation Commands

```bash
# Validate a single MCU definition
pad-corebuilder validate --mcu my_mcu.json

# Validate all definitions
pad-corebuilder validate --all

# Generate with verbose output
pad-corebuilder create --mcu MY_MCU --verbose
```

## Best Practices

- Use consistent naming conventions
- Include comprehensive descriptions
- Verify all values against official documentation
- Test generated cores with real hardware when possible
- Provide example projects for validation