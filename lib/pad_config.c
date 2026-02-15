#include "../include/common_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple configuration structure
typedef struct config_item {
    char name[64];
    char value[256];
    struct config_item* next;
} config_item;

static config_item* config_head = NULL;

// Initialize configuration system
int pad_config_init(void) {
    // Clean up any existing configuration
    pad_config_cleanup();
    return 0;
}

// Load configuration from a file
int pad_config_load(const char* filename) {
    if (!filename) return -1;
    
    FILE* file = fopen(filename, "r");
    if (!file) return -1;
    
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;
        
        // Skip empty lines and comments
        if (line[0] == '#' || line[0] == ';' || strlen(line) == 0) {
            continue;
        }
        
        // Parse key=value
        char* separator = strchr(line, '=');
        if (separator) {
            *separator = '\0';
            char* key = line;
            char* value = separator + 1;
            
            // Trim whitespace
            while (*key == ' ' || *key == '\t') key++;
            while (*value == ' ' || *value == '\t') value++;
            
            // Add to configuration
            pad_config_set_string(key, value);
        }
    }
    
    fclose(file);
    return 0;
}

// Save configuration to a file
int pad_config_save(const char* filename) {
    if (!filename) return -1;
    
    FILE* file = fopen(filename, "w");
    if (!file) return -1;
    
    config_item* current = config_head;
    while (current) {
        fprintf(file, "%s=%s\n", current->name, current->value);
        current = current->next;
    }
    
    fclose(file);
    return 0;
}

// Set a string value in configuration
int pad_config_set_string(const char* key, const char* value) {
    if (!key || !value) return -1;
    
    // Check if key already exists
    config_item* current = config_head;
    while (current) {
        if (strcmp(current->name, key) == 0) {
            pad_strncpy(current->value, value, sizeof(current->value));
            return 0;
        }
        current = current->next;
    }
    
    // Create new item
    config_item* new_item = (config_item*)pad_malloc(sizeof(config_item));
    if (!new_item) return -1;
    
    pad_strncpy(new_item->name, key, sizeof(new_item->name));
    pad_strncpy(new_item->value, value, sizeof(new_item->value));
    new_item->next = config_head;
    config_head = new_item;
    
    return 0;
}

// Get a string value from configuration
const char* pad_config_get_string(const char* key, const char* default_value) {
    if (!key) return default_value;
    
    config_item* current = config_head;
    while (current) {
        if (strcmp(current->name, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    
    return default_value;
}

// Set an integer value in configuration
int pad_config_set_int(const char* key, int value) {
    if (!key) return -1;
    
    char str_value[32];
    snprintf(str_value, sizeof(str_value), "%d", value);
    
    return pad_config_set_string(key, str_value);
}

// Get an integer value from configuration
int pad_config_get_int(const char* key, int default_value) {
    if (!key) return default_value;
    
    const char* str_value = pad_config_get_string(key, NULL);
    if (!str_value) return default_value;
    
    return atoi(str_value);
}

// Set a float value in configuration
int pad_config_set_float(const char* key, float value) {
    if (!key) return -1;
    
    char str_value[64];
    snprintf(str_value, sizeof(str_value), "%.6f", value);
    
    return pad_config_set_string(key, str_value);
}

// Get a float value from configuration
float pad_config_get_float(const char* key, float default_value) {
    if (!key) return default_value;
    
    const char* str_value = pad_config_get_string(key, NULL);
    if (!str_value) return default_value;
    
    return atof(str_value);
}

// Remove a key from configuration
int pad_config_remove(const char* key) {
    if (!key) return -1;
    
    config_item* current = config_head;
    config_item* prev = NULL;
    
    while (current) {
        if (strcmp(current->name, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                config_head = current->next;
            }
            pad_free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    
    return -1; // Key not found
}

// Clean up configuration system
int pad_config_cleanup(void) {
    while (config_head) {
        config_item* temp = config_head;
        config_head = config_head->next;
        pad_free(temp);
    }
    return 0;
}

// Enumerate all configuration keys
int pad_config_enumerate_keys(void (*callback)(const char* key, const char* value)) {
    if (!callback) return -1;
    
    config_item* current = config_head;
    while (current) {
        callback(current->name, current->value);
        current = current->next;
    }
    
    return 0;
}