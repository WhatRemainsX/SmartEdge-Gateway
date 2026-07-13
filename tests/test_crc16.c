/**
 * ============================================================================
 * CRC16 Modbus 校验函数测试套件
 * ============================================================================
 * 
 * 测试目的：验证 crc16_modbus() 函数的正确性
 * 
 * 测试覆盖：
 *   1. 已知数据测试 - 验证标准测试向量是否产生正确的 CRC 值
 *   2. 数据修改检测 - 验证 CRC 能否检测到数据的改变
 *   3. 空数据处理 - 验证对无数据输入的正确处理
 *   4. 无效指针处理 - 验证错误输入的安全处理
 * 
 * 标准测试向量：
 *   输入：字符串 "123456789"
 *   期望 CRC：0x4B37（Modbus CRC16 标准值）
 * ============================================================================
 */

#include "crc16.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/**
 * test_known_data - 测试已知数据的 CRC 计算
 * 
 * 测试内容：
 *   使用标准测试向量 "123456789" 计算 CRC
 *   验证结果是否等于 Modbus 标准值 0x4B37
 * 
 * 用途：
 *   确保 CRC 算法的基本功能正确
 *   验证与其他 CRC16 实现的兼容性
 * 
 * 返回值：0 表示通过，-1 表示失败
 */
static int test_known_data(void)
{
    // 标准测试数据：字符 "123456789"
    const uint8_t data[] = {
        '1', '2', '3', '4', '5',
        '6', '7', '8', '9'
    };

    // 计算这 9 个字符的 CRC16 校验值
    uint16_t crc = crc16_modbus(
        data,
        sizeof(data)
    );

    // 打印计算结果，格式：0x4B37（16 进制，4 位数字）
    printf(
        "CRC of 123456789: 0x%04" PRIX16 "\n",
        crc
    );

    // 验证 CRC 值是否正确
    // Modbus 标准规定 "123456789" 的 CRC16 应该是 0x4B37
    if (crc != 0x4B37U) {
        printf("[FAIL] known CRC value\n");
        return -1;
    }

    printf("[PASS] known CRC value\n");
    return 0;
}

/**
 * test_modified_data - 测试数据修改检测能力
 * 
 * 测试内容：
 *   1. 计算原始数据的 CRC
 *   2. 修改其中一个字节（0x02 → 0x82）
 *   3. 计算修改后的 CRC
 *   4. 验证两个 CRC 值是否不同
 * 
 * 用途：
 *   确保 CRC 能有效检测数据中的错误
 *   验证即使单个比特改变也能被发现
 * 
 * 返回值：0 表示检测成功，-1 表示失败
 */
static int test_modified_data(void)
{
    // 原始测试数据
    uint8_t original[] = {
        0xAAU,
        0x01U,
        0x02U,  // 这个字节稍后会被修改
        0x03U
    };

    // 修改后的数据（第三个字节从 0x02 改为 0x82）
    // 只改变了一个字节的第 7 位：0000 0010 → 1000 0010
    uint8_t modified[] = {
        0xAAU,
        0x01U,
        0x82U,  // 0x02 ^ 0x80 = 0x82（改变了第 7 位）
        0x03U
    };

    uint16_t original_crc;
    uint16_t modified_crc;

    // 计算原始数据的 CRC
    original_crc = crc16_modbus(
        original,
        sizeof(original)
    );

    // 计算修改后数据的 CRC
    modified_crc = crc16_modbus(
        modified,
        sizeof(modified)
    );

    // 打印两个 CRC 值进行对比
    printf(
        "Original CRC: 0x%04" PRIX16 "\n",
        original_crc
    );

    printf(
        "Modified CRC: 0x%04" PRIX16 "\n",
        modified_crc
    );

    // 验证两个 CRC 值是否不同
    // 如果相同说明 CRC 未能检测到数据的改变（测试失败）
    if (original_crc == modified_crc) {
        printf("[FAIL] modified data not detected\n");
        return -1;
    }

    printf("[PASS] modified data detected\n");
    return 0;
}

/**
 * test_empty_data - 测试空数据处理
 * 
 * 测试内容：
 *   调用 crc16_modbus(NULL, 0) - 传入空指针和 0 长度
 *   验证返回值是否等于初值 0xFFFF
 * 
 * 用途：
 *   验证对合法的空输入的处理
 *   当没有数据时，CRC 应返回初值（尚未被数据修改）
 * 
 * 返回值：0 表示通过，-1 表示失败
 */
static int test_empty_data(void)
{
    // 传入 NULL 指针和长度 0（合法的空数据）
    uint16_t crc = crc16_modbus(NULL, 0U);

    // 打印结果
    printf(
        "Empty data CRC: 0x%04" PRIX16 "\n",
        crc
    );

    // 验证返回值是否等于初值
    // 空数据应该返回 CRC 的初值 0xFFFF（未被任何数据修改）
    if (crc != 0xFFFFU) {
        printf("[FAIL] empty data CRC\n");
        return -1;
    }

    printf("[PASS] empty data CRC\n");
    return 0;
}

/**
 * test_invalid_pointer - 测试无效指针处理
 * 
 * 测试内容：
 *   调用 crc16_modbus(NULL, 4) - 传入空指针但长度 > 0
 *   验证函数是否返回 0（错误标志）
 * 
 * 用途：
 *   验证函数的防御性编程能力
 *   确保无效的输入组合被正确处理
 * 
 * 返回值：0 表示通过，-1 表示失败
 */
static int test_invalid_pointer(void)
{
    // 传入 NULL 指针但要求处理 4 个字节（非法的输入组合）
    // 这会触发 crc16_modbus 中的错误检查
    uint16_t crc = crc16_modbus(NULL, 4U);

    // 验证是否返回 0（函数定义的错误标志）
    if (crc != 0U) {
        printf("[FAIL] invalid pointer handling\n");
        return -1;
    }

    printf("[PASS] invalid pointer handling\n");
    return 0;
}

/**
 * main - 运行所有测试
 * 
 * 测试流程：
 *   1. 运行 4 个测试用例
 *   2. 记录失败的测试数量
 *   3. 打印汇总信息
 *   4. 返回测试结果（0 = 全部通过，1 = 有测试失败）
 * 
 * 返回值：0 表示全部通过，1 表示至少有一个测试失败
 */
int main(void)
{
    // 记录失败的测试数量
    unsigned int failed = 0U;

    // 运行测试 1：已知数据
    if (test_known_data() != 0) {
        failed++;
    }

    // 运行测试 2：数据修改检测
    if (test_modified_data() != 0) {
        failed++;
    }

    // 运行测试 3：空数据处理
    if (test_empty_data() != 0) {
        failed++;
    }

    // 运行测试 4：无效指针处理
    if (test_invalid_pointer() != 0) {
        failed++;
    }

    // 打印测试汇总
    printf(
        "\nCRC16 summary: %u failed\n",
        failed
    );

    // 返回测试结果：0 = 全部通过，1 = 有失败
    return failed == 0U ? 0 : 1;
}