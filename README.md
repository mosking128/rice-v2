# RICE v2

RICE v2 is an interactive C environment for the STM32H750VBTx. It embeds the
[PicoC](picoc/) interpreter in a FreeRTOS application and exposes it through
USART1 and an optional CH394Q UDP link.

[中文文档](README_CN.md) | [Porting guide](MIGRATION.md) | [License](LICENSE)

## Hardware and Runtime

- MCU: STM32H750VBTx, Cortex-M7, up to 480 MHz
- UART: USART1 on PA9 (TX) and PA10 (RX), 115200 baud, 8N1
- RTOS: FreeRTOS CMSIS-RTOS v2, kernel 10.6.2
- Network: CH394Q on SPI4, UDP socket 0
- Default CH394Q address: `192.168.1.200:1000`
- Default UDP peer: `192.168.1.100:1000`

The default network values are defined in `Core/Src/CH394Q_NET.c`.

## Complete Serial Workflow

This is the normal path from a clean checkout to executing and debugging a C
script. Commands are case-sensitive and each command must end with the line
terminator configured in the terminal.

### 1. Build and Flash

Firmware is built with Keil MDK; there is no supported command-line build.

1. Open `MDK-ARM/UART_DMA_H750.uvprojx` in Keil MDK.
2. Build with **F7**.
3. Connect the board through ST-Link and flash the generated image.
4. Connect a serial terminal to USART1 at **115200, 8 data bits, no parity,
   1 stop bit**. Use LF or CRLF as the transmit line ending. Disable local echo
   if the terminal would otherwise show every typed character twice.

The CubeMX project is `UART_DMA_H750.ioc`. Regenerating CubeMX code can
overwrite HAL files in `Core/Src` and `Core/Inc`.

### 2. Activate the REPL

After boot, the board starts in UDP bridge mode rather than in the interpreter:

```text
=== UDP Bridge Ready ===
```

Send the exact line `:Rice` over USART1. The active channel then prints the
RICE banner and `Rice> ` prompt:

```text
:Rice
RICE <version> -- Runtime Interactive C Environment
Rice>
```

Only send C code after the prompt appears. While bridge mode is active, normal
serial lines are forwarded to the configured UDP peer instead of being treated
as PicoC input.

### 3. Run C Interactively

Enter a complete statement or expression and press Enter. Expressions are
printed automatically. For an incomplete block, the prompt changes to
`     > ` until all braces, brackets, parentheses, strings, and comments are
closed.

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

REPL declarations remain in the REPL interpreter instance until `:reset` or a
board reset. A single queued REPL message has a 255-byte source payload; keep
individual REPL submissions below that limit.

### 4. Upload and Run a Complete Script

Use load mode for a multi-line program. `:load` clears the previous upload,
returns `:ok`, and changes the prompt to `load> `. Send source one line at a
time, then send `:end` on a line by itself. The source is stored in an 8 KiB
buffer and executed in an isolated PicoC instance named `serial_load`.

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

`main()` is called automatically when it is present. Preserve blank lines when
copying a file because the debugger reports the original upload line numbers.
Use `:load <bytes>` only as a size pre-check; a value greater than 8191 is
rejected with `:err buffer full`. Send `:abort` before `:end` to discard the
upload and return to `Rice> `.

### 5. Set a Breakpoint and Debug the Uploaded Script

Breakpoints target the `serial_load` filename and use one-based source line
numbers. Set them before `:load` or while the script is paused. This complete
example stops on line 5, where `value` is incremented:

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

While paused, the interpreter consumes the following commands directly. Do not
send ordinary C source until `:cont` finishes the script or `:abort` stops it.

| Command | Paused-state action |
| --- | --- |
| `:cont` | Resume until the next breakpoint or program completion. |
| `:step` | Run one statement and pause again. |
| `:eval <expression>` | Evaluate an expression in the current scope. |
| `:vars` | Emit visible variables as `:var ...` lines, followed by `:ok vars`. |
| `:set <name> <value>` | Change a visible variable. |
| `:bkpt <file> <line>` | Add a breakpoint. |
| `:bkptclear <file> <line>` | Remove a breakpoint. |
| `:abort` | Stop the paused script and return to the REPL. |

Breakpoints configured for an upload are cleared after that upload completes.

### 6. Interrupt, Check, or Reset

Runaway loop example:

```text
Rice> while (1) { }
Rice> :ping
:pong
Rice> :abort
```

`:abort` is cooperative. It is checked by PicoC loop bodies and blocking
console input, so it interrupts normal `while`, `for`, and `do` loops without
resetting the board. Code that does not reach a PicoC checkpoint cannot be
interrupted immediately. `:ping` is handled by the serial task and remains
responsive while a script runs.

Use `:reset` to recreate the REPL PicoC instance, discard an active upload, and
clear its breakpoints. Use `:RST` only when a complete MCU reset is intended;
the board returns to UDP bridge mode and requires `:Rice` again.

## UDP Workflow and Channel Switching

At boot, serial input and UDP data are bridged in both directions. To make UDP
the interpreter channel, send a UDP datagram containing `:Rice`. The sender
receives the RICE banner, a `Rice> ` prompt, and `:ok rice`; subsequent REPL,
load, debug, and output traffic uses UDP.

Use the following commands to move the active interpreter channel. The `:ok
debug ...` reply is sent on the old channel; the new channel receives the next
prompt.

```text
:debug udp
:debug serial
```

When serial is active, incoming UDP traffic is ignored except for `:debug udp`.
When UDP is active, incoming serial traffic is ignored except for `:debug
serial`. Configure the CH394Q address and UDP peer first if the default network
addresses do not match the local network.

## Command Reference

| Command | Meaning | Normal response |
| --- | --- | --- |
| `:Rice` | Leave bridge mode and activate the channel's REPL. | RICE banner and `Rice> `; UDP also sends `:ok rice`. |
| `:load [bytes]` | Start a new script upload. | `:ok`, then `load> `. |
| `:end` | Execute the accumulated upload. | Program output, then `:ok ready`. |
| `:abort` | Cancel an upload or cooperatively interrupt running code. | `:err load cancelled` for a cancelled upload. |
| `:ping` | Check communication. | `:pong`. |
| `:reset` | Reinitialize the REPL interpreter and clear state. | `:ok`. |
| `:RST` | Reset the STM32 through `HAL_NVIC_SystemReset()`. | `:ok`, then boot output. |
| `:bkpt <file> <line>` | Set a breakpoint. | `:ok bkpt`. |
| `:bkptclear <file> <line>` | Clear a breakpoint. | `:ok bkptclear`. |
| `:debug serial` | Select USART1 as active I/O. | `:ok debug serial` on the previous channel. |
| `:debug udp` | Select UDP as active I/O. | `:ok debug udp` on the previous channel. |

## Limitations

- The target has no filesystem. Host-file `#include` and file APIs are not
  available; use `:load` to transfer complete source.
- The upload buffer is 8 KiB, and task messages carry at most 255 bytes of
  source text.
- FreeRTOS `heap_4` is configured for 72 KiB. PicoC has a separate 64 KiB heap.
- Buffer sizes, task stacks, and network values are static configuration;
  profile resource use before increasing script complexity.

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

- `serialTask`: high priority, 4 KiB stack; drains serial input and parses
  protocol lines.
- `picocTask`: normal priority, 32 KiB stack; runs PicoC and the debugger; it
  starts suspended and resumes after `:Rice`.
- `udpTask`: above-normal priority, 8 KiB stack; services CH394Q UDP I/O.

## Repository Map

```text
Core/Src, Core/Inc/   HAL glue, FreeRTOS tasks, serial and PicoC application
picoc/                PicoC interpreter core and STM32H7 platform bindings
Drivers/              STM32 HAL and CMSIS device headers
Middlewares/          FreeRTOS/CMSIS-RTOS integration
MDK-ARM/              Keil project, startup code, linker settings
MIGRATION.md          Porting workflow and file dependency matrix
```

The codebase is layered: `picoc/*.c` is the reusable interpreter core;
`picoc/platform/*` contains platform bindings; `Core/Src/*_app.c` owns the
application protocol; CubeMX/HAL files own chip-specific startup and drivers.

## License

MIT. See [LICENSE](LICENSE).
