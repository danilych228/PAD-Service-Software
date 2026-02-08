# Pin Mapping Guide for PAD-CoreBuilder

This document explains how to create and manage pin mappings for MCUs in PAD-CoreBuilder.

## Overview

Pin mapping defines the relationship between physical pins on an MCU package and the internal signals (GPIOs, peripherals, etc.) that those pins can control. Proper pin mapping is essential for correct hardware abstraction layer (HAL) generation.

## Pin Mapping Structure

The pin mapping is defined in a JSON file with the following structure:

```json
{
  "package": "LQFP64",
  "pins": [
    {
      "number": 1,
      "name": "PB9",
      "type": "GPIO",
      "functions": [
        {
          "name": "GPIO",
          "description": "General purpose input/output"
        },
        {
          "name": "I2C1_SDA",
          "description": "I2C data line"
        },
        {
          "name": "TIM11_CH1",
          "description": "Timer 11 channel 1"
        }
      ],
      "properties": {
        "max_drive_strength": "4mA",
        "schmitt_trigger": true,
        "pull_up_down": true
      }
    }
  ]
}
```

### Field Descriptions

- `package`: The name of the physical package (e.g., LQFP64, TQFP48)
- `pins`: An array of pin definitions
- `number`: The physical pin number on the package
- `name`: The logical name of the pin (e.g., PB9, PA0)
- `type`: The primary function type (GPIO, ADC, etc.)
- `functions`: An array of all possible functions for this pin
- `properties`: Additional electrical properties of the pin

## Creating a New Pin Map

### Step 1: Identify Package Information

First, determine the exact package name and pin count from the MCU datasheet. Common packages include:
- LQFP (Low-profile Quad Flat Package)
- TQFP (Thin Quad Flat Package)
- QFN (Quad Flat No-leads)
- BGA (Ball Grid Array)

### Step 2: Document All Pins

For each pin, record:
- Physical pin number
- Logical signal name
- All possible alternate functions
- Electrical characteristics

### Step 3: Define Functions

List all possible functions for each pin according to the datasheet. This includes:
- GPIO (general purpose input/output)
- ADC channels
- Timer inputs/outputs
- Communication interfaces (SPI, I2C, UART, CAN)
- Analog functions (DAC, comparator inputs)
- Clock inputs
- Reset pins
- Supply pins (VDD, VSS, etc.)

### Step 4: Specify Properties

Document electrical properties where applicable:
- Drive strength options
- Schmitt trigger capability
- Internal pull-up/pull-down resistors
- Maximum voltage ratings
- Open-drain capability

## Validation

Validate your pin mapping using the built-in tool:

```bash
./pad-corebuilder validate-pin-map --file my_pin_map.json
```

This will check for:
- Missing pins
- Duplicate pin numbers
- Incorrect syntax
- Conflicting functions

## Integration

Once validated, place the pin map file in the appropriate directory within the PAD-CoreBuilder configuration hierarchy. The system will automatically detect and use the mapping when generating cores for the specified MCU and package combination.