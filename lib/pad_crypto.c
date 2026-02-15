#include "../include/common_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple XOR cipher for demonstration purposes
// NOTE: This is not cryptographically secure and should not be used in production
int pad_xor_cipher(uint8_t* data, size_t length, const uint8_t* key, size_t key_length) {
    if (!data || !key || length == 0 || key_length == 0) {
        return -1;
    }
    
    for (size_t i = 0; i < length; i++) {
        data[i] ^= key[i % key_length];
    }
    
    return 0;
}

// Simple hash function (not cryptographically secure)
uint32_t pad_simple_hash(const uint8_t* data, size_t length) {
    if (!data || length == 0) {
        return 0;
    }
    
    uint32_t hash = 5381;
    for (size_t i = 0; i < length; i++) {
        hash = ((hash << 5) + hash) + data[i]; // hash * 33 + c
    }
    
    return hash;
}

// Key derivation function (simple version)
int pad_derive_key(const char* password, const uint8_t* salt, size_t salt_len, 
                   uint8_t* key, size_t key_len) {
    if (!password || !salt || !key || key_len == 0) {
        return -1;
    }
    
    // Initialize key with zeros
    memset(key, 0, key_len);
    
    // Simple key derivation using hash chaining
    uint32_t hash = pad_simple_hash((const uint8_t*)password, strlen(password));
    
    for (size_t i = 0; i < key_len; i++) {
        hash = pad_simple_hash((const uint8_t*)&hash, sizeof(hash));
        if (salt && i < salt_len) {
            hash ^= salt[i % salt_len];
        }
        key[i] = (uint8_t)(hash & 0xFF);
    }
    
    return 0;
}

// Simple signature verification (demonstration only)
int pad_verify_signature(const uint8_t* data, size_t data_len, 
                        const uint8_t* signature, size_t sig_len,
                        const uint8_t* public_key, size_t key_len) {
    // This is a simplified demonstration function
    // In a real implementation, you would use proper cryptographic algorithms
    
    if (!data || !signature || !public_key || data_len == 0 || sig_len == 0 || key_len == 0) {
        return 0; // Verification failed
    }
    
    // For demonstration, we'll use a simple hash comparison
    // This is NOT secure and should not be used in production
    if (sig_len < sizeof(uint32_t)) {
        return 0; // Signature too short
    }
    
    uint32_t calculated_hash = pad_simple_hash(data, data_len);
    uint32_t stored_hash = *(uint32_t*)signature;
    
    // Compare the hashes
    return (calculated_hash == stored_hash) ? 1 : 0;
}

// Generate a simple signature (demonstration only)
int pad_generate_signature(const uint8_t* data, size_t data_len, 
                          uint8_t* signature, size_t sig_len,
                          const uint8_t* private_key, size_t key_len) {
    if (!data || !signature || !private_key || data_len == 0 || sig_len < sizeof(uint32_t)) {
        return -1;
    }
    
    // Calculate hash of the data
    uint32_t hash = pad_simple_hash(data, data_len);
    
    // Store the hash in the signature
    memcpy(signature, &hash, sizeof(hash));
    
    return 0;
}

// Secure memory wipe
void pad_memwipe(void* ptr, size_t len) {
    if (!ptr || len == 0) return;
    
    volatile uint8_t* p = (volatile uint8_t*)ptr;
    for (size_t i = 0; i < len; i++) {
        p[i] = 0;
    }
}