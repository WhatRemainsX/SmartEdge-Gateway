#ifndef CRC16_H
#define CRC16_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief 计算 CRC-16/MODBUS。
 *
 * @param data 输入数据。
 * @param length 数据长度。
 *
 * @return CRC16 计算结果。
 */
uint16_t crc16_modbus(
    const uint8_t *data,
    size_t length
);

#endif