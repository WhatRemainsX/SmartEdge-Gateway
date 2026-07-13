#include "ring_buffer.h"

#include <stdint.h>
#include <stdio.h>

static int test_basic_push_pop(void)
{
    uint8_t storage[5] = {0U};
    RingBuffer ring_buffer;
    uint8_t value;

    if (ring_buffer_init(
            &ring_buffer,
            storage,
            sizeof(storage)
        ) != RING_BUFFER_OK) {
        return -1;
    }

    ring_buffer_push(&ring_buffer, 10U);
    ring_buffer_push(&ring_buffer, 20U);
    ring_buffer_push(&ring_buffer, 30U);

    if (ring_buffer_size(&ring_buffer) != 3U) {
        return -1;
    }

    ring_buffer_pop(&ring_buffer, &value);

    if (value != 10U) {
        return -1;
    }

    ring_buffer_pop(&ring_buffer, &value);

    if (value != 20U) {
        return -1;
    }

    ring_buffer_pop(&ring_buffer, &value);

    if (value != 30U) {
        return -1;
    }

    return 0;
}

static int test_full_buffer(void)
{
    uint8_t storage[3] = {0U};
    RingBuffer ring_buffer;

    ring_buffer_init(
        &ring_buffer,
        storage,
        sizeof(storage)
    );

    if (ring_buffer_push(&ring_buffer, 1U)
        != RING_BUFFER_OK) {
        return -1;
    }

    if (ring_buffer_push(&ring_buffer, 2U)
        != RING_BUFFER_OK) {
        return -1;
    }

    if (ring_buffer_push(&ring_buffer, 3U)
        != RING_BUFFER_OK) {
        return -1;
    }

    if (!ring_buffer_is_full(&ring_buffer)) {
        return -1;
    }

    if (ring_buffer_push(&ring_buffer, 4U)
        != RING_BUFFER_FULL) {
        return -1;
    }

    return 0;
}
static int test_empty_buffer(void)
{
    uint8_t storage[3] = {0U};
    RingBuffer ring_buffer;
    uint8_t value = 0U;

    ring_buffer_init(
        &ring_buffer,
        storage,
        sizeof(storage)
    );

    if (!ring_buffer_is_empty(&ring_buffer)) {
        return -1;
    }

    if (ring_buffer_pop(&ring_buffer, &value)
        != RING_BUFFER_EMPTY) {
        return -1;
    }

    return 0;
}
static int test_wrap_around(void)
{
    uint8_t storage[4] = {0U};
    RingBuffer ring_buffer;
    uint8_t value;

    ring_buffer_init(
        &ring_buffer,
        storage,
        sizeof(storage)
    );

    ring_buffer_push(&ring_buffer, 1U);
    ring_buffer_push(&ring_buffer, 2U);
    ring_buffer_push(&ring_buffer, 3U);
    ring_buffer_push(&ring_buffer, 4U);

    ring_buffer_pop(&ring_buffer, &value);

    if (value != 1U) {
        return -1;
    }

    ring_buffer_pop(&ring_buffer, &value);

    if (value != 2U) {
        return -1;
    }

    /*
     * 此时数组前两个位置已经可重新使用。
     * head 会回绕到数组开头。
     */
    ring_buffer_push(&ring_buffer, 5U);
    ring_buffer_push(&ring_buffer, 6U);

    const uint8_t expected[] = {
        3U, 4U, 5U, 6U
    };

    for (size_t index = 0U;
         index < sizeof(expected);
         index++) {
        ring_buffer_pop(&ring_buffer, &value);

        if (value != expected[index]) {
            return -1;
        }
    }

    return 0;
}
static void run_test(
    const char *name,
    int (*test_function)(void),
    unsigned int *passed,
    unsigned int *failed
)
{
    if (test_function() == 0) {
        printf("[PASS] %s\n", name);
        (*passed)++;
    } else {
        printf("[FAIL] %s\n", name);
        (*failed)++;
    }
}

int main(void)
{
    unsigned int passed = 0U;
    unsigned int failed = 0U;

    run_test(
        "basic push and pop",
        test_basic_push_pop,
        &passed,
        &failed
    );

    run_test(
        "full buffer",
        test_full_buffer,
        &passed,
        &failed
    );

    run_test(
        "empty buffer",
        test_empty_buffer,
        &passed,
        &failed
    );

    run_test(
        "wrap around",
        test_wrap_around,
        &passed,
        &failed
    );

    printf(
        "\nRing buffer summary: %u passed, %u failed\n",
        passed,
        failed
    );

    return failed == 0U ? 0 : 1;
}