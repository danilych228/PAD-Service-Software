# Peripheral Templates Guide for PAD-CoreBuilder

This guide explains how to use and create peripheral templates in PAD-CoreBuilder for efficient core generation.

## Overview

Peripheral templates are reusable components that define the structure and behavior of common microcontroller peripherals. They allow for rapid core creation by providing standardized definitions for commonly-used peripherals like timers, UARTs, GPIOs, and more.

## Template Structure

A peripheral template consists of a base definition that can be instantiated multiple times with different parameters:

```json
{
  "template_name": "uart_base",
  "description": "Base template for UART peripherals",
  "registers": [
    {
      "name": "DR",
      "offset": "0x00",
      "size": 8,
      "access": "rw",
      "description": "Data register"
    },
    {
      "name": "SR",
      "offset": "0x04",
      "size": 8,
      "access": "r",
      "description": "Status register"
    },
    {
      "name": "CR1",
      "offset": "0x08",
      "size": 16,
      "access": "rw",
      "description": "Control register 1"
    }
  ],
  "interrupts": [
    {
      "name": "TXE",
      "bit_position": 7,
      "description": "Transmit data register empty"
    },
    {
      "name": "RXNE",
      "bit_position": 5,
      "description": "Read data register not empty"
    }
  ],
  "features": [
    "transmit",
    "receive",
    "parity_check",
    "hardware_flow_control"
  ]
}
```

## Available Template Types

### GPIO Template

The GPIO template defines general-purpose input/output ports:

```json
{
  "template_name": "gpio_port",
  "description": "Template for GPIO ports",
  "registers": [
    {
      "name": "MODER",
      "offset": "0x00",
      "size": 32,
      "description": "Mode register"
    },
    {
      "name": "OTYPER",
      "offset": "0x04",
      "size": 32,
      "description": "Output type register"
    },
    {
      "name": "OSPEEDR",
      "offset": "0x08",
      "size": 32,
      "description": "Output speed register"
    },
    {
      "name": "PUPDR",
      "offset": "0x0C",
      "size": 32,
      "description": "Pull-up/pull-down register"
    },
    {
      "name": "IDR",
      "offset": "0x10",
      "size": 32,
      "description": "Input data register"
    },
    {
      "name": "ODR",
      "offset": "0x14",
      "size": 32,
      "description": "Output data register"
    },
    {
      "name": "BSRR",
      "offset": "0x18",
      "size": 32,
      "description": "Bit set/reset register"
    },
    {
      "name": "LCKR",
      "offset": "0x1C",
      "size": 32,
      "description": "Lock register"
    },
    {
      "name": "AFRL",
      "offset": "0x20",
      "size": 32,
      "description": "Alternate function low register"
    },
    {
      "name": "AFRH",
      "offset": "0x24",
      "size": 32,
      "description": "Alternate function high register"
    }
  ],
  "features": [
    "input_mode",
    "output_mode",
    "alternate_function",
    "analog_mode"
  ]
}
```

### Timer Template

The timer template supports various timer configurations:

```json
{
  "template_name": "timer_advanced",
  "description": "Advanced timer with PWM and capture features",
  "registers": [
    {
      "name": "CR1",
      "offset": "0x00",
      "size": 16,
      "description": "Control register 1"
    },
    {
      "name": "CR2",
      "offset": "0x04",
      "size": 16,
      "description": "Control register 2"
    },
    {
      "name": "SMCR",
      "offset": "0x08",
      "size": 16,
      "description": "Slave mode control register"
    },
    {
      "name": "DIER",
      "offset": "0x0C",
      "size": 16,
      "description": "DMA/Interrupt enable register"
    },
    {
      "name": "SR",
      "offset": "0x10",
      "size": 16,
      "description": "Status register"
    },
    {
      "name": "EGR",
      "offset": "0x14",
      "size": 16,
      "description": "Event generation register"
    },
    {
      "name": "CCMR1",
      "offset": "0x18",
      "size": 16,
      "description": "Capture/Compare mode register 1"
    },
    {
      "name": "CCMR2",
      "offset": "0x1C",
      "size": 16,
      "description": "Capture/Compare mode register 2"
    },
    {
      "name": "CCER",
      "offset": "0x20",
      "size": 16,
      "description": "Capture/Compare enable register"
    },
    {
      "name": "CNT",
      "offset": "0x24",
      "size": 16,
      "description": "Counter register"
    },
    {
      "name": "PSC",
      "offset": "0x28",
      "size": 16,
      "description": "Prescaler register"
    },
    {
      "name": "ARR",
      "offset": "0x2C",
      "size": 16,
      "description": "Auto-reload register"
    }
  ],
  "features": [
    "pwm_generation",
    "input_capture",
    "one_pulse_mode",
    "encoder_interface"
  ]
}
```

### ADC Template

The ADC template for analog-to-digital converters:

```json
{
  "template_name": "adc_basic",
  "description": "Basic ADC peripheral template",
  "registers": [
    {
      "name": "SR",
      "offset": "0x00",
      "size": 32,
      "description": "Status register"
    },
    {
      "name": "CR1",
      "offset": "0x04",
      "size": 32,
      "description": "Control register 1"
    },
    {
      "name": "CR2",
      "offset": "0x08",
      "size": 32,
      "description": "Control register 2"
    },
    {
      "name": "SMPR1",
      "offset": "0x0C",
      "size": 32,
      "description": "Sample time register 1"
    },
    {
      "name": "SMPR2",
      "offset": "0x10",
      "size": 32,
      "description": "Sample time register 2"
    },
    {
      "name": "JOFR1",
      "offset": "0x14",
      "size": 32,
      "description": "Injected channel data offset register 1"
    },
    {
      "name": "HTR",
      "offset": "0x24",
      "size": 32,
      "description": "Watchdog higher threshold register"
    },
    {
      "name": "LTR",
      "offset": "0x28",
      "size": 32,
      "description": "Watchdog lower threshold register"
    },
    {
      "name": "SQR1",
      "offset": "0x2C",
      "size": 32,
      "description": "Regular sequence register 1"
    },
    {
      "name": "JSQR",
      "offset": "0x38",
      "size": 32,
      "description": "Injected sequence register"
    },
    {
      "name": "JDR1",
      "offset": "0x3C",
      "size": 32,
      "description": "Injected data register 1"
    },
    {
      "name": "DR",
      "offset": "0x4C",
      "size": 32,
      "description": "Regular data register"
    }
  ],
  "features": [
    "single_conversion",
    "continuous_conversion",
    "discontinuous_mode",
    "dma_support"
  ]
}
```

## Using Templates in MCU Definitions

To use a template in an MCU definition, reference it in the peripheral list:

```json
{
  "mcu_name": "MyCustomMCU",
  "peripherals": [
    {
      "name": "GPIOA",
      "template": "gpio_port",
      "base_address": "0x40020000"
    },
    {
      "name": "GPIOB",
      "template": "gpio_port",
      "base_address": "0x40020400"
    },
    {
      "name": "USART1",
      "template": "uart_base",
      "base_address": "0x40011000",
      "parameters": {
        "irq_number": 37,
        "dma_channels": [4, 7]
      }
    }
  ]
}
```

## Creating Custom Templates

### Step 1: Define the Template Structure

Create a new template definition file:

```json
{
  "template_name": "my_custom_peripheral",
  "description": "Description of what this peripheral does",
  "category": "communication",  // Options: gpio, timer, communication, analog, etc.
  "registers": [
    // Register definitions as shown above
  ],
  "interrupts": [
    // Interrupt definitions
  ],
  "features": [
    // Feature list
  ],
  "parameters": {
    // Configurable parameters
    "irq_number": {
      "type": "integer",
      "description": "Interrupt request number",
      "default": 0
    },
    "dma_channels": {
      "type": "array",
      "description": "Available DMA channels",
      "default": []
    }
  }
}
```

### Step 2: Validate the Template

Validate your template before using it:

```bash
pad-corebuilder validate --template my_custom_peripheral.json
```

### Step 3: Register the Template

Add your template to the core builder's template registry:

```bash
pad-corebuilder register-template --template my_custom_peripheral.json
```

## Template Parameters

Templates can accept parameters to customize their instantiation:

```json
{
  "name": "SPI1",
  "template": "spi_master",
  "base_address": "0x40013000",
  "parameters": {
    "max_speed": 50000000,
    "data_width": 8,
    "slave_select_count": 4,
    "fifo_depth": 16
  }
}
```

## Advanced Template Features

### Conditional Registers

Some registers may only exist under certain conditions:

```json
{
  "template_name": "advanced_uart",
  "registers": [
    {
      "name": "DR",
      "offset": "0x00",
      "size": 8,
      "description": "Data register"
    },
    {
      "name": "GTPR",
      "offset": "0x20",
      "size": 16,
      "description": "Guard time and prescaler register",
      "condition": "feature == 'smartcard'"
    }
  ]
}
```

### Register Arrays

For peripherals with multiple similar registers:

```json
{
  "template_name": "dma_controller",
  "registers": [
    {
      "name": "CCR",
      "offset": "0x08",
      "size": 32,
      "array_size": 7,  // Creates CCR1, CCR2, ..., CCR7
      "element_stride": 0x14,
      "description": "Channel configuration register array"
    }
  ]
}
```

## Template Libraries

PAD-CoreBuilder comes with a comprehensive library of templates for common peripherals:

- `gpio_port` - General-purpose I/O ports
- `uart_base` - Universal asynchronous receiver/transmitter
- `spi_master` - Serial peripheral interface master
- `i2c_controller` - Inter-integrated circuit controller
- `timer_basic` - Basic timer
- `timer_advanced` - Advanced timer with PWM
- `adc_basic` - Analog-to-digital converter
- `dac_basic` - Digital-to-analog converter
- `rtc_base` - Real-time clock
- `wdg_base` - Watchdog timer
- `crc_base` - Cyclic redundancy check
- `dma_controller` - Direct memory access controller

## Best Practices

### 1. Consistent Naming
Use consistent naming conventions across all templates:
- Register names in uppercase (e.g., CR1, SR, DR)
- Descriptions in sentence case
- Feature names in lowercase with underscores

### 2. Complete Documentation
Include detailed descriptions for:
- Each register and its fields
- All available features
- Parameter requirements and constraints

### 3. Modular Design
Design templates to be:
- Reusable across different MCUs
- Extensible for future enhancements
- Compatible with existing templates

### 4. Validation
Always validate templates:
- Check register overlaps
- Verify address alignment
- Test parameter ranges

## Troubleshooting

### Common Issues

1. **Register Overlap**: Ensure no two registers share the same offset
2. **Parameter Mismatch**: Verify all required parameters are provided
3. **Template Not Found**: Check registration and spelling of template names
4. **Invalid Addresses**: Validate base addresses align with MCU memory map

### Debugging Templates

Use verbose output to debug template issues:

```bash
pad-corebuilder create --mcu MyMCU --verbose --debug-templates
```

## Creating Template Documentation

Generate documentation for your templates:

```bash
pad-corebuilder doc --template my_template.json --output docs/my_template.md
```

This creates comprehensive documentation with register maps, bit field definitions, and usage examples.