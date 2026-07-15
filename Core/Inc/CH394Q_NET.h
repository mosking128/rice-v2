/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH394Q_NET.h
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2025/07/01
 * Description        : CH394Q net program header file
 *******************************************************************************/
#ifndef CH394Q_NET_H_
#define CH394Q_NET_H_
#include <CH394Q.h>

#define TCPServer  0x01
#define TCPClient  0x02
#define UDP        0x03
#define MACRAW     0x04
#define IPRAW6     0x05
#define TCPClient6 0x06

#define SINT_state_SOCK0  0x01
#define SINT_state_SOCK1  0x02
#define SINT_state_SOCK2  0x04
#define SINT_state_SOCK3  0x08
#define SINT_state_SOCK4  0x10
#define SINT_state_SOCK5  0x20
#define SINT_state_SOCK6  0x40
#define SINT_state_SOCK7  0x80

void CH394Q_InfParam(void);
void CH394Q_IPv6_InfParam(void);
void CH394Q_GlobalInterrupt(void);
void CH394Q_SocketInterrupt(uint8_t sockindex);
void CH394Q_ReopenSocket(uint8_t sockindex);
void CH394Q_MACRAWSocketInit(uint8_t sockindex, uint8_t mode);
void CH394Q_UDPSocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport);
void CH394Q_UDPSendData(uint8_t sockindex, const uint8_t *data, uint16_t len);
void CH394Q_TCPServerSocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport);
void CH394Q_TCPClientSocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport,uint8_t * desip, uint16_t desport);
void CH394Q_TCPClient_IPv6_SocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport,uint8_t * desip, uint16_t desport);
void CH394Q_UDPMultiSocketInit(uint8_t sockindex, uint8_t mode, uint8_t * multiip, uint8_t * multimac, uint16_t multiport);
void CH394Q_UDPMultiIPv6SocketInit(uint8_t sockindex, uint8_t mode, uint8_t * multiip, uint8_t * multimac, uint16_t multiport);
void CH394Q_IPRAW_IPv6_SocketInit(uint8_t sockindex, uint8_t mode, uint8_t ippro);
#endif
