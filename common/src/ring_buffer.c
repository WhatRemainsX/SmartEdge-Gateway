#include "ring_buffer.h"

int ring_buffer_init(
    RingBuffer *ring_buffer,
    uint8_t *storage,
    size_t capacity
)
{
    if ((ring_buffer == NULL) ||
        (storage == NULL) ||
        (capacity == 0U)) {
        return RING_BUFFER_ERROR;
    }

    ring_buffer->storage = storage;
    ring_buffer->capacity = capacity;
    ring_buffer->head = 0U;
    ring_buffer->tail = 0U;
    ring_buffer->count = 0U;

    return RING_BUFFER_OK;
}



int ring_buffer_is_empty(
    const RingBuffer *ring_buffer
)
{
    if (ring_buffer == NULL) {
        return 1;
    }

    return ring_buffer->count == 0U;
}



int ring_buffer_is_full(
    const RingBuffer *ring_buffer
)
{
    if (ring_buffer == NULL) {
        return 0;
    }

    return ring_buffer->count == ring_buffer->capacity;
}






size_t ring_buffer_size(
    const RingBuffer *ring_buffer
)
{
    if (ring_buffer == NULL) {
        return 0U;
    }

    return ring_buffer->count;
}



int ring_buffer_push(
    RingBuffer *ring_buffer,
    uint8_t value
)
{
    if (ring_buffer == NULL) {
        return RING_BUFFER_ERROR;
    }

    if (ring_buffer_is_full(ring_buffer)) {
        return RING_BUFFER_FULL;
    }

    /* TODO 1：把 value 写入 head 所在位置 */
    ring_buffer->storage[ring_buffer->head] = value;
    /* TODO 2：让 head 向前移动并在末尾回绕 */
    ring_buffer->head = (ring_buffer->head + 1U) % ring_buffer->capacity;
    /* TODO 3：count 加一 */
    ring_buffer->count++;

    return RING_BUFFER_OK;
}





int ring_buffer_pop(
    RingBuffer *ring_buffer,
    uint8_t *value
)
{
    if ((ring_buffer == NULL) || (value == NULL)) {
        return RING_BUFFER_ERROR;
    }

    if (ring_buffer_is_empty(ring_buffer)) {
        return RING_BUFFER_EMPTY;
    }

    /* TODO 1：读取 tail 所在位置的数据 */
    *value = ring_buffer->storage[ring_buffer->tail];
    /* TODO 2：让 tail 向前移动并回绕 */
    ring_buffer->tail = (ring_buffer->tail + 1U) % ring_buffer->capacity;
    /* TODO 3：count 减一 */
    ring_buffer->count--;

    return RING_BUFFER_OK;
}



int ring_buffer_peek(
    const RingBuffer *ring_buffer,
    uint8_t *value
)
{
    if ((ring_buffer == NULL) || (value == NULL)) {
        return RING_BUFFER_ERROR;
    }

    if (ring_buffer_is_empty(ring_buffer)) {
        return RING_BUFFER_EMPTY;
    }

    *value = ring_buffer->storage[ring_buffer->tail];

    return RING_BUFFER_OK;
}



void ring_buffer_clear(
    RingBuffer *ring_buffer
)
{
    if (ring_buffer == NULL) {
        return;
    }

    ring_buffer->head = 0U;
    ring_buffer->tail = 0U;
    ring_buffer->count = 0U;
}