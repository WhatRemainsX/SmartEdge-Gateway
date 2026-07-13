#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stddef.h>
#include <stdint.h>

#define RING_BUFFER_OK           0
#define RING_BUFFER_ERROR       -1
#define RING_BUFFER_FULL        -2
#define RING_BUFFER_EMPTY       -3

typedef struct {
    uint8_t *storage;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
} RingBuffer;

int ring_buffer_init(
    RingBuffer *ring_buffer,
    uint8_t *storage,
    size_t capacity
);

int ring_buffer_push(
    RingBuffer *ring_buffer,
    uint8_t value
);

int ring_buffer_pop(
    RingBuffer *ring_buffer,
    uint8_t *value
);

int ring_buffer_peek(
    const RingBuffer *ring_buffer,
    uint8_t *value
);

size_t ring_buffer_size(
    const RingBuffer *ring_buffer
);

int ring_buffer_is_empty(
    const RingBuffer *ring_buffer
);

int ring_buffer_is_full(
    const RingBuffer *ring_buffer
);

void ring_buffer_clear(
    RingBuffer *ring_buffer
);

#endif