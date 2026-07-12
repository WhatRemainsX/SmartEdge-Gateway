#include "bit_utils.h"



// Function prototypes for bit manipulation utilities
uint8_t bit_set(uint8_t value, uint8_t bit)
{
    if (bit >= 8) {
        return 0; // Invalid bit position
    }
    return value | (1 << bit);
    
}
uint8_t bit_clear(uint8_t value, uint8_t bit)
{
    if (bit >= 8) {
        return 0; // Invalid bit position
    }
    return value & ~(1 << bit);    
}
uint8_t bit_toggle(uint8_t value, uint8_t bit)
{
    if (bit >= 8) {
        return 0; // Invalid bit position
    }
    return value ^ (1 << bit);
}
uint8_t bit_read(uint8_t value, uint8_t bit)
{
    if (bit >= 8) {
        return 0; // Invalid bit position
    }
    return (value >> bit) & 1;
}