#include "protocol.h"

#include <stdint.h>
#include <stdio.h>

static void print_bytes(
    const uint8_t *data,
    size_t length
)
{
    size_t index;

    for (index = 0U; index < length; index++) {
        printf("%02X ", data[index]);
    }

    printf("\n");
}

static int test_encode_normal_frame(void)
{
    ProtocolFrame frame = {0};
    uint8_t output[128] = {0U};
    size_t output_length = 0U;
    int result;

    frame.type = 0x01U;
    frame.sequence = 0x1234U;
    frame.payload_length = 2U;
    frame.payload[0] = 0x09U;
    frame.payload[1] = 0xC4U;

    result = protocol_encode(
        &frame,
        output,
        sizeof(output),
        &output_length
    );

    if (result != PROTOCOL_OK) {
        return -1;
    }

    printf("Encoded frame: ");
    print_bytes(output, output_length);

    if (output_length != 9U) {
        return -1;
    }

    if (output[0] != PROTOCOL_SOF) {
        return -1;
    }

    if (output[1] != 0x01U) {
        return -1;
    }

    if ((output[2] != 0x12U) ||
        (output[3] != 0x34U)) {
        return -1;
    }

    if (output[4] != 2U) {
        return -1;
    }

    if ((output[5] != 0x09U) ||
        (output[6] != 0xC4U)) {
        return -1;
    }

    return 0;
}

static int test_output_buffer_too_small(void)
{
    ProtocolFrame frame = {0};
    uint8_t output[4] = {0U};
    size_t output_length = 0U;

    frame.type = 1U;
    frame.sequence = 1U;
    frame.payload_length = 2U;

    if (protocol_encode(
            &frame,
            output,
            sizeof(output),
            &output_length
        ) != PROTOCOL_BUFFER_TOO_SMALL) {
        return -1;
    }

    return 0;
}

static int test_invalid_parameters(void)
{
    ProtocolFrame frame = {0};
    uint8_t output[32] = {0U};
    size_t output_length = 0U;

    if (protocol_encode(
            NULL,
            output,
            sizeof(output),
            &output_length
        ) != PROTOCOL_ERROR) {
        return -1;
    }

    if (protocol_encode(
            &frame,
            NULL,
            sizeof(output),
            &output_length
        ) != PROTOCOL_ERROR) {
        return -1;
    }

    if (protocol_encode(
            &frame,
            output,
            sizeof(output),
            NULL
        ) != PROTOCOL_ERROR) {
        return -1;
    }

    return 0;
}


static int test_encode_decode_round_trip(void)
{
    ProtocolFrame original = {0};
    ProtocolFrame decoded = {0};
    uint8_t output[128] = {0U};
    size_t output_length = 0U;

    original.type = 0x01U;
    original.sequence = 0x1234U;
    original.payload_length = 2U;
    original.payload[0] = 0x09U;
    original.payload[1] = 0xC4U;

    if (protocol_encode(
            &original,
            output,
            sizeof(output),
            &output_length
        ) != PROTOCOL_OK) {
        return -1;
    }

    if (protocol_decode(
            output,
            output_length,
            &decoded
        ) != PROTOCOL_OK) {
        return -1;
    }

    if (decoded.type != original.type) {
        return -1;
    }

    if (decoded.sequence != original.sequence) {
        return -1;
    }

    if (decoded.payload_length
        != original.payload_length) {
        return -1;
    }

    if ((decoded.payload[0]
            != original.payload[0]) ||
        (decoded.payload[1]
            != original.payload[1])) {
        return -1;
    }

    printf(
        "Decoded frame: type=%u, sequence=0x%04X, "
        "length=%u, payload=%02X %02X\n",
        decoded.type,
        decoded.sequence,
        decoded.payload_length,
        decoded.payload[0],
        decoded.payload[1]
    );

    return 0;
}



static int test_crc_error(void)
{
    ProtocolFrame original = {0};
    ProtocolFrame decoded = {0};
    uint8_t output[128] = {0U};
    size_t output_length = 0U;

    original.type = 0x01U;
    original.sequence = 1U;
    original.payload_length = 2U;
    original.payload[0] = 0x09U;
    original.payload[1] = 0xC4U;

    if (protocol_encode(
            &original,
            output,
            sizeof(output),
            &output_length
        ) != PROTOCOL_OK) {
        return -1;
    }

    /*
     * 模拟UART传输过程中一个字节发生错误。
     */
    output[5] ^= 0x01U;

    if (protocol_decode(
            output,
            output_length,
            &decoded
        ) != PROTOCOL_CRC_MISMATCH) {
        return -1;
    }

    return 0;
}



static int test_invalid_sof(void)
{
    ProtocolFrame original = {0};
    ProtocolFrame decoded = {0};
    uint8_t output[128] = {0U};
    size_t output_length = 0U;

    original.type = 1U;
    original.sequence = 1U;
    original.payload_length = 1U;
    original.payload[0] = 0x55U;

    if (protocol_encode(
            &original,
            output,
            sizeof(output),
            &output_length
        ) != PROTOCOL_OK) {
        return -1;
    }

    output[0] = 0xBBU;

    if (protocol_decode(
            output,
            output_length,
            &decoded
        ) != PROTOCOL_INVALID_SOF) {
        return -1;
    }

    return 0;
}


static int test_truncated_frame(void)
{
    ProtocolFrame original = {0};
    ProtocolFrame decoded = {0};
    uint8_t output[128] = {0U};
    size_t output_length = 0U;

    original.type = 1U;
    original.sequence = 1U;
    original.payload_length = 2U;
    original.payload[0] = 0x11U;
    original.payload[1] = 0x22U;

    if (protocol_encode(
            &original,
            output,
            sizeof(output),
            &output_length
        ) != PROTOCOL_OK) {
        return -1;
    }

    /*
     * 模拟最后一个字节没有收到。
     */
    if (protocol_decode(
            output,
            output_length - 1U,
            &decoded
        ) != PROTOCOL_INVALID_LENGTH) {
        return -1;
    }

    return 0;
}


int main(void)
{
    unsigned int passed = 0U;
    unsigned int failed = 0U;

    if (test_encode_normal_frame() == 0) {
        printf("[PASS] encode normal frame\n");
        passed++;
    } else {
        printf("[FAIL] encode normal frame\n");
        failed++;
    }

    if (test_output_buffer_too_small() == 0) {
        printf("[PASS] output buffer too small\n");
        passed++;
    } else {
        printf("[FAIL] output buffer too small\n");
        failed++;
    }

    if (test_invalid_parameters() == 0) {
        printf("[PASS] invalid parameters\n");
        passed++;
    } else {
        printf("[FAIL] invalid parameters\n");
        failed++;
    }



    if (test_encode_decode_round_trip() == 0) {
    printf("[PASS] encode and decode round trip\n");
    passed++;
} else {
    printf("[FAIL] encode and decode round trip\n");
    failed++;
}

if (test_crc_error() == 0) {
    printf("[PASS] CRC error detected\n");
    passed++;
} else {
    printf("[FAIL] CRC error detected\n");
    failed++;
}

if (test_invalid_sof() == 0) {
    printf("[PASS] invalid SOF detected\n");
    passed++;
} else {
    printf("[FAIL] invalid SOF detected\n");
    failed++;
}

if (test_truncated_frame() == 0) {
    printf("[PASS] truncated frame detected\n");
    passed++;
} else {
    printf("[FAIL] truncated frame detected\n");
    failed++;
}
    printf(
        "\nProtocol encode summary: %u passed, %u failed\n",
        passed,
        failed
    );
    return failed == 0U ? 0 : 1;
}