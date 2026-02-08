# Frequently Asked Questions (FAQ) for PAD-CoreBuilder

## General Questions

### What is PAD-CoreBuilder?
PAD-CoreBuilder is a powerful generator for Arduino IDE/PlatformIO cores that enables rapid development and customization of microcontroller support packages. It provides an intuitive interface for creating custom cores with drag-and-drop peripheral configuration.

### What platforms does PAD-CoreBuilder support?
PAD-CoreBuilder supports:
- Linux (Ubuntu, Debian, Fedora, Arch, etc.)
- macOS (10.14+)
- Windows (10, 11)

### Can I use PAD-CoreBuilder for commercial projects?
Yes, PAD-CoreBuilder is distributed under the MIT License, which allows for commercial use. There are no restrictions on using generated cores in commercial projects.

## Technical Questions

### Which microcontrollers are supported?
PAD-CoreBuilder supports all major microcontroller families:
- ARM Cortex-M series (M0, M0+, M3, M4, M7, M33)
- ESP32 family (ESP32, ESP32-C3, ESP32-S3, ESP8266)
- AVR series (ATmega, ATtiny, XMEGA)
- RISC-V cores (GD32VF103, SiFive)
- Proprietary cores can be added using the flexible configuration system

### How does the template system work?
The template system provides predefined structures for common peripherals like GPIO, UART, SPI, I2C, timers, and ADCs. These templates can be customized and reused across different MCUs to streamline core development.

### What file formats are supported?
- MCU definitions: JSON format
- Board definitions: JSON format
- Peripheral templates: JSON format
- Export formats: Arduino hardware format, PlatformIO platform format

## Usage Questions

### How do I create a new core?
You can create a new core using the command line:
```bash
pad-corebuilder create --mcu my_mcu.json --name MyCore --author "Author Name"
```

Or using the GUI:
```bash
pad-corebuilder gui
```

### Can I customize existing cores?
Yes, you can modify existing core definitions and regenerate them with your customizations. PAD-CoreBuilder maintains separation between the core generation templates and your customizations.

### How do I add a new microcontroller?
To add a new microcontroller, create a JSON definition file that specifies:
- Basic MCU properties (name, family, core, memory sizes)
- Pin definitions and functions
- Peripheral definitions with base addresses
- Memory map and clock configuration

See the [Adding New MCUs Guide](./adding_new_mcus.md) for detailed instructions.

### How do I map custom pins for my board?
Create a board definition file that maps logical pin names (like D0, D1, LED_BUILTIN) to physical MCU pins. The [Pin Mapping Guide](./pin_mapping.md) provides detailed instructions and examples.

## Troubleshooting

### Why is my generated core not compiling?
Common causes include:
- Missing toolchain for the target MCU
- Incorrect memory region definitions
- Syntax errors in configuration files
- Missing startup code or linker scripts

Check the compilation logs for specific error messages and validate your configuration files.

### How can I debug issues with generated cores?
Enable verbose output during core generation:
```bash
pad-corebuilder create --mcu my_mcu.json --verbose
```

Also validate your configurations before generation:
```bash
pad-corebuilder validate --mcu my_mcu.json
```

### What should I do if export fails?
If export to Arduino IDE or PlatformIO fails:
1. Check directory permissions
2. Verify the target directory exists
3. Use the `--force` flag to overwrite existing files
4. Ensure no other processes are accessing the target directory

## Performance and Scalability

### How long does core generation take?
Core generation typically takes a few seconds for simple MCUs and up to a minute for complex MCUs with many peripherals. Performance depends on system resources and the complexity of the MCU definition.

### How much memory does PAD-CoreBuilder require?
PAD-CoreBuilder requires approximately 100-500MB of RAM depending on the complexity of the MCU being processed. Additional memory is needed for compilation of generated cores.

## Integration

### Can I integrate PAD-CoreBuilder into my CI/CD pipeline?
Yes, PAD-CoreBuilder is designed for automation with:
- Comprehensive command-line interface
- Machine-readable output formats
- Exit codes for success/failure detection
- Batch processing capabilities

### How do I validate configurations programmatically?
Use the validation commands:
```bash
# Validate MCU definition
pad-corebuilder validate --mcu my_mcu.json

# Validate board definition
pad-corebuilder validate --board my_board.json

# Validate template
pad-corebuilder validate --template my_template.json

# Validate everything
pad-corebuilder validate --all
```

## Support and Community

### Where can I get help?
You can get support through:
- Our [community forum](https://community.pad-service.ru/)
- Email support: [support@pad-service.ru](mailto:support@pad-service.ru)
- GitHub issues: [PAD-CoreBuilder Repository](https://github.com/pad-service/pad-corebuilder/issues)

### How often is PAD-CoreBuilder updated?
We release regular updates with new MCU support, bug fixes, and feature enhancements. Stable releases are published quarterly, with critical fixes released as needed.

### Can I contribute to PAD-CoreBuilder development?
Yes! Contributions are welcome. Check our [contributing guidelines](../CONTRIBUTING.md) for information on how to submit improvements, bug fixes, or new features.

### How do I report a bug?
When reporting bugs, please include:
- PAD-CoreBuilder version (`pad-corebuilder --version`)
- Operating system and hardware details
- Exact command used and full error output
- Relevant configuration files
- Steps to reproduce the issue

## Advanced Topics

### How do I create custom peripheral templates?
Create a JSON file with the template definition including registers, interrupts, and features. See the [Peripheral Templates Guide](./peripheral_templates.md) for detailed specifications and examples.

### Can I extend the GUI interface?
The GUI is built with extensibility in mind. You can create plugins to extend functionality, though this requires C++ programming skills and familiarity with the internal APIs.

### How does the drag-and-drop interface work?
The GUI interface uses SDL2 for rendering and provides a visual canvas where you can:
- Drag peripheral components onto the workspace
- Connect components to visualize relationships
- Configure parameters through property panels
- Preview generated code before export

## Licensing

### What license is PAD-CoreBuilder distributed under?
PAD-CoreBuilder is distributed under the MIT License. See the [LICENSE](../LICENSE) file for complete terms.

### Are there any restrictions on the generated cores?
No, there are no restrictions on the cores generated by PAD-CoreBuilder. The generated code is owned by you and can be used freely according to the licensing terms of the underlying MCU manufacturers.

## Migration and Compatibility

### Can I migrate from other core generators?
PAD-CoreBuilder is designed to be compatible with existing Arduino and PlatformIO workflows. You can gradually migrate by generating new cores for your MCUs while maintaining existing projects.

### How do I update an existing generated core?
To update an existing core:
1. Modify your MCU/board definition files
2. Regenerate the core using the same command
3. Replace the old core in your development environment
4. Test thoroughly with your existing projects

## Comparison with Alternatives

### How does PAD-CoreBuilder compare to manual core creation?
PAD-CoreBuilder significantly reduces the time and expertise needed to create new cores compared to manual creation. It handles complex aspects like register definitions, linker scripts, and startup code automatically.

### What advantages does PAD-CoreBuilder offer over other tools?
PAD-CoreBuilder offers:
- Intuitive GUI for visual core design
- Flexible template system for rapid development
- Comprehensive validation tools
- Multi-format export (Arduino, PlatformIO)
- Extensive documentation and examples
- Active community and commercial support