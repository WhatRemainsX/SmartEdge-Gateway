#ifndef BUFFER_UTIL_H


#define BUFFER_UTIL_H


#include <stddef.h>
#include <stdint.h>


/**
 * @brief 反转一个字节缓冲区。
 *
 * @param buffer 缓冲区首地址。
 * @param length 缓冲区长度。
 *
 * @return 0 表示成功，-1 表示参数无效。
 */
int buffer_reverse(uint8_t *buffer, size_t length);


/**
 * @brief 查找字节缓冲区中的最大值。
 *
 * @param buffer 缓冲区首地址。
 * @param length 缓冲区长度。
 * @param max_value 用于返回最大值。
 *
 * @return 0 表示成功，-1 表示参数无效。
 */
int buffer_find_max(
    //const uint8_t *buffer 函数可以读取 buffer 指向的数据，但不能通过这个指针修改数据。
    const uint8_t *buffer,
    //size_t 是专门表示内存大小、数组长度和对象大小的无符号整数类型。
    size_t length,
    uint8_t *max_value
);


/**
 * @brief 复制一个字节缓冲区。
 *
 * @param destination 目标缓冲区。
 * @param source 源缓冲区。
 * @param length 复制长度。
 *
 * @return 0 表示成功，-1 表示参数无效。
 */
int buffer_copy(
    uint8_t *destination,
    const uint8_t *source,
    size_t length
);




/**
 * @brief 给缓冲区求和。
 *
 * @param buffer 缓冲区首地址。
 * @param length 缓冲区长度。
 * @param sum 用于返回求和结果。
 *
 * @return 0 表示成功，-1 表示参数无效。
 */
int buffer_sum(
    const uint8_t *buffer,
    size_t length,
    uint32_t *sum
);








#endif