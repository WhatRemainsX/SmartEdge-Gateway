#include "bit_utils.h"
#include "byte_order.h"

#include <stdio.h>
#include <stdint.h>



typedef struct {
    uint8_t type;
    uint16_t sequence;
    uint32_t timestamp;
} TestFrame;

int main()
{
    uint8_t value = 0U; // Initial value

    value = bit_set(value, 3U);
    printf("Set bit 3: 0x%02X\n", value);

    value = bit_set(value, 0U);
    printf("Set bit 0: 0x%02X\n", value);

    printf("Read bit 3: %u\n", bit_read(value, 3U));

    value = bit_clear(value, 3U);
    printf("Clear bit 3: 0x%02X\n", value);

    value = bit_toggle(value, 1U);
    printf("Toggle bit 1: 0x%02X\n", value);

    uint8_t bytes[2] = {0U};
uint16_t original = 0x1234U;
uint16_t decoded;

write_u16_be(bytes, original);

printf(
    "Encoded: %02X %02X\n",
    bytes[0],
    bytes[1]
);

decoded = read_u16_be(bytes);

printf("Decoded: 0x%04X\n", decoded);

printf("sizeof(TestFrame) = %zu\n", sizeof(TestFrame));
    return 0;
}