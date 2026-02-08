# Peripheral Templates for PAD-CoreBuilder

This document describes how to create and use peripheral templates in PAD-CoreBuilder.

## Introduction

Peripheral templates are reusable configurations that define how to set up and use common hardware peripherals in embedded applications. They simplify the process of configuring complex peripherals by providing standardized structures and initialization routines.

## Template Structure

A peripheral template is defined in JSON format with the following structure:

```json
{
  "template_id": "spi_master_v1",
  "name": "SPI Master",
  "version": "1.0",
  "description": "Template for configuring SPI in master mode",
  "category": "communication",
  "dependencies": [
    "gpio",
    "rcc"
  ],
  "registers": [
    {
      "name": "SPI_CR1",
      "address_offset": "0x00",
      "fields": [
        {
          "name": "CPHA",
          "bit_position": 0,
          "width": 1,
          "description": "Clock phase",
          "default_value": 0
        },
        {
          "name": "CPOL",
          "bit_position": 1,
          "width": 1,
          "description": "Clock polarity",
          "default_value": 0
        },
        {
          "name": "MSTR",
          "bit_position": 2,
          "width": 1,
          "description": "Master selection",
          "default_value": 1
        }
      ]
    }
  ],
  "configuration_options": [
    {
      "name": "clock_speed",
      "type": "int",
      "range": [1000, 50000000],
      "default": 1000000,
      "description": "SPI clock speed in Hz"
    },
    {
      "name": "data_bits",
      "type": "int",
      "range": [4, 16],
      "default": 8,
      "description": "Number of data bits"
    }
  ],
  "api_functions": [
    {
      "name": "initialize",
      "description": "Initialize SPI peripheral with given configuration",
      "parameters": [
        {
          "name": "config",
          "type": "spi_config_t",
          "description": "Configuration structure"
        }
      ]
    },
    {
      "name": "transfer",
      "description": "Send and receive data over SPI",
      "parameters": [
        {
          "name": "tx_data",
          "type": "uint8_t*",
          "description": "Data to transmit"
        },
        {
          "name": "rx_data",
          "type": "uint8_t*",
          "description": "Buffer for received data"
        },
        {
          "name": "length",
          "type": "uint32_t",
          "description": "Number of bytes to transfer"
        }
      ]
    }
  ],
  "examples": [
    {
      "name": "Basic SPI Master",
      "description": "Configure SPI as master and perform a simple transfer",
      "code": "#include \"spi_master.h\"\n\nint main() {\n    spi_config_t config = {\n        .clock_speed = 1000000,\n        .data_bits = 8\n    };\n    \n    spi_initialize(&config);\n    \n    uint8_t tx_data[] = {0x55, 0xAA};\n    uint8_t rx_data[2];\n    \n    spi_transfer(tx_data, rx_data, 2);\n    \n    return 0;\n}"
    }
  ]
}
```

## Key Components

### Registers Section
Defines the hardware registers associated with the peripheral, including:
- Register names and addresses
- Bit fields within each register
- Default values for each field

### Configuration Options
Specifies configurable parameters for the peripheral, such as:
- Clock speeds
- Data sizes
- Operating modes
- Pin selections

### API Functions
Describes the software interface for controlling the peripheral, including:
- Initialization functions
- Data transfer methods
- Status checking functions
- Configuration update methods

## Using Templates

### In the PAD-CoreBuilder UI
1. Select the desired peripheral from the template library
2. Adjust configuration options as needed
3. Generate the initialization code
4. Integrate into your project

### Programmatically
Templates can be applied programmatically using the PAD-CoreBuilder API:

```bash
./pad-corebuilder apply-template --mcu STM32F407VG --template spi_master_v1 --output src/spi.c
```

## Creating Custom Templates

To create a custom template:
1. Study existing templates in the `templates/` directory
2. Create a new JSON file following the structure above
3. Validate the template syntax
4. Test with a sample project
5. Submit for inclusion in the standard library

## Best Practices

- Use descriptive names for registers and fields
- Include comprehensive documentation for each element
- Provide practical examples
- Validate against actual hardware specifications
- Maintain backward compatibility when updating templates