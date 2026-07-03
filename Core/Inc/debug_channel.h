/**
 * @file    debug_channel.h
 * @brief   调试通道抽象层 — 支持串口和以太网(UDP)两种调试 I/O 通道
 */

#ifndef __DEBUG_CHANNEL_H__
#define __DEBUG_CHANNEL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

union OutputStreamInfo;

typedef enum {
    DEBUG_CHANNEL_SERIAL = 0,
    DEBUG_CHANNEL_UDP    = 1
} DebugChannelMode;

/* Unified I/O channel selector — the single source of truth for all I/O routing */
typedef enum {
    IO_CHANNEL_SERIAL = 0,
    IO_CHANNEL_UDP    = 1
} IOChannel;

extern volatile DebugChannelMode g_debug_channel;
extern volatile IOChannel g_active_channel;

void DebugChannel_Init(void);
DebugChannelMode DebugChannel_GetMode(void);

/* Flush accumulated UDP output immediately (for prompts with no trailing \n) */
void DebugChannel_UdpFlush(void);

/* PicoC 输出字符，在 UDP 调试模式下累积到缓冲区，
 * 遇 '\n' 通过 udpQuene → udpTask → CH394Q 发出 */
void DebugChannel_UdpPutch(unsigned char OutCh, union OutputStreamInfo *Stream);

/* UDP → 调试输入环形缓冲区 */
uint32_t DebugChannel_UdpInputWrite(const uint8_t *data, uint32_t len);
int DebugChannel_UdpGetChar(void);
void DebugChannel_SetSender(const uint8_t *ip, uint16_t port);

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_CHANNEL_H__ */
