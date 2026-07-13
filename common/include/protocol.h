#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stddef.h>
#include <stdint.h>

#define PROTOCOL_SOF              0xAAU
#define PROTOCOL_MAX_PAYLOAD_SIZE 64U
#define PROTOCOL_FIXED_SIZE       7U

#define PROTOCOL_OK                0
#define PROTOCOL_ERROR            -1
#define PROTOCOL_BUFFER_TOO_SMALL -2
#define PROTOCOL_PAYLOAD_TOO_LARGE -3

#define PROTOCOL_INVALID_SOF       -4
#define PROTOCOL_INVALID_LENGTH    -5
#define PROTOCOL_CRC_MISMATCH      -6


typedef struct {
    uint8_t type;
    uint16_t sequence;
    uint8_t payload_length;
    uint8_t payload[PROTOCOL_MAX_PAYLOAD_SIZE];
} ProtocolFrame;

/*
| SOF | TYPE | SEQ | LEN | PAYLOAD | CRC16 |
| 1B  | 1B   | 2B  | 1B  | N B     | 2B    |
*/

int protocol_encode(
    const ProtocolFrame *frame,
    uint8_t *output,
    size_t output_capacity,
    size_t *output_length
);


int protocol_decode(
    const uint8_t *input,
    size_t input_length,
    ProtocolFrame *frame
);





#endif