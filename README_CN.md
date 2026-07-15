# RICE v2

RICE v2 是运行在 STM32H750VBTx 上的交互式 C 环境。项目将
[PicoC](picoc/) 解释器嵌入 FreeRTOS，并通过 USART1 和可选的 CH394Q UDP
链路提供交互、脚本执行和调试能力。

[English](README.md) | [移植指南](MIGRATION.md) | [许可证](LICENSE)

## 硬件与运行时

- MCU：STM32H750VBTx，Cortex-M7，最高 480 MHz
- 串口：USART1，PA9（TX）和 PA10（RX），115200 波特率、8 数据位、无校验、1 停止位（8N1）
- RTOS：FreeRTOS CMSIS-RTOS v2，内核版本 10.6.2
- 网络：CH394Q（SPI4），使用 UDP socket 0
- CH394Q 默认地址：`192.168.1.200:1000`
- UDP 默认对端：`192.168.1.100:1000`

默认网络参数定义在 `Core/Src/CH394Q_NET.c`。

## 完整串口使用流程

以下流程从干净的代码仓库开始，一直到执行和调试 C 脚本。命令区分大小写，且每条
命令都必须以终端配置的行结束符发送。

### 1. 编译与烧录

固件只能通过 Keil MDK 编译，项目不提供受支持的命令行构建方式。

1. 在 Keil MDK 中打开 `MDK-ARM/UART_DMA_H750.uvprojx`。
2. 按 **F7** 编译。
3. 通过 ST-Link 连接开发板并烧录生成的镜像。
4. 使用串口终端连接 USART1，设置为 **115200、8 数据位、无校验、1 停止位**。发送
   行结束符设为 LF 或 CRLF；若终端会导致键入字符显示两次，请关闭本地回显。

CubeMX 工程文件为 `UART_DMA_H750.ioc`。重新生成 CubeMX 代码可能覆盖
`Core/Src` 和 `Core/Inc` 中的 HAL 文件。

### 2. 激活 REPL

设备上电后先进入 UDP 桥接模式，而不是直接进入解释器：

```text
=== UDP Bridge Ready ===
```

通过 USART1 发送完整的一行 `:Rice`。当前通道随后输出 RICE 横幅和 `Rice> ` 提示符：

```text
:Rice
RICE <version> -- Runtime Interactive C Environment
Rice>
```

只有看到提示符后才能发送 C 代码。桥接模式下，普通串口行会转发到配置的 UDP 对端，
不会被当作 PicoC 输入。

### 3. 交互执行 C 代码

输入完整的语句或表达式后按 Enter。表达式会自动打印结果。若代码块尚未闭合，提示符
会变成 `     > `，直到花括号、方括号、圆括号、字符串和注释全部闭合。

```text
Rice> int x = 42;
Rice> x + 5
47
Rice> for (int i = 0; i < 3; i++) {
     >     printf("i=%d\n", i);
     > }
i=0
i=1
i=2
Rice>
```

REPL 中声明的变量会保留在 REPL 解释器实例中，直到发送 `:reset` 或重启开发板。
单条进入任务队列的 REPL 源码消息最多为 255 字节，因此单次提交应控制在此范围内。

### 4. 上传并运行完整脚本

多行程序应使用加载模式。`:load` 会清除上一次上传内容，返回 `:ok` 并将提示符改为
`load> `。逐行发送源码，最后单独发送一行 `:end`。源码保存在 8 KiB 缓冲区中，并在
独立的 PicoC 实例 `serial_load` 中运行。

```text
Rice> :load
:ok
load> #include <stdio.h>
load> int main(void)
load> {
load>     int total = 0;
load>     for (int i = 1; i <= 5; i++) {
load>         total += i;
load>     }
load>     printf("total=%d\n", total);
load>     return 0;
load> }
load> :end
total=15
:ok ready
Rice>
```

存在 `main()` 时会自动调用它。复制文件时应保留空行，因为调试器按原始上传行号报告
位置。`:load <bytes>` 仅用于大小预检查；数值大于 8191 时会返回 `:err buffer full`。
在发送 `:end` 前发送 `:abort` 可丢弃上传内容并回到 `Rice> `。

### 5. 设置断点并调试上传脚本

断点的文件名必须为 `serial_load`，行号从 1 开始。可以在 `:load` 前设置，也可以在脚本
暂停时设置。下列完整示例会在第 5 行的 `value` 自增语句处暂停：

```text
Rice> :bkpt serial_load 5
:ok bkpt
Rice> :load
:ok
load> #include <stdio.h>
load> int main(void)
load> {
load>     int value = 41;
load>     value = value + 1;
load>     printf("value=%d\n", value);
load>     return 0;
load> }
load> :end
:break serial_load 5 0
:vars
:var value 41
:ok vars
:eval value + 1
42
:set value 100
:ok set
:step
:step serial_load 6 0
:cont
value=100
:ok ready
Rice>
```

暂停期间，解释器直接消费下列命令。不要在此时发送普通 C 源码；应先使用 `:cont` 完成
脚本，或用 `:abort` 停止脚本。

| 命令 | 暂停时的作用 |
| --- | --- |
| `:cont` | 继续执行，直至下一个断点或程序结束。 |
| `:step` | 执行一条语句后再次暂停。 |
| `:eval <expression>` | 在当前作用域中求值。 |
| `:vars` | 逐行输出可见变量的 `:var ...` 记录，最后输出 `:ok vars`。 |
| `:set <name> <value>` | 修改可见变量。 |
| `:bkpt <file> <line>` | 添加断点。 |
| `:bkptclear <file> <line>` | 移除断点。 |
| `:abort` | 停止暂停中的脚本并返回 REPL。 |

一次上传执行结束后，为该上传配置的断点会被清除。

### 6. 中断、连通性检查与复位

以下是中断死循环的示例：

```text
Rice> while (1) { }
Rice> :ping
:pong
Rice> :abort
```

`:abort` 是协作式中断。PicoC 在循环体和阻塞式控制台输入处检查中断请求，因此普通的
`while`、`for` 和 `do` 循环无需复位开发板即可中断。长期不经过 PicoC 检查点的代码
不能保证立即被中断。`:ping` 由串口任务处理，脚本执行期间仍可响应。

`:reset` 会重新创建 REPL PicoC 实例、丢弃正在上传的内容并清除其中的断点。只有需要
完全复位 MCU 时才使用 `:RST`；设备会回到 UDP 桥接模式，之后需要再次发送 `:Rice`。

## UDP 流程与通道切换

启动后，串口输入和 UDP 数据会双向桥接。若要使 UDP 成为解释器通道，请向设备发送内容
为 `:Rice` 的 UDP 数据报。该发送方会收到 RICE 横幅、`Rice> ` 提示符和 `:ok rice`；
之后的 REPL、上传、调试及输出都通过 UDP 进行。

使用以下命令切换活动解释器通道。`:ok debug ...` 会发送到旧通道，新的提示符出现在
新通道。

```text
:debug udp
:debug serial
```

串口活跃时，除 `:debug udp` 外的 UDP 输入都会被忽略；UDP 活跃时，除 `:debug serial`
外的串口输入都会被忽略。若默认 IP 不适合当前网络，应先修改 CH394Q 地址和 UDP 对端。

## 命令速查

| 命令 | 作用 | 正常响应 |
| --- | --- | --- |
| `:Rice` | 离开桥接模式，激活当前通道的 REPL。 | RICE 横幅和 `Rice> `；UDP 还会发送 `:ok rice`。 |
| `:load [bytes]` | 开始新的脚本上传。 | `:ok`，随后是 `load> `。 |
| `:end` | 执行已累积的上传脚本。 | 程序输出，随后为 `:ok ready`。 |
| `:abort` | 取消上传或协作式中断运行中的代码。 | 取消上传时为 `:err load cancelled`。 |
| `:ping` | 检查连通性。 | `:pong`。 |
| `:reset` | 重建 REPL 解释器并清除状态。 | `:ok`。 |
| `:RST` | 通过 `HAL_NVIC_SystemReset()` 复位 STM32。 | `:ok`，随后是启动输出。 |
| `:bkpt <file> <line>` | 设置断点。 | `:ok bkpt`。 |
| `:bkptclear <file> <line>` | 清除断点。 | `:ok bkptclear`。 |
| `:debug serial` | 将 USART1 设为活动 I/O。 | 旧通道收到 `:ok debug serial`。 |
| `:debug udp` | 将 UDP 设为活动 I/O。 | 旧通道收到 `:ok debug udp`。 |

## 限制

- 目标没有文件系统，不支持读取主机文件的 `#include` 或文件 API；完整源码请通过
  `:load` 传输。
- 上传缓冲区为 8 KiB，任务消息最多携带 255 字节源码文本。
- FreeRTOS `heap_4` 配置为 72 KiB，PicoC 另有独立的 64 KiB 堆。
- 缓冲区、任务栈和网络参数均为静态配置；增加脚本复杂度前应评估资源使用情况。

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

- `serialTask`：高优先级，4 KiB 栈；读取串口输入并解析协议行。
- `picocTask`：普通优先级，32 KiB 栈；执行 PicoC 和调试器；启动时挂起，收到 `:Rice`
  后恢复运行。
- `udpTask`：高于普通优先级，8 KiB 栈；处理 CH394Q UDP 收发。

## 仓库结构

```text
Core/Src, Core/Inc/   HAL 胶水、FreeRTOS 任务、串口和 PicoC 应用
picoc/                PicoC 解释器核心及 STM32H7 平台适配
Drivers/              STM32 HAL 和 CMSIS 设备头文件
Middlewares/          FreeRTOS/CMSIS-RTOS 集成
MDK-ARM/              Keil 工程、启动代码和链接配置
MIGRATION.md          移植流程与文件依赖矩阵
```

代码按层次组织：`picoc/*.c` 是可复用的解释器核心；`picoc/platform/*` 包含平台绑定；
`Core/Src/*_app.c` 负责应用协议；CubeMX/HAL 文件负责芯片启动和驱动。

## 许可证

MIT，详见 [LICENSE](LICENSE)。
