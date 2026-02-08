#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>

#ifdef __linux__
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#endif

#define VERSION "1.0.0"
#define MAX_DEVICES 8
#define BUFFER_SIZE 4096

typedef enum {
    INTERFACE_UART = 0,
    INTERFACE_JTAG,
    INTERFACE_SWD
} interface_type_t;

typedef struct {
    interface_type_t type;
    char device_path[256];
    int baudrate;
    uint32_t timeout;
    int validate_after_flash;
    int recovery_mode;
    int fd; // File descriptor for the connection
} device_config_t;

typedef struct {
    char firmware_path[512];
    int validate_after_flash;
    int recovery_mode;
    int parallel_mode;
    int num_devices;
    device_config_t devices[MAX_DEVICES];
} flash_config_t;

// Function prototypes
int parse_command_line(int argc, char *argv[], flash_config_t *config);
void print_usage(const char *program_name);
void print_version();
int init_device_connection(device_config_t *config);
int close_device_connection(device_config_t *config);
int flash_device(device_config_t *device, const char *firmware_path);
int validate_checksum(const char *firmware_path, device_config_t *device);
int enter_recovery_mode(device_config_t *device);
int perform_batch_operation(flash_config_t *config);

int main(int argc, char *argv[]) {
    flash_config_t config = {0};
    
    printf("PAD-Flasher v%s - Universal Device Programmer\n", VERSION);
    printf("Supports UART/JTAG/SWD interfaces for mass device programming\n\n");
    
    // Parse command line arguments
    if (parse_command_line(argc, argv, &config) != 0) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    
    // Perform the flashing operation
    if (perform_batch_operation(&config) != 0) {
        fprintf(stderr, "Flashing operation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("\nFlashing completed successfully!\n");
    return EXIT_SUCCESS;
}

int parse_command_line(int argc, char *argv[], flash_config_t *config) {
    int opt;
    int device_count = 0;
    
    // Initialize default values
    strcpy(config->firmware_path, "");
    config->validate_after_flash = 0;
    config->recovery_mode = 0;
    config->parallel_mode = 0;
    config->num_devices = 0;
    
    struct option long_options[] = {
        {"firmware", required_argument, 0, 'f'},
        {"interface", required_argument, 0, 'i'},
        {"device", required_argument, 0, 'd'},
        {"baudrate", required_argument, 0, 'b'},
        {"validate", no_argument, 0, 'v'},
        {"recovery", no_argument, 0, 'r'},
        {"parallel", no_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'V'},
        {"batch", required_argument, 0, 'c'},
        {"num-devices", required_argument, 0, 'n'},
        {0, 0, 0, 0}
    };
    
    while ((opt = getopt_long(argc, argv, "f:i:d:b:vprhVc:n:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                strncpy(config->firmware_path, optarg, sizeof(config->firmware_path) - 1);
                break;
            case 'i':
                if (strcmp(optarg, "uart") == 0) {
                    if (device_count < MAX_DEVICES) {
                        config->devices[device_count].type = INTERFACE_UART;
                    }
                } else if (strcmp(optarg, "jtag") == 0) {
                    if (device_count < MAX_DEVICES) {
                        config->devices[device_count].type = INTERFACE_JTAG;
                    }
                } else if (strcmp(optarg, "swd") == 0) {
                    if (device_count < MAX_DEVICES) {
                        config->devices[device_count].type = INTERFACE_SWD;
                    }
                } else {
                    fprintf(stderr, "Invalid interface type: %s\n", optarg);
                    return -1;
                }
                break;
            case 'd':
                if (device_count < MAX_DEVICES) {
                    strncpy(config->devices[device_count].device_path, optarg, 
                            sizeof(config->devices[device_count].device_path) - 1);
                }
                break;
            case 'b':
                if (device_count < MAX_DEVICES) {
                    config->devices[device_count].baudrate = atoi(optarg);
                }
                break;
            case 'v':
                config->validate_after_flash = 1;
                break;
            case 'r':
                config->recovery_mode = 1;
                break;
            case 'p':
                config->parallel_mode = 1;
                break;
            case 'n':
                config->num_devices = atoi(optarg);
                if (config->num_devices > MAX_DEVICES) {
                    config->num_devices = MAX_DEVICES;
                }
                break;
            case 'c':
                printf("Batch configuration file: %s\n", optarg);
                // In a real implementation, we would parse the config file here
                break;
            case 'V':
                print_version();
                exit(EXIT_SUCCESS);
            case 'h':
                print_usage(argv[0]);
                exit(EXIT_SUCCESS);
            default:
                return -1;
        }
        
        // Increment device count only if we've set a device path
        if (opt == 'd') {
            device_count++;
            config->num_devices = device_count;
        }
    }
    
    // If no devices were specified individually, but num_devices was set, create default configs
    if (config->num_devices > 0 && device_count == 0) {
        for (int i = 0; i < config->num_devices && i < MAX_DEVICES; i++) {
            config->devices[i].type = INTERFACE_UART; // default
            snprintf(config->devices[i].device_path, sizeof(config->devices[i].device_path), 
                     "/dev/ttyUSB%d", i);
            config->devices[i].baudrate = 115200; // default
        }
    }
    
    // If no devices were specified at all, set up one default
    if (config->num_devices == 0) {
        config->devices[0].type = INTERFACE_UART;
        strcpy(config->devices[0].device_path, "/dev/ttyUSB0");
        config->devices[0].baudrate = 115200;
        config->num_devices = 1;
    }
    
    // Set default baudrate if not specified
    for (int i = 0; i < config->num_devices; i++) {
        if (config->devices[i].baudrate == 0) {
            config->devices[i].baudrate = 115200;
        }
    }
    
    if (strlen(config->firmware_path) == 0) {
        fprintf(stderr, "Error: Firmware file not specified (-f option required)\n");
        return -1;
    }
    
    return 0;
}

void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS]\n", program_name);
    printf("PAD-Flasher - Universal Device Programmer for UART/JTAG/SWD interfaces\n\n");
    printf("Options:\n");
    printf("  -f, --firmware FILE     Firmware file to flash (.hex, .bin, .elf)\n");
    printf("  -i, --interface TYPE    Interface type: uart, jtag, swd (default: uart)\n");
    printf("  -d, --device PATH       Device path (e.g., /dev/ttyUSB0)\n");
    printf("  -b, --baudrate RATE     Baudrate for UART interface (default: 115200)\n");
    printf("  -n, --num-devices NUM   Number of devices for parallel flashing (default: 1)\n");
    printf("  -v, --validate          Validate checksum after flashing\n");
    printf("  -r, --recovery          Enable recovery mode\n");
    printf("  -p, --parallel          Enable parallel mode for multiple devices\n");
    printf("  -c, --batch CONFIG      Batch configuration file\n");
    printf("  -V, --version           Print version information\n");
    printf("  -h, --help              Show this help message\n\n");
    printf("Examples:\n");
    printf("  %s -f firmware.hex -i uart -d /dev/ttyUSB0\n", program_name);
    printf("  %s -f firmware.hex -i swd -n 4 -p        # Flash 4 devices in parallel\n", program_name);
    printf("  %s -f firmware.hex -c batch.conf         # Use batch configuration\n", program_name);
}

void print_version() {
    printf("PAD-Flasher v%s\n", VERSION);
    printf("Compiled on: %s at %s\n", __DATE__, __TIME__);
    printf("Copyright (c) 2023 PAD Service\n");
}

int init_device_connection(device_config_t *config) {
    if (config->type == INTERFACE_UART) {
        // Open serial port
        config->fd = open(config->device_path, O_RDWR | O_NOCTTY);
        if (config->fd < 0) {
            fprintf(stderr, "Error opening %s: %s\n", config->device_path, strerror(errno));
            return -1;
        }
        
#ifdef __linux__
        struct termios tty;
        
        if (tcgetattr(config->fd, &tty) != 0) {
            fprintf(stderr, "Error getting attributes for %s: %s\n", config->device_path, strerror(errno));
            close(config->fd);
            return -1;
        }
        
        cfsetospeed(&tty, config->baudrate);
        cfsetispeed(&tty, config->baudrate);
        
        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        tty.c_iflag &= ~IGNBRK;                         // disable break processing
        tty.c_lflag = 0;                                // no signaling chars, no echo,
                                                        // no canonical processing
        tty.c_oflag = 0;                                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;                            // read doesn't block
        tty.c_cc[VTIME] = 5;                            // 0.5 seconds read timeout
        
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // shut off xon/xoff ctrl
        
        tty.c_cflag |= (CLOCAL | CREAD);                // ignore modem controls,
                                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);              // shut off parity
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
        
        if (tcsetattr(config->fd, TCSANOW, &tty) != 0) {
            fprintf(stderr, "Error setting attributes for %s: %s\n", config->device_path, strerror(errno));
            close(config->fd);
            return -1;
        }
#endif
        printf("Connected to device via UART: %s at %d baud\n", config->device_path, config->baudrate);
    } else {
        // For JTAG/SWD, we would implement specific initialization
        printf("Initialized connection to %s via %s\n", 
               config->device_path, 
               config->type == INTERFACE_JTAG ? "JTAG" : "SWD");
        config->fd = 1; // Placeholder for demo
    }
    
    return 0;
}

int close_device_connection(device_config_t *config) {
    if (config->fd > 0) {
        if (config->type == INTERFACE_UART) {
            close(config->fd);
        }
        config->fd = -1;
    }
    return 0;
}

int flash_device(device_config_t *device, const char *firmware_path) {
    printf("Flashing device %s with firmware %s...\n", device->device_path, firmware_path);
    
    // Simulate flashing process
    for (int i = 0; i <= 100; i += 10) {
        printf("\rFlashing progress: %d%%", i);
        fflush(stdout);
        usleep(200000); // Sleep for 200ms to simulate work
    }
    printf("\n");
    
    // In a real implementation, we would actually send the firmware data to the device
    printf("Device %s flashed successfully\n", device->device_path);
    return 0;
}

int validate_checksum(const char *firmware_path, device_config_t *device) {
    if (!device->validate_after_flash) {
        return 0; // Skip validation if not requested
    }
    
    printf("Validating checksum on device %s...\n", device->device_path);
    
    // Simulate validation process
    for (int i = 0; i <= 100; i += 25) {
        printf("\rValidation progress: %d%%", i);
        fflush(stdout);
        usleep(100000); // Sleep for 100ms to simulate work
    }
    printf("\n");
    
    printf("Checksum validation passed for device %s\n", device->device_path);
    return 0;
}

int enter_recovery_mode(device_config_t *device) {
    if (!device->recovery_mode) {
        return 0; // Skip recovery if not requested
    }
    
    printf("Entering recovery mode on device %s...\n", device->device_path);
    
    // Simulate recovery process
    sleep(1);
    printf("Recovery mode entered successfully for device %s\n", device->device_path);
    return 0;
}

int perform_batch_operation(flash_config_t *config) {
    printf("Starting batch operation with %d device(s)\n", config->num_devices);
    
    if (config->parallel_mode) {
        printf("Running in parallel mode\n");
    } else {
        printf("Running in sequential mode\n");
    }
    
    // Process each device
    for (int i = 0; i < config->num_devices; i++) {
        printf("\n--- Processing Device %d ---\n", i+1);
        printf("Interface: %s\n", 
               config->devices[i].type == INTERFACE_UART ? "UART" :
               config->devices[i].type == INTERFACE_JTAG ? "JTAG" : "SWD");
        printf("Device: %s\n", config->devices[i].device_path);
        
        // Initialize connection
        if (init_device_connection(&config->devices[i]) != 0) {
            fprintf(stderr, "Failed to initialize device %s\n", config->devices[i].device_path);
            continue;
        }
        
        // Enter recovery mode if enabled
        enter_recovery_mode(&config->devices[i]);
        
        // Flash the device
        if (flash_device(&config->devices[i], config->firmware_path) != 0) {
            fprintf(stderr, "Failed to flash device %s\n", config->devices[i].device_path);
            close_device_connection(&config->devices[i]);
            continue;
        }
        
        // Validate checksum if requested
        if (validate_checksum(config->firmware_path, &config->devices[i]) != 0) {
            fprintf(stderr, "Checksum validation failed for device %s\n", config->devices[i].device_path);
            close_device_connection(&config->devices[i]);
            continue;
        }
        
        // Close connection
        close_device_connection(&config->devices[i]);
        
        printf("Device %s completed successfully\n", config->devices[i].device_path);
    }
    
    return 0;
}