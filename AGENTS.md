# AGENTS.md

This file provides guidance to Codex (Codex.ai/code) when working with code in this repository.

## Project Overview

RICE v2 — PicoC C interpreter running on STM32H750VBTx (Cortex-M7, 480 MHz) under FreeRTOS. Provides interactive C scripting via serial terminal (USART1, 115200 8N1) with breakpoint debugging, single-stepping, and variable inspection.

## Build & Flash

- **IDE:** Keil MDK. Open `MDK-ARM/UART_DMA_H750.uvprojx`, build with F7, flash via ST-Link.
- **CubeMX:** The `.ioc` file is `UART_DMA_H750.ioc`. Regenerating code overwrites HAL-layer files (see Layer 4 below).
- **No CLI build** — Keil is the sole build system for the embedded target.

## Architecture: 4-Layer Stack

```
Layer 1: PicoC Interpreter Core      picoc/*.c          Pure C, no HW dependencies. Never modify.
Layer 2: Platform Adaptation          picoc/platform/*   I/O bridge (platform_stm32h7.c) + HW bindings (library_stm32h7.c)
Layer 3: Application                  Core/Src/*_app.c   REPL state machine, serial DMA driver, task definitions
Layer 4: HAL (CubeMX-generated)       Core/Src/main.c, usart.c, dma.c, gpio.c, stm32h7xx_it.c, etc.
```

- **Layers 1-2** are reusable across MCU ports. **Layer 3** needs ~80-98% reuse per port. **Layer 4** is fully rewritten per chip via CubeMX.
- See `MIGRATION.md` for the complete porting guide and file dependency matrix.

## Task Model (FreeRTOS CMSIS_V2)

| Task | Priority | Stack | Role |
|------|----------|-------|------|
| serialTask | `osPriorityHigh` (40) | 4 KB | Polls `SerialApp_Read()`, parses protocol lines, enqueues `TaskMsg` |
| picocTask | `osPriorityNormal` (24) | 32 KB | Dequeues from `uartQuene`, runs PicoC interpreter, handles debug |
| udpTask | `osPriorityAboveNormal` | 16 KB | CH394Q Ethernet chip event loop + UDP send |

- **IPC:** Two `osMessageQueue` instances — `uartQuene` (serialTask → picocTask, 16 × 256-byte `TaskMsg`) and `udpQuene` (serialTask → udpTask).
- picocTask starts **suspended** and is resumed only when `MSG_RICE_ENABLE` is sent (post-boot activation).

## Key Data Flow

```
DMA ISR → rx_ring[8192] (lock-free SPSC) → serialTask polls SerialApp_Read()
    → PicocApp_ProcessChars() parses protocol lines
    → source lines enqueued as MSG_SOURCE_LINE → picocTask dequeues & executes
```

- **ISR-to-task:** `SerialApp_RxEventCallback()` (called from `HAL_UARTEx_RxEventCallback`) copies DMA circular buffer → rx_ring.
- **Debug mode:** When `g_debug_input_active` is set, serialTask skips reading rx_ring — picocTask consumes it directly to avoid races on single-step/continue commands.

## Cooperative Abort Mechanism

PicoC's loop structures (`while`, `for`, `do-while`) and blocking I/O (`scanf`, `getchar`) check an `AbortRequested` flag each iteration. When serialTask receives `:abort`, it calls `PicocApp_Abort()` which sets the flag. The interpreter detects it, unwinds via `setjmp`/`longjmp` **within picocTask only** (no cross-task longjmp — that would be undefined behavior).

## Key Interfaces

- **`Core/Inc/task_msg.h`** — `TaskMsg` struct and `TaskMsgType` enum. The contract between tasks.
- **`Core/Inc/picoc_app.h`** — `PicocApp_ProcessChars()` is the protocol parser entry point; `PicocApp_ConsoleGetCharBlocking()` is called by PicoC's platform I/O layer for blocking input.
- **`Core/Inc/serial_app.h`** — `SerialApp_Read()` / `SerialApp_Write()` for ring-buffer access. Thread-safe: ISR writes, tasks read (no locks).
- **`picoc/platform.h`** — `STM32H750_HOST` defines heap size (64 KB), feature flags, and stdlib bindings.

## Important Constraints

- `PicocApp_ProcessChars()` may return 0 (no message yet — data buffered internally) or 1 (`out_msg` valid for enqueue).
- Debug commands (`:step`, `:cont`, `:eval`, `:vars`, `:set`) are consumed directly by picocTask via `g_debug_input_active` flag — they bypass the message queue.
- Heap: FreeRTOS `heap_4` with 30 KB total. PicoC has its own 64 KB heap (`HEAP_SIZE` in platform.h).
- Error recovery: `setjmp` at picocTask loop entry; any `ProgramFail` or `PlatformExit` longjmps back to the REPL prompt.
