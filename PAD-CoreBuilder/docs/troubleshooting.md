# Troubleshooting Guide for PAD-CoreBuilder

This guide helps diagnose and resolve common issues encountered when using PAD-CoreBuilder.

## Installation Issues

### Missing Dependencies

**Problem:** Installation fails due to missing dependencies.

**Solutions:**
```bash
# On Ubuntu/Debian
sudo apt update
sudo apt install build-essential cmake git python3-dev python3-pip

# On Fedora/RHEL
sudo dnf install gcc gcc-c++ make cmake git python3-devel python3-pip

# On macOS
xcode-select --install
brew install cmake python3
```

### Permission Errors

**Problem:** Installation fails due to permission issues.

**Solutions:**
- Run with appropriate permissions (using sudo where necessary)
- Check user account permissions
- Verify installation directory permissions

## Core Generation Issues

### Invalid MCU Definition

**Problem:** Core generation fails with "invalid MCU definition" error.

**Solutions:**
1. Validate the MCU definition file:
   ```bash
   pad-corebuilder validate --mcu my_mcu.json
   ```
   
2. Check for required fields:
   - `mcu_name`
   - `family`
   - `core`
   - `flash_size`
   - `ram_size`

3. Verify base addresses don't overlap
4. Check register definitions for correctness

### Pin Mapping Conflicts

**Problem:** Error indicating conflicting pin assignments.

**Solutions:**
1. Check for duplicate pin names
2. Verify no two functions are assigned to the same physical pin
3. Validate alternate function assignments

### Missing Peripheral Templates

**Problem:** Error "template not found" when generating core.

**Solutions:**
1. Check template name spelling
2. Verify template is registered:
   ```bash
   pad-corebuilder list-templates
   ```
3. Register missing template:
   ```bash
   pad-corebuilder register-template --template my_template.json
   ```

## Export Issues

### Arduino IDE Export Failures

**Problem:** Export to Arduino hardware folder fails.

**Solutions:**
1. Verify Arduino IDE installation path
2. Check permissions in hardware directory
3. Ensure no existing conflicting core
4. Use `--force` flag to overwrite existing cores

### PlatformIO Export Problems

**Problem:** Generated PlatformIO platform doesn't work.

**Solutions:**
1. Check platform manifest format
2. Verify framework compatibility
3. Test with a simple project
4. Ensure proper directory structure

## GUI Issues

### Interface Not Responding

**Problem:** GUI interface freezes or doesn't respond.

**Solutions:**
1. Check system resources (RAM, CPU)
2. Close unnecessary applications
3. Restart the application
4. Check for graphics driver issues

### Rendering Problems

**Problem:** Graphics don't render correctly in GUI.

**Solutions:**
1. Update graphics drivers
2. Check for SDL2 library issues
3. Run with software rendering:
   ```bash
   pad-corebuilder gui --software-rendering
   ```

## Configuration Issues

### Invalid JSON Format

**Problem:** Configuration files cause parsing errors.

**Solutions:**
1. Validate JSON syntax using online validators
2. Check for trailing commas
3. Verify string quotes are properly closed
4. Use consistent formatting

### Missing Configuration Values

**Problem:** Default values not applied when config is incomplete.

**Solutions:**
1. Check documentation for required fields
2. Use the `--generate-config` command to create a template:
   ```bash
   pad-corebuilder generate-config --template my_mcu.json
   ```

## Compilation Issues

### Build Failures

**Problem:** Generated cores fail to compile.

**Solutions:**
1. Check toolchain installation
2. Verify compiler version compatibility
3. Check for missing include paths
4. Validate linker script syntax

### Linker Errors

**Problem:** Programs fail to link after compilation.

**Solutions:**
1. Verify memory region definitions
2. Check for undefined references
3. Validate startup code inclusion
4. Check stack/heap size settings

## Runtime Issues

### Generated Code Problems

**Problem:** Generated code doesn't behave as expected.

**Solutions:**
1. Compare with reference implementations
2. Check register initialization sequences
3. Verify clock configuration
4. Test with minimal example programs

### Performance Issues

**Problem:** Generated cores have poor performance.

**Solutions:**
1. Check compiler optimization settings
2. Verify interrupt handling efficiency
3. Check for unnecessary abstractions
4. Profile the generated code

## Debugging Techniques

### Enable Verbose Output

```bash
# Enable detailed logging
pad-corebuilder create --mcu my_mcu.json --verbose --log-level debug

# Log to file
pad-corebuilder create --mcu my_mcu.json --log-file debug.log
```

### Validate Configurations

```bash
# Validate MCU definition
pad-corebuilder validate --mcu my_mcu.json

# Validate board definition
pad-corebuilder validate --board my_board.json

# Validate template
pad-corebuilder validate --template my_template.json
```

### Generate Reports

```bash
# Generate detailed report
pad-corebuilder report --mcu my_mcu.json --output report.html

# Generate pin report
pad-corebuilder report --pins --board my_board.json
```

## Recovery Procedures

### Rollback Changes

If a generated core causes issues:

1. Backup the generated core directory
2. Regenerate with corrected configuration
3. Test incrementally with simple programs

### Factory Reset

To reset PAD-CoreBuilder to default state:

```bash
pad-corebuilder reset --all
```

This removes all custom configurations, templates, and generated cores.

## Performance Optimization

### Slow Generation Times

**Possible Causes:**
- Large MCU definitions
- Complex peripheral configurations
- System resource limitations

**Solutions:**
1. Simplify MCU definitions if possible
2. Increase system resources (RAM, faster storage)
3. Use SSD instead of HDD
4. Close other applications during generation

### High Memory Usage

**Symptoms:**
- System slowdown during generation
- Memory allocation errors

**Solutions:**
1. Check available RAM
2. Close unnecessary applications
3. Generate smaller cores incrementally
4. Monitor memory usage during generation

## Getting Help

### Diagnostic Information Collection

When requesting support, provide:

1. PAD-CoreBuilder version:
   ```bash
   pad-corebuilder --version
   ```

2. System information:
   ```bash
   uname -a  # Linux/macOS
   systeminfo  # Windows
   ```

3. Detailed log with `--verbose` flag
4. The exact command used and full error output
5. The configuration files involved

### Support Resources

- Check the [FAQ](./faq.md) for common questions
- Visit our [community forum](https://community.pad-service.ru/)
- Email technical support: [support@pad-service.ru](mailto:support@pad-service.ru)
- Submit an issue on our [GitHub repository](https://github.com/pad-service/pad-corebuilder/issues)

### Creating Bug Reports

When submitting bug reports, include:

- Steps to reproduce
- Expected vs. actual behavior
- System configuration
- Log files with verbose output
- Any relevant configuration files
- Screenshots if applicable

## Common Solutions Summary

| Problem | Command to Try | Additional Steps |
|---------|----------------|------------------|
| Invalid MCU definition | `pad-corebuilder validate --mcu file.json` | Check required fields |
| Missing templates | `pad-corebuilder list-templates` | Register missing templates |
| Export failures | `pad-corebuilder export --force ...` | Check permissions |
| GUI freezing | Restart application | Check system resources |
| Compilation errors | Check toolchain | Verify include paths |
| Performance issues | `--verbose` flag | Profile generated code |

## Prevention Tips

1. Always validate configurations before generating cores
2. Keep backups of working configurations
3. Test generated cores with simple programs first
4. Use version control for custom configurations
5. Regularly update PAD-CoreBuilder to latest version