# RICE v2

RICE v2 是运行在 STM32H750VBTx 上的交互式 C 环境。项目将
[PicoC](picoc/) 解释器嵌入 FreeRTOS，并通过 USART1 和可选的 CH394Q UDP
链路提供交互、脚本执行和调试能力。

[English](README.md) | [移植指南](MIGRATION.md) | [许可证](LICENSE)

## 硬件与运行时

- MCU：STM32H750VBTx，Cortex-M7，最高 480 MHz
- 串口：USART1，115200 波特率，8 数据位、无校验、1 停止位（115200 8N1）
- 串口引脚：PA9（TX）、PA10（RX）
- RTOS：FreeRTOS CMSIS-RTOS v2，内核版本 10.6.2
- 网络：CH394Q（SPI4），使用 UDP socket 0
- CH394Q 默认地址：`192.168.1.200:1000`
- UDP 默认对端：`192.168.1.100:1000`

默认 IP 和端口定义在 `Core/Src/CH394Q_NET.c`，如需更换网络请修改该文件。

## 启动行为

设备**不会**上电后直接进入 C REPL。HAL 和 FreeRTOS 初始化完成后，系统先
进入 UDP 桥接模式并输出：

```text
=== UDP Bridge Ready ===
```

桥接模式下，USART1 收到的完整行会发送给 UDP 对端，收到的 UDP 数据报会转发
到 USART1。此时 `picocTask` 已创建但处于挂起状态。

通过 USART1 发送完整的一行 `:Rice`，可激活串口 REPL；通过 UDP 数据报发送
`:Rice`，可激活 UDP REPL。激活后，当前通道会收到 `Rice> ` 提示符及所有解释器输出。

## 编译与烧录

项目没有受支持的命令行固件构建流程，请使用 Keil MDK：

1. 打开 `MDK-ARM/UART_DMA_H750.uvprojx`。
2. 按 **F7** 编译。
3. 使用 ST-Link 烧录。
4. 用串口终端连接 USART1，配置为 115200 8N1。

CubeMX 工程文件为 `UART_DMA_H750.ioc`。重新生成代码可能覆盖
`Core/Src` 和 `Core/Inc` 中的 HAL 文件，请注意保留应用层接口和修改。

## REPL 交互

发送 `:Rice` 后即可输入 C 语句或表达式。完整语句会进入 `picocTask` 执行，
未闭合的多行代码会使用续行提示符。

```text
Rice> int x = 42;
Rice> x + 5
47
Rice> for (int i = 0; i < 3; i++) {
     >   printf("i=%d\\n", i);
     > }
i=0
i=1
i=2
```

目标没有文件系统，需要主机文件的 `#include` 或文件 API 会返回错误。完整脚本
应使用上传协议发送。

## 上传脚本

`:load` 进入加载模式并显示 `load> `。源码会累积到 8 KiB 缓冲区，收到 `:end`
后执行。上传脚本在独立的 PicoC 实例中运行，调试器使用文件名 `serial_load`
报告行号。

```text
:load
#include <stdio.h>
int main(void) {
    printf("hello\\n");
    return 0;
}
:end
```

加载期间发送 `:abort` 会丢弃当前缓冲区。`:load <bytes>` 可选参数用于预检查，
大于 8 KiB 的值会在开始上传前被拒绝。

## 命令协议

命令按行解析并区分大小写，设备响应同样按行发送。

| 主机命令 | 作用 |
| --- | --- |
| `:Rice` | 离开桥接模式，激活当前通道的 REPL |
| `:load [bytes]` | 进入脚本上传模式 |
| `:end` | 执行已上传脚本 |
| `:abort` | 请求协作式中断脚本，或取消上传 |
| `:ping` | 立即返回心跳 `:pong` |
| `:reset` | 重新初始化 PicoC，清除变量和断点 |
| `:RST` | 通过 `HAL_NVIC_SystemReset()` 复位 STM32 |
| `:bkpt <file> <line>` | 设置断点 |
| `:bkptclear <file> <line>` | 清除断点 |
| `:debug serial` | 将调试 I/O 切换到 USART1 |
| `:debug udp` | 将调试 I/O 切换到 UDP |

常见响应包括 `:ok`、`:ok ready`、`:err <message>`、`:pong`、
`:break <file> <line> <column>`、`:step <file> <line> <column>`，以及位于
`:vars` 和 `:ok vars` 之间逐行发送的 `:var ...` 记录。

## 调试

可以在加载脚本前或之后设置断点。程序暂停时，调试器会直接消费以下命令，
不会经过普通源码消息队列：

```text
:bkpt serial_load 5
:load
...
:end
:break serial_load 5 0
:vars
:eval x + 1
:set x 100
:step
:cont
```

`:step` 执行一条语句，`:eval <expression>` 在暂停作用域求值，`:vars` 列出可见
变量，`:set <name> <value>` 修改暂停中的变量，`:cont` 继续执行直到下一个断点
或正常结束。

## 协作式中断

脚本运行期间，`:abort` 由高优先级 `serialTask` 处理。PicoC 循环检查点和阻塞式
控制台输入会检查 `AbortRequested`，随后解释器在 **picocTask 自身内部**通过
`setjmp/longjmp` 展开调用栈并返回提示符，不会跨任务执行 `longjmp`。

`:ping` 在脚本执行期间仍然响应。该机制是协作式的：如果代码长期不经过 PicoC
检查点，就不能保证立即中断。

## 运行时架构

```text
USART1 DMA/IDLE ISR
        |
        v
rx_ring[8192] --serialTask--> PicocApp_ProcessChars()
                                  |
                 +----------------+----------------+
                 |                                 |
          uartQuene (16)                    udpQuene (16)
                 |                                 |
             picocTask                         udpTask
```

- `serialTask`：高优先级，4 KiB 栈；读取 UART 并解析协议行。
- `picocTask`：普通优先级，32 KiB 栈；执行 PicoC 和调试器，启动时挂起。
- `udpTask`：高于普通优先级，8 KiB 栈；处理 CH394Q UDP 收发。
- FreeRTOS `heap_4`：配置堆 72 KiB；PicoC 另有独立的 64 KiB 堆。
- `TaskMsg` 数据区上限为 256 字节。单条 REPL 语句应控制在此范围内，解析器最多
  将 255 个源码字节复制到任务消息中。

## 仓库结构

```text
Core/Src, Core/Inc/   HAL 胶水、FreeRTOS 任务、串口和 PicoC 应用
picoc/                PicoC 解释器核心及 STM32H7 平台适配
Drivers/              STM32 HAL 和 CMSIS 设备头文件
Middlewares/          FreeRTOS/CMSIS-RTOS 集成
MDK-ARM/              Keil 工程、启动代码和链接配置
MIGRATION.md          移植流程与文件依赖矩阵
```

代码按以下层次组织：

1. `picoc/*.c`：可复用的解释器核心，移植硬件时不应修改。
2. `picoc/platform/*`：目标平台 I/O 和外设绑定。
3. `Core/Src/*_app.c`：REPL、协议解析、DMA 环形缓冲集成。
4. CubeMX/HAL 文件：芯片相关的启动、时钟、外设和中断实现。

## 已知限制

- 固件仅支持使用 Keil MDK 编译和烧录。
- 嵌入式目标没有基于文件系统的 `#include` 或文件执行能力。
- 缓冲区、任务栈和网络参数均为静态配置；增加脚本复杂度前应重新评估资源。
- 仓库包含 CubeMX 生成的 HAL 文件，重新生成时必须保持应用层接口不变。

## 许可证

MIT，详见 [LICENSE](LICENSE)。
