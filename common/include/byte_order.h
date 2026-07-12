#ifndef BYTE_ORDER_H


#define BYTE_ORDER_H



#include <stdint.h>

void write_u16_be(uint8_t *buffer, uint16_t value);
uint16_t read_u16_be(const uint8_t *buffer);







#endif // BYTE_ORDER_H