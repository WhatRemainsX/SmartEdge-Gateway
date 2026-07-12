#ifndef BIT_UTILS_H
#define BIT_UTILS_H


#include <stddef.h>
#include <stdint.h>

// Function prototypes for bit manipulation utilities
uint8_t bit_set(uint8_t value, uint8_t bit);
uint8_t bit_clear(uint8_t value, uint8_t bit);
uint8_t bit_toggle(uint8_t value, uint8_t bit);
uint8_t bit_read(uint8_t value, uint8_t bit);
    
#endif // BIT_UTILS_H
