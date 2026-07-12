#include "buffer_utils.h"



#include <stdio.h>
#include <stdint.h>
static unsigned int call_count = 0;
static void increment_call_count(void);
int main()
{

    uint8_t buffer[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(buffer) / sizeof(buffer[0]);

    printf("Original buffer: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    // Reverse the buffer
    if (buffer_reverse(buffer, length) == 0) {
        printf("Reversed buffer: ");
        for (size_t i = 0; i < length; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    } else {
        printf("Error reversing buffer.\n");
    }

    // Find the maximum value in the buffer
    uint8_t max_value;
    if (buffer_find_max(buffer, length, &max_value) == 0) {
        printf("Maximum value in buffer: %d\n", max_value);
    } else {
        printf("Error finding maximum value.\n");
    }

    // Copy the buffer to a new destination
    uint8_t destination[5];
    if (buffer_copy(destination, buffer, length) == 0) {
        printf("Copied buffer: ");
        for (size_t i = 0; i < length; i++) {
            printf("%d ", destination[i]);
        }
        printf("\n");
    } else {
        printf("Error copying buffer.\n");
    }

    uint8_t sum_data[] = {10, 20, 30, 40, 50};
    uint32_t sum_result=0;
    if (buffer_sum(sum_data, sizeof(sum_data)/sizeof(sum_data[0]), &sum_result) == 0) {
        printf("Sum of buffer: %d\n", sum_result);
    } else {
        printf("Error calculating sum.\n");
    }

    increment_call_count();
    increment_call_count();
    increment_call_count();



    return 0;
    
}
static void increment_call_count(void) {
    call_count++;
    printf("Function called %u times\n", call_count);
}