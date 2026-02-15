#ifndef PAD_INTERFACES_H
#define PAD_INTERFACES_H

#include "common_types.h"

// Common interface for all PAD tools
typedef struct {
    int (*init)(void* config);
    int (*execute)(void* params);
    int (*cleanup)(void);
    int (*get_status)(char* buffer, int size);
} pad_interface_t;

// Flasher interface
typedef struct {
    int (*connect_device)(const char* port);
    int (*flash_firmware)(const char* firmware_path);
    int (*verify_checksum)(void);
    int (*disconnect_device)(void);
} flasher_interface_t;

// Debugger interface
typedef struct {
    int (*attach_to_target)(uint32_t target_id);
    int (*read_memory)(uint32_t addr, uint8_t* buffer, uint32_t len);
    int (*write_memory)(uint32_t addr, uint8_t* buffer, uint32_t len);
    int (*continue_execution)(void);
    int (*halt_execution)(void);
} debugger_interface_t;

// Health monitoring interface
typedef struct {
    int (*read_temperature)(float* temp);
    int (*read_voltage)(float* voltage);
    int (*read_clock_stability)(float* stability);
    int (*set_thresholds)(float temp_max, float voltage_min, float voltage_max);
} health_monitor_interface_t;

#endif // PAD_INTERFACES_H