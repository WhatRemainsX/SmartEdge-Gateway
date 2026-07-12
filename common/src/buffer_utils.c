#include "buffer_utils.h"

/**
 * @brief 反转一个字节缓冲区。
 *
 * @param buffer 缓冲区首地址。
 * @param length 缓冲区长度。
 *
 * @return 0 表示成功，-1 表示参数无效。
 */
void swap_bytes(uint8_t *left, uint8_t *right) {
    uint8_t temp = *left;
    *left = *right;
    *right = temp;
}

int buffer_reverse(uint8_t *buffer, size_t length)
{
    size_t left = 0;
    size_t right = length - 1;
    if (buffer == NULL || length == 0) {
        return -1; // 参数无效
    }

    while(left < right) {
        swap_bytes(&buffer[left], &buffer[right]);
        left++;
        right--;
    }
    return 0; // 成功
}



int buffer_find_max(const uint8_t *buffer, size_t length, uint8_t *max_value)
{
    if (buffer == NULL || length == 0 || max_value == NULL) {
        return -1; // 参数无效
    }

    *max_value = buffer[0];
    for (size_t i = 1; i < length; i++) {
        if (buffer[i] > *max_value) {
            *max_value = buffer[i];
        }
    }
    return 0; // 成功
}


int buffer_copy(uint8_t *destination, const uint8_t *source, size_t length)
{
    if (destination == NULL || source == NULL || length == 0) {
        return -1; // 参数无效
    }

    for (size_t i = 0; i < length; i++) {
        destination[i] = source[i];
    }
    return 0; // 成功
}



int buffer_sum(
    const uint8_t *buffer,
    size_t length,
    uint32_t *sum
)
{

    if (buffer == NULL || length == 0 || sum == NULL) {
        return -1; // 参数无效
    }

    *sum = 0;
    for (size_t i = 0; i < length; i++) {
        *sum += buffer[i];
    }
    return 0; // 成功
}

