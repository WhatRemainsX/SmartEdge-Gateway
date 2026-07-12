#include "byte_order.h"




//写入大端序
void write_u16_be(uint8_t *buffer, uint16_t value)
{
    buffer[0]=(uint8_t)(value >> 8); // 高字节
    buffer[1]=(uint8_t)(value); // 低字节
}

//读取大端序
uint16_t read_u16_be(const uint8_t *buffer)
{
    return ((uint16_t)buffer[0]<<8 | (uint16_t)buffer[1]);  
}