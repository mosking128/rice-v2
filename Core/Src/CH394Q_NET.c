/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH394Q_NET.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2025/07/01
 * Description        : CH394Q net program body
 *******************************************************************************/
#include "debug.h"
#include <CH394Q_NET.h>
#include <CH394Q_SPI.h>
#include <CH394Q.h>

uint8_t socketmode[8];
uint8_t MyBuffer[8][2048];
/* CH394Q IP Information */
uint8_t  CH394Q_MACAddr [6];                                   /* CH394Q MAC       */
uint8_t  CH394Q_IPAddr  [4] = {192, 168, 1, 200};              /* CH394Q IP        */
uint8_t  CH394Q_GWIPAddr[4] = {192, 168, 1, 1  };              /* CH394Q Gateway   */
uint8_t  CH394Q_IPMask  [4] = {255, 255, 255, 0};              /* CH394Q Mask      */
uint16_t CH394Q_Port = 1000;                                   /* CH394Q Port      */
/* Destination IP information */
uint8_t  DesIP[4] = {192, 168, 1, 100};                        /* Destination IP   */
uint16_t DesPort  = 1000;                                      /* Destination port */
/* Multicast IP information */
uint8_t  MultiMAC [6] = {0x01,0x00,0x5e,0x01,0x01,0x12};       /* Multicast MAC    */
uint8_t  MultiMAC6[6] = {0x33,0x33,0x00,0xAB,0xCD,0xEF};       /* IPv6 Multicast MAC */
uint8_t  MultiIP  [4] = {224,1,1,18};                          /* Multicast IP     */
uint16_t MultiPort = 3000;                                     /* Multicast port   */
/* CH394Q IPv6 information */
uint8_t  CH394Q_IPAddr_IPv6[16] = {
         // fe80::1234:5
         0xfe, 0x80,  0x0,  0x0, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x00, 0x05};      /* CH394Q IP   */
uint8_t  CH394Q_GWIPAddr_IPv6[16] = {
	// fe80::82ea:7ff:fee1:9776
         0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x82, 0xea, 0x07, 0xff, 0xfe, 0xe1, 0x97, 0x76};      /* CH394Q Gateway */
uint8_t  CH394Q_IPMask_IPv6[16] = {
         0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};      /* CH394Q Mask */
uint8_t  CH394Q_GUA_IPv6[16] = {
         // 2001::1234:5
         0x20, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x50, 0x54, 0x00, 0x04};      /* CH394Q Global Unicast Address */
uint8_t  CH394Q_MultiIPv6[16] = {
         // FF02::100:00AB:CDEF
         0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x01, 0x00, 0x00, 0xAB, 0xCD, 0xEF};      /* CH394Q Multicast Address */
uint16_t CH394Q_Port_IPv6 = 1000;                              /* CH394Q Port */
/* Destination IPv6 information */
uint8_t  DesIP_IPv6[16] = {
        // fe80::f4b:4dd1:1e01:b510
         0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x0f, 0x4b, 0x4d, 0xd1, 0x1e, 0x01, 0xb5, 0x10};      /* Destination IP    */
uint16_t DesPort_IPv6 = 1000;                                  /* Destination port  */

/********************************************************************************
 * Function Name  : CH394Q_InfParam
 * Description    : Configure CH394Q network parameters
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_InfParam(void)
{
    uint8_t ip[4], mask[4], gw[4];
    CH394Q_SetIP(CH394Q_IPAddr);
    CH394Q_SetSMIP(CH394Q_IPMask);
    CH394Q_SetGWIP(CH394Q_GWIPAddr);
    CH394Q_GetMAC(CH394Q_MACAddr);
    printf(" CH394Q MAC address : %02x.%02x.%02x.%02x.%02x.%02x\r\n", CH394Q_MACAddr[0], CH394Q_MACAddr[1], CH394Q_MACAddr[2],
           CH394Q_MACAddr[3], CH394Q_MACAddr[4], CH394Q_MACAddr[5]);
    CH394Q_GetIP(ip);
    printf(" CH394Q IP address  : %d.%d.%d.%d\r\n", ip[0], ip[1], ip[2], ip[3]);
    CH394Q_GetSMIP(mask);
    printf(" CH394Q subnet mask : %d.%d.%d.%d\r\n", mask[0], mask[1], mask[2], mask[3]);
    CH394Q_GetGWIP(gw);
    printf(" CH394Q gateway     : %d.%d.%d.%d\r\n", gw[0], gw[1], gw[2], gw[3]);
}

/********************************************************************************
 * Function Name  : CH394Q_IPv6_InfParam
 * Description    : Configure CH394Q IPv6 network parameters
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_IPv6_InfParam(void)
{
    if (CH394Q_GetCHIP_CONFIG() == 1)
    {
        CH394Q_SetLLA(CH394Q_IPAddr_IPv6);
        Delay_Ms(1);
        CH394Q_SetGWIP6(CH394Q_GWIPAddr_IPv6);
        Delay_Ms(1);
        CH394Q_GetLLA(CH394Q_IPAddr_IPv6);
        Delay_Ms(1);
        printf(" Local IP           :");
        print_ipv6_addr(CH394Q_IPAddr_IPv6);
        CH394Q_GetGWIP6(CH394Q_GWIPAddr_IPv6);
        Delay_Ms(1);
        printf(" Local Gateway      :");
        print_ipv6_addr(CH394Q_GWIPAddr_IPv6);
        Delay_Ms(2000);
    }
}

/********************************************************************************
 * Function Name  : CH394Q_TCPServerSocketInit
 * Description    : TCP server socket initialization function
 * Input          : sockindex: socket number
                    mode: Set socket mode
                    sourport: Source port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_TCPServerSocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport)
{
    CH394Q_Socket_Init(sockindex, mode, sourport);
    CH394Q_Socket_Listen(sockindex);
    socketmode[sockindex] = TCPServer;
}

/********************************************************************************
 * Function Name  : CH394Q_TCPClientSocketInit
 * Description    : TCP client socket initialization function
 * Input          : sockindex: socket number
                    mode: Set socket mode
                    sourport: Source port
                    desip: Destination IP
                    desport: Destination port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_TCPClientSocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport, uint8_t *desip, uint16_t desport)
{
    CH394Q_Socket_Init(sockindex, mode, sourport);
    CH394Q_Socket_Connect(sockindex, desip, desport);
    socketmode[sockindex] = TCPClient;
}

/********************************************************************************
 * Function Name  : CH394Q_TCPClient_IPv6_SocketInit
 * Description    : IPv6 TCP client socket initialization function
 * Input          : sockindex��socket number
                    mode: Set socket mode
                    sourport: Source port
                    desip: Destination IP
                    desport: Destination port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_TCPClient_IPv6_SocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport, uint8_t *desip, uint16_t desport)
{
    CH394Q_Socket_Init(sockindex, mode, sourport);
    CH394Q_Socket_Connect6(sockindex, desip, desport);
    socketmode[sockindex] = TCPClient6;
}

/********************************************************************************
 * Function Name  : CH394Q_UDPSocketInit
 * Description    : UDP socket initialization function
 * Input          : sockindex: socket number
                    mode: Set socket mode
                    sourport: Source port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_UDPSocketInit(uint8_t sockindex, uint8_t mode, uint16_t sourport)
{
    CH394Q_Socket_Init(sockindex, mode, sourport);
    socketmode[sockindex] = UDP;
}

/********************************************************************************
 * Function Name  : CH394Q_UDPMultiSocketInit
 * Description    : UDP multicast socket initialization function
 * Input          : sockindex: socket number
                    mode: Set socket mode
                    multiip: Multicast IP
                    multimac: Multicast MAC
                    multiport: Multicast port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_UDPMultiSocketInit(uint8_t sockindex, uint8_t mode, uint8_t *multiip, uint8_t *multimac, uint16_t multiport)
{
    CH394Q_SetSn_DIP(sockindex, multiip);
    CH394Q_SetSn_DMAC(sockindex, multimac);
    CH394Q_SetSn_DPORT(sockindex, multiport);
    CH394Q_Socket_Init(sockindex, mode, multiport);
    socketmode[sockindex] = UDP;
}

/********************************************************************************
 * Function Name  : CH394Q_UDPMultiIPv6SocketInit
 * Description    : IPv6 UDP multicast socket initialization function
 * Input          : sockindex: socket number
                    mode: Set socket mode
                    multiip: Multicast IPv6 address
                    multimac: Multicast MAC
                    multiport: Multicast port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_UDPMultiIPv6SocketInit(uint8_t sockindex, uint8_t mode, uint8_t *multiip, uint8_t *multimac, uint16_t multiport)
{
    CH394Q_SetSn_DIP6(sockindex, multiip);
    CH394Q_SetSn_DMAC(sockindex, multimac);
    CH394Q_SetSn_DPORT(sockindex, multiport);
    CH394Q_Socket_Init(sockindex, mode, multiport);
    socketmode[sockindex] = UDP;
}

/********************************************************************************
 * Function Name  : CH394Q_IPRAW_IPv6_SocketInit
 * Description    : IPv6 IPRAW socket initialization function
 * Input          : sockindex: socket number
                    mode: Set socket mode
                    ippro: IP protocol number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_IPRAW_IPv6_SocketInit(uint8_t sockindex, uint8_t mode, uint8_t ippro)
{
    CH394Q_SetSn_IPPRO(sockindex, ippro);
    CH394Q_Socket_Init(sockindex, mode, 0);
    socketmode[sockindex] = IPRAW6;
}

/********************************************************************************
 * Function Name  : CH394Q_MACRAWSocketInit
 * Description    : MACRAW socket initialization function
 * Input          : sockindex: socket number
                    mode: Set socket mode
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_MACRAWSocketInit(uint8_t sockindex, uint8_t mode)
{
    CH394Q_Socket_Init(sockindex, mode, 0);
    socketmode[sockindex] = MACRAW;
}

/********************************************************************************
 * Function Name  : CH394Q_ReopenSocket
 * Description    : Reopen socket
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_ReopenSocket(uint8_t sockindex)
{
    CH394Q_SetSn_INT(sockindex, 0xFF);
    CH394Q_Socket_Open(sockindex);
    if (socketmode[sockindex] == TCPServer)
    {
        CH394Q_Socket_Listen(sockindex);
    }
    if (socketmode[sockindex] == TCPClient)
    {
        CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_CONNECT);
        while (CH394Q_GetSn_CTRL(sockindex));
    }
    if (socketmode[sockindex] == TCPClient6)
    {
        CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_CONNECT6);
        while (CH394Q_GetSn_CTRL(sockindex));
    }
}

/********************************************************************************
 * Function Name  : CH394Q_SocketInterrupt
 * Description    : Socket interrupt function
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SocketInterrupt(uint8_t sockindex)
{
    int len = 0;
    uint16_t udp_desport;
    uint8_t udp_desip[16];
    uint16_t udp_real_len = 0;
    uint8_t ipraw6_desip[16];
    uint16_t ipraw6_real_len = 0;
    uint16_t macraw_real_len = 0;
    uint8_t Sn_STA_state = CH394Q_GetSn_STA(sockindex);
    uint8_t Sn_INT_state = CH394Q_GetSn_INT(sockindex);
    if (Sn_INT_state & Sn_INT_RECV)
    {
        len = CH394Q_GetSn_RX_RS(sockindex);
        CH394Q_SetSn_INT(sockindex, Sn_INT_RECV);
        if (len > 0)
        {
            if (Sn_STA_state == SOCK_TCP_ESTABLISHED)
            {
                CH394Q_SocketTCPRecv(sockindex, MyBuffer[sockindex], len);
                CH394Q_SocketTCPSend(sockindex, MyBuffer[sockindex], len);
            }
            else if (Sn_STA_state == SOCK_UDP)
            {
								uint8_t flag = 0;
								while (len > 0)
								{
										udp_real_len = CH394Q_Socket_UDP_Recv(sockindex, MyBuffer[sockindex], len, udp_desip, &udp_desport, &flag);
										MyBuffer[sockindex][udp_real_len] = 0;
								#if IPv6_MODE
										if (flag == 0)
										{
												printf("PC[%d.%d.%d.%d:%d]: %s\r\n", udp_desip[0], udp_desip[1], udp_desip[2], udp_desip[3], udp_desport, MyBuffer[sockindex]);
												len = len - udp_real_len - 8;
										}
										else
										{
												printf("PC[IPv6]: %s\r\n", MyBuffer[sockindex]);
												len = len - udp_real_len - 20;
										}
								#else
										printf("PC[%d.%d.%d.%d:%d]: %s\r\n", udp_desip[0], udp_desip[1], udp_desip[2], udp_desip[3], udp_desport, MyBuffer[sockindex]);
										len = len - udp_real_len - 8;
								#endif
								}
            }
            else if (Sn_STA_state == SOCK_MACRAW)
            {
                while (len > 0)
                {
                    macraw_real_len = CH394Q_Socket_MACRAW_Recv(sockindex, MyBuffer[sockindex], len);
                    CH394Q_Socket_MACRAW_Send(sockindex, MyBuffer[sockindex], macraw_real_len);
                    len = len - macraw_real_len - 2;
                }
            }
            else if (Sn_STA_state == Sn_STA_IPRAW6)
            {
                while (len > 0)
                {
                    ipraw6_real_len = CH394Q_Socket_IPRAW6_Recv(sockindex, MyBuffer[sockindex], len, ipraw6_desip);
                    CH394Q_Socket_IPRAW6_Send(sockindex, MyBuffer[sockindex], ipraw6_real_len, ipraw6_desip);
                    len = len - ipraw6_real_len - 18;
                }
            }
        }
    }
    if (Sn_INT_state & Sn_INT_DISCONNECT)
    {
        CH394Q_SetSn_INT(sockindex, Sn_INT_DISCONNECT);
        if (socketmode[sockindex] != UDP && socketmode[sockindex] != MACRAW)
        {
            printf(" DISCONNECT\r\n");
            if (Sn_STA_state == SOCK_CLOSE_WAIT)
            {
                CH394Q_Socket_Disconnect(sockindex);
            }
            while (CH394Q_GetSn_STA(sockindex) != 0x00);
            CH394Q_ReopenSocket(sockindex);
        }
    }
    if (Sn_INT_state & Sn_INT_CONNECT)
    {
        printf(" CONNECT\r\n");
        CH394Q_SetSn_INT(sockindex, Sn_INT_CONNECT);
    }
    if (Sn_INT_state & Sn_INT_SEND_SUC)
    {
        CH394Q_SetSn_INT(sockindex, Sn_INT_SEND_SUC);
    }
    if (Sn_INT_state & Sn_INT_TIMEOUT)
    {
        CH394Q_SetSn_INT(sockindex, Sn_INT_TIMEOUT);
        if (socketmode[sockindex] != UDP)
        {
            printf(" TIMEOUT\r\n");
            while (CH394Q_GetSn_STA(sockindex) != 0x00);
            CH394Q_ReopenSocket(sockindex);
        }
    }
}

/********************************************************************************
 * Function Name  : CH394Q_GlobalInterrupt
 * Description    : Global interrupt function
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GlobalInterrupt(void)
{
    uint8_t i, t = 0;
    static uint8_t PA[8];
    uint8_t SINT_state = CH394Q_GetSINT();
    uint8_t GINT_state = CH394Q_GetGINT();
    uint8_t SINT_socket[8] = {
    SINT_state_SOCK0, SINT_state_SOCK1, SINT_state_SOCK2, SINT_state_SOCK3,
    SINT_state_SOCK4, SINT_state_SOCK5, SINT_state_SOCK6, SINT_state_SOCK7};
    for (i = 0; i < 8; i++)
    {
        if (SINT_state & SINT_socket[i])
        {
            CH394Q_SocketInterrupt(i);
        }
    }
    if (GINT_state & GINT_IP_CONFLI)
    {
        printf(" IP CONFLICT\r\n");
        CH394Q_SetGINT(GINT_IP_CONFLI);
    }
    if (GINT_state & GINT_UNREACH)
    {
        printf(" UNREACHABLE\r\n");
        CH394Q_SetGINT(GINT_UNREACH);
    }
    if (GINT_state & GINT_MP)
    {
        printf(" MAGIC\r\n");
        CH394Q_SetGINT(GINT_MP);
    }
    if (GINT_state & GINT_UNREACH6)
    {
        printf(" UNREACH6\r\n");
        CH394Q_SetGINT(GINT_UNREACH6);
    }
    if (GINT_state & GINT_RA)
    {
        printf(" RA\r\n");
        CH394Q_SetGINT(GINT_RA);
        CH394Q_GetPA(PA);
        if (CH394Q_Compare_PA(PA, CH394Q_GUA_IPv6) == 0)
        {
            for (t = 0; t < 8; t++)
            {
                CH394Q_GUA_IPv6[t] = PA[t];
            }
        }
        CH394Q_SetGUA(CH394Q_GUA_IPv6);
        CH394Q_GetGUA(CH394Q_GUA_IPv6);
        printf(" Global unicast address:");
        print_ipv6_addr(CH394Q_GUA_IPv6);
    }
    if (GINT_state & GINT_IPv6_CONFLI)
    {
        printf(" IPv6 CONFLI\r\n");
        CH394Q_SetGINT(GINT_IPv6_CONFLI);
    }
}
/********************************************************************************
 * Function Name  : CH394Q_UDPSendData
 * Description    : Proactively send UDP data to the default destination (DesIP, DesPort)
 * Input          : sockindex: socket number
 *                  data: Send data buffer
 *                  len: Data length
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_UDPSendData(uint8_t sockindex, const uint8_t *data, uint16_t len)
{
    CH394Q_SetSn_INT(sockindex, 0xFF);
    CH394Q_SocketSendTo(sockindex, data, len, DesIP, DesPort);
    printf("-> PC: %s\r\n", data);
}
