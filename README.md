# SmartEdge-Gateway

基于 STM32、FreeRTOS 与 Linux 的嵌入式数据采集网关。

## 项目目标

实现 STM32 数据采集、可靠通信、Linux 串口守护进程和 TCP 数据服务。

## 当前进度

- [x] 创建项目仓库
- [ ] CRC16 模块
- [ ] 环形缓冲区
- [ ] 协议帧编码与解析
- [ ] STM32 UART 数据发送
- [ ] Linux 串口接收

## 项目结构

- `common/`：STM32 和 Linux 共用的纯 C 模块
- `tests/`：公共模块测试代码
- `mcu_firmware/`：STM32 固件
- `linux_daemon/`：Linux 守护进程
- `docs/`：协议与调试文档
