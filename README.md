# RICE v2

RICE v2 is an interactive C environment for the STM32H750VBTx. It embeds the
[PicoC](picoc/) interpreter in a FreeRTOS application and exposes it through
USART1 and an optional CH394Q UDP link.

[中文文档](README_CN.md) | [移植指南](MIGRATION.md) | [许可证](LICENSE)

## Current Hardware

- MCU: STM32H750VBTx, Cortex-M7, up to 480 MHz
- UART: USART1, 115200 baud, 8 data bits, no parity, 1 stop bit (8N1)
- UART pins: PA9 (TX), PA10 (RX)
- RTOS: FreeRTOS CMSIS-RTOS v2, kernel 10.6.2
- Network: CH394Q over SPI4, UDP socket 0
- Default CH394Q address: `192.168.1.200:1000`
- Default UDP peer: `192.168.1.100:1000`

The default IP and port values are defined in `Core/Src/CH394Q_NET.c`; change
them there for a different network.

## Boot Behavior

The board does **not** boot directly into the C REPL. After HAL and FreeRTOS
initialization it starts in UDP bridge mode:

```text
=== UDP Bridge Ready ===
```

In bridge mode, complete lines received from USART1 are sent to the UDP peer,
and UDP datagrams are forwarded to USART1. The PicoC task is created suspended.

Send the exact line `:Rice` over USART1 to activate the serial REPL. Send
`:Rice` in a UDP datagram to activate the UDP REPL. The active channel then
receives the prompt `Rice> ` and all interpreter output.

## Build and Flash

There is no supported command-line firmware build. Use Keil MDK:

1. Open `MDK-ARM/UART_DMA_H750.uvprojx`.
2. Build with **F7**.
3. Flash with an ST-Link.
4. Open a terminal on USART1 at 115200 8N1.

The CubeMX source is `UART_DMA_H750.ioc`. Regenerating it can overwrite HAL
files in `Core/Src` and `Core/Inc`; keep application-layer changes separate.

## REPL

After sending `:Rice`, enter C statements or expressions. A complete statement
is queued to `picocTask`; incomplete blocks use the continuation prompt.

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

The target has no filesystem. `#include` and file APIs that require a host
file return an error. Use the upload protocol for complete scripts.

## Uploading a Script

`:load` enters load mode and shows `load> `. Source is accumulated in an 8 KiB
buffer and executed after `:end`. The uploaded program is parsed in a separate
PicoC instance named `serial_load` for debugger file/line reporting.

```text
:load
#include <stdio.h>
int main(void) {
    printf("hello\\n");
    return 0;
}
:end
```

Use `:abort` while loading to discard the buffer. `:load <bytes>` is accepted
as an optional size hint; values larger than the 8 KiB load buffer are rejected
before upload starts.

## Command Protocol

Commands are line-oriented and case-sensitive. Responses are also line-based.

| Host command | Meaning |
| --- | --- |
| `:Rice` | Leave bridge mode and activate the current channel's REPL |
| `:load [bytes]` | Enter script upload mode |
| `:end` | Execute the uploaded script |
| `:abort` | Request cooperative script abort, or cancel an upload |
| `:ping` | Immediate heartbeat (`:pong`) |
| `:reset` | Reinitialize PicoC state and clear breakpoints |
| `:RST` | Reset the STM32 through `HAL_NVIC_SystemReset()` |
| `:bkpt <file> <line>` | Set a breakpoint |
| `:bkptclear <file> <line>` | Clear a breakpoint |
| `:debug serial` | Route debugger I/O to USART1 |
| `:debug udp` | Route debugger I/O to UDP |

Typical responses are `:ok`, `:ok ready`, `:err <message>`, `:pong`,
`:break <file> <line> <column>`, `:step <file> <line> <column>`, and streamed
`:var ...` records bracketed by `:ok vars`.

## Debugging

Set breakpoints before or after loading a script. While execution is paused,
the debugger consumes these commands directly (they do not go through the
normal source queue):

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

`:step` advances one statement, `:eval <expression>` evaluates in the paused
scope, `:vars` lists visible variables, and `:set <name> <value>` changes a
paused variable. `:cont` resumes execution until the next breakpoint or normal
completion.

## Cooperative Abort

`:abort` is handled by the high-priority serial task while `picocTask` runs.
PicoC loop checkpoints and blocking console input check `AbortRequested`; the
interpreter then unwinds with `setjmp/longjmp` **inside picocTask** and returns
to the prompt. No cross-task `longjmp` is used.

`:ping` remains responsive during script execution. Abort responsiveness is
cooperative: code that never reaches a PicoC checkpoint cannot be interrupted.

## Runtime Architecture

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

- `serialTask`: high priority, 4 KiB stack; drains UART input and parses lines.
- `picocTask`: normal priority, 32 KiB stack; runs PicoC and the debugger; starts suspended.
- `udpTask`: above-normal priority, 8 KiB stack; services CH394Q UDP I/O.
- FreeRTOS `heap_4`: 72 KiB configured heap; PicoC has a separate 64 KiB heap.
- `TaskMsg` payloads are capped at 256 bytes. Keep individual REPL statements
  within that payload; the parser copies at most 255 source bytes into a task
  message.

## Repository Map

```text
Core/Src, Core/Inc/   HAL glue, FreeRTOS tasks, serial and PicoC application
picoc/                PicoC interpreter core and STM32H7 platform bindings
Drivers/              STM32 HAL and CMSIS device headers
Middlewares/          FreeRTOS/CMSIS-RTOS integration
MDK-ARM/              Keil project, startup code, linker settings
MIGRATION.md          Porting workflow and file dependency matrix
```

The codebase is intentionally layered:

1. `picoc/*.c`: reusable interpreter core; do not change for a hardware port.
2. `picoc/platform/*`: target I/O and peripheral bindings.
3. `Core/Src/*_app.c`: REPL, protocol parser, DMA ring-buffer integration.
4. CubeMX/HAL files: chip-specific startup, clocks, peripherals, and IRQs.

## Known Constraints

- Firmware is built and flashed with Keil MDK only.
- The embedded target has no filesystem-backed `#include` or file execution.
- Buffer sizes, task stacks, and network defaults are static configuration;
  profile them before increasing script complexity.
- This repository contains generated HAL files. Regenerate with CubeMX only
  when the corresponding application-layer contracts are preserved.
