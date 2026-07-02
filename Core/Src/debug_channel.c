/**
 * @file    debug_channel.c
 * @brief   调试通道抽象层实现
 */

#include "debug_channel.h"
#include "CH394Q.h"
#include "task_msg.h"
#include "cmsis_os2.h"
#include <string.h>

extern uint8_t  DesIP[4];
extern uint16_t DesPort;
extern osMessageQueueId_t udpQueneHandle;

#define UDP_DEBUG_RING_SIZE  2048U
static uint8_t  udp_debug_ring[UDP_DEBUG_RING_SIZE];
static volatile uint32_t udp_debug_head = 0U;
static volatile uint32_t udp_debug_tail = 0U;

#define UDP_DEBUG_OUT_MAX    1400U
static uint8_t  udp_debug_out_buf[UDP_DEBUG_OUT_MAX];
static volatile uint32_t udp_debug_out_len = 0U;

static uint8_t  udp_debug_sender_ip[4];
static uint16_t udp_debug_sender_port = 0U;

volatile DebugChannelMode g_debug_channel = DEBUG_CHANNEL_SERIAL;

void DebugChannel_Init(void)
{
    g_debug_channel = DEBUG_CHANNEL_SERIAL;
    udp_debug_head = 0U;
    udp_debug_tail = 0U;
    udp_debug_out_len = 0U;
    (void)memcpy(udp_debug_sender_ip, DesIP, 4U);
    udp_debug_sender_port = DesPort;
}

DebugChannelMode DebugChannel_GetMode(void)
{
    return g_debug_channel;
}

/* 累积字符，遇 '\n' 整行通过 udpQuene 发给 udpTask 统一处理 */
void DebugChannel_UdpPutch(unsigned char OutCh, union OutputStreamInfo *Stream)
{
    (void)Stream;

    if (udp_debug_out_len < (UDP_DEBUG_OUT_MAX - 1U))
    {
        udp_debug_out_buf[udp_debug_out_len++] = OutCh;
    }

    if (OutCh == '\n' && udp_debug_out_len > 0U && udpQueneHandle != NULL)
    {
        TaskMsg msg;
        uint32_t copy_len = udp_debug_out_len;
        if (copy_len > sizeof(msg.data) - 1U)
            copy_len = sizeof(msg.data) - 1U;
        (void)memcpy(msg.data, udp_debug_out_buf, copy_len);
        msg.data[copy_len] = '\0';
        msg.len = (uint16_t)copy_len;
        msg.type = MSG_UDP_LINE;
        (void)osMessageQueuePut(udpQueneHandle, &msg, 0U, 0U);
        udp_debug_out_len = 0U;
    }
}

uint32_t DebugChannel_UdpInputWrite(const uint8_t *data, uint32_t len)
{
    uint32_t count = 0U;
    while (count < len)
    {
        uint32_t next = (udp_debug_head + 1U) % UDP_DEBUG_RING_SIZE;
        if (next == udp_debug_tail) break;
        udp_debug_ring[udp_debug_head] = data[count++];
        udp_debug_head = next;
    }
    return count;
}

int DebugChannel_UdpGetChar(void)
{
    if (udp_debug_tail == udp_debug_head) return -1;
    int ch = (int)udp_debug_ring[udp_debug_tail];
    udp_debug_tail = (udp_debug_tail + 1U) % UDP_DEBUG_RING_SIZE;
    return ch;
}

void DebugChannel_SetSender(const uint8_t *ip, uint16_t port)
{
    if (ip != NULL)
        (void)memcpy(udp_debug_sender_ip, ip, 4U);
    udp_debug_sender_port = port;
}
