#include "protocol.h"

#include "byte_order.h"
#include "crc16.h"

/*
 * 帧格式：SOF(1) + Type(1) + Sequence(2, BE) + PayloadLength(1) + Payload(N) + CRC16(2, BE)
 */
int protocol_encode(
    const ProtocolFrame *frame,
    uint8_t *output,
    size_t output_capacity,
    size_t *output_length
)
{
    size_t frame_length;
    size_t index;
    uint16_t crc;

    /* 先做基础参数校验，避免后续写入空指针或越界缓冲区。 */
    if ((frame == NULL) ||
        (output == NULL) ||
        (output_length == NULL)) {
        return PROTOCOL_ERROR;
    }

    /* 负载长度必须受协议上限约束。 */
    if (frame->payload_length > PROTOCOL_MAX_PAYLOAD_SIZE) {
        return PROTOCOL_PAYLOAD_TOO_LARGE;
    }

    /* 总长度 = 固定头部 + 负载。 */
    frame_length =
        PROTOCOL_FIXED_SIZE + frame->payload_length;

    /* 输出缓冲区至少要能容纳整帧。 */
    if (output_capacity < frame_length) {
        return PROTOCOL_BUFFER_TOO_SMALL;
    }

    /* 按协议顺序依次写入各字段。 */
    output[0] = PROTOCOL_SOF;
    output[1] = frame->type;

    write_u16_be(
        &output[2],
        frame->sequence
    );

    output[4] = frame->payload_length;

    for (index = 0U;
         index < frame->payload_length;
         index++) {
        output[5U + index] = frame->payload[index];
    }

    /* CRC 覆盖从 SOF 到 Payload 结束位置，不包含 CRC 自身。 */
    crc = crc16_modbus(
        output,
        5U + frame->payload_length
    );

    write_u16_be(
        &output[5U + frame->payload_length],
        crc
    );

    *output_length = frame_length;

    return PROTOCOL_OK;
}










/*
| SOF | TYPE | SEQ | LEN | PAYLOAD | CRC16 |
| 1B  | 1B   | 2B  | 1B  | N B     | 2B    |
*/
int protocol_decode(
    const uint8_t *input,
    size_t input_length,
    ProtocolFrame *frame
)
{
    ProtocolFrame decoded_frame = {0};
    uint8_t payload_length;
    size_t expected_length;
    size_t index;
    uint16_t received_crc;
    uint16_t calculated_crc;

    /* 先检查参数，避免空指针访问。 */
    if ((input == NULL) || (frame == NULL)) {
        return PROTOCOL_ERROR;
    }

    /* 至少要包含固定头部，才有可能是完整帧。 */
    if (input_length < PROTOCOL_FIXED_SIZE) {
        return PROTOCOL_INVALID_LENGTH;
    }

    /* 帧头必须匹配协议定义。 */
    if (input[0] != PROTOCOL_SOF) {
        return PROTOCOL_INVALID_SOF;
    }

    /* 先读取负载长度，再据此判断整帧长度。 */
    payload_length = input[4];

    /* 负载长度不能超过协议允许的最大值。 */
    if (payload_length > PROTOCOL_MAX_PAYLOAD_SIZE) {
        return PROTOCOL_PAYLOAD_TOO_LARGE;
    }

    expected_length =
        PROTOCOL_FIXED_SIZE + payload_length;

    /* 输入长度必须和帧格式完全一致。 */
    if (input_length != expected_length) {
        return PROTOCOL_INVALID_LENGTH;
    }

    /* 先取出报文中携带的 CRC，再重新计算整帧 CRC 做比对。 */
    received_crc = read_u16_be(
        &input[5U + payload_length]
    );

    calculated_crc = crc16_modbus(
        input,
        5U + payload_length
    );

    if (received_crc != calculated_crc) {
        return PROTOCOL_CRC_MISMATCH;
    }

    /* CRC 正确后，再解析各字段到临时结构体中。 */
    decoded_frame.type = input[1];

    decoded_frame.sequence = read_u16_be(
        &input[2]
    );

    decoded_frame.payload_length = payload_length;

    for (index = 0U;
         index < payload_length;
         index++) {
        decoded_frame.payload[index] =
            input[5U + index];
    }

    /* 解析成功后再一次性写回调用者，避免半解析状态外泄。 */
    *frame = decoded_frame;

    return PROTOCOL_OK;
}