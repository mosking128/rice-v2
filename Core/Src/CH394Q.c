/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH394Q.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2025/07/01
 * Description        : CH394Q application program file
 *******************************************************************************/
#include <CH394Q_SPI.h>
#include <CH394Q.h>

uint8_t TX_BUFF[SOCKET_NUM];
uint8_t RX_BUFF[SOCKET_NUM];
/********************************************************************************
 * Function Name  : CH394Q_SetMODE
 * Description    : Set CH394Q mode
 * Input          : mode: Set mode
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetMODE(uint8_t mode)
{
    CH394Q_Write(MODE, mode);
}

/********************************************************************************
 * Function Name  : CH394Q_SetGWIP
 * Description    : Set CH394Q gateway address
 * Input          : gwip: Gateway address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetGWIP(uint8_t *gwip)
{
    CH394Q_WriteSafe(GWIP0, gwip[0]);
    CH394Q_WriteSafe(GWIP1, gwip[1]);
    CH394Q_WriteSafe(GWIP2, gwip[2]);
    CH394Q_WriteSafe(GWIP3, gwip[3]);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSMIP
 * Description    : Set CH394Q subnet mask address
 * Input          : smip: Subnet mask address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSMIP(uint8_t *smip)
{
    CH394Q_WriteSafe(SMIP0, smip[0]);
    CH394Q_WriteSafe(SMIP1, smip[1]);
    CH394Q_WriteSafe(SMIP2, smip[2]);
    CH394Q_WriteSafe(SMIP3, smip[3]);
}

/********************************************************************************
 * Function Name  : CH394Q_SetMAC
 * Description    : Set CH394Q MAC address
 * Input          : mac: MAC address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetMAC(uint8_t *mac)
{
    CH394Q_Write(MAC0, mac[0]);
    CH394Q_Write(MAC1, mac[1]);
    CH394Q_Write(MAC2, mac[2]);
    CH394Q_Write(MAC3, mac[3]);
    CH394Q_Write(MAC4, mac[4]);
    CH394Q_Write(MAC5, mac[5]);
}

/********************************************************************************
 * Function Name  : CH394Q_SetIP
 * Description    : Set CH394Q source IP address
 * Input          : ip: IP address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetIP(uint8_t *ip)
{
    CH394Q_WriteSafe(IP0, ip[0]);
    CH394Q_WriteSafe(IP1, ip[1]);
    CH394Q_WriteSafe(IP2, ip[2]);
    CH394Q_WriteSafe(IP3, ip[3]);
}

/********************************************************************************
 * Function Name  : CH394Q_SetIIT
 * Description    : Interrupt interval time register
 * Input          : iit: Wait time
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetIIT(uint16_t iit)
{
    CH394Q_Write(IIT0, (uint8_t)((iit & 0xff00) >> 8));
    CH394Q_Write(IIT1, (uint8_t)(iit & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetGINT
 * Description    : Clear global interrupt flag
 * Input          : gint: Global interrupt flag
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetGINT(uint8_t gint)
{
    CH394Q_Write(GINT, gint);
}

/********************************************************************************
 * Function Name  : CH394Q_SetGINTE
 * Description    : Enable global interrupt
 * Input          : ginte: Enable a global interrupt
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetGINTE(uint8_t ginte)
{
    CH394Q_Write(GINTE, ginte);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSINTE
 * Description    : Enable socket interrupt
 * Input          : sinte: Enable a socket interrupt
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSINTE(uint8_t sinte)
{
    CH394Q_Write(SINTE, sinte);
}

/********************************************************************************
 * Function Name  : CH394Q_SetRTIME
 * Description    : Set TCP retransmission time
 * Input          : rtime: TCP retransmission time, unit time is 100us
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetRTIME(uint16_t rtime)
{
    CH394Q_Write(RTIME0, (uint8_t)((rtime & 0xff00) >> 8));
    CH394Q_Write(RTIME1, (uint8_t)(rtime & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetRCNT
 * Description    : Set TCP retransmission times
 * Input          : rcnt: TCP retransmission times
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetRCNT(uint8_t rcnt)
{
    CH394Q_Write(RCNT, rcnt);
}

/********************************************************************************
 * Function Name  : CH394Q_SetPHY_CFG
 * Description    : Set PHY configuration
 * Input          : phycfg: Configuration Mode
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetPHY_CFG(uint8_t phycfg)
{
    CH394Q_Write(PHY_CFG, phycfg);
    Delay_Ms(2);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_MODE
 * Description    : Set socket mode
 * Input          : sockindex: socket number
                    mode: Socket mode
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_MODE(uint8_t sockindex, uint8_t mode)
{
    CH394Q_WriteSafe(Sn_MODE(sockindex), mode);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_CTRL
 * Description    : Set socket control command
 * Input          : sockindex: socket number
                    ctrl: Control command
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_CTRL(uint8_t sockindex, uint8_t ctrl)
{
    CH394Q_Write(Sn_CTRL(sockindex), ctrl);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_INT
 * Description    : Clear the interrupt flag of socket n
 * Input          : sockindex: socket number
                    val: Interrupt flag
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_INT(uint8_t sockindex, uint8_t val)
{
    CH394Q_Write(Sn_INT(sockindex), val);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_PORT
 * Description    : Set socket source port
 * Input          : sockindex: socket number
                    port: Source port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_PORT(uint8_t sockindex, uint16_t port)
{
    CH394Q_WriteSafe(Sn_PORT0(sockindex), (uint8_t)((port & 0xff00) >> 8));
    CH394Q_WriteSafe(Sn_PORT1(sockindex), (uint8_t)(port & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_DMAC
 * Description    : Set socket destination MAC address
 * Input          : sockindex: socket number
                    dmac: Destination MAC address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_DMAC(uint8_t sockindex, uint8_t *dmac)
{
    CH394Q_Write(Sn_DMAC0(sockindex), dmac[0]);
    CH394Q_Write(Sn_DMAC1(sockindex), dmac[1]);
    CH394Q_Write(Sn_DMAC2(sockindex), dmac[2]);
    CH394Q_Write(Sn_DMAC3(sockindex), dmac[3]);
    CH394Q_Write(Sn_DMAC4(sockindex), dmac[4]);
    CH394Q_Write(Sn_DMAC5(sockindex), dmac[5]);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_DIP
 * Description    : Set socket destination IP address
 * Input          : sockindex: socket number
                    dip: Destination IP address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_DIP(uint8_t sockindex, uint8_t *dip)
{
    CH394Q_WriteSafe(Sn_DIP0(sockindex), dip[0]);
    CH394Q_WriteSafe(Sn_DIP1(sockindex), dip[1]);
    CH394Q_WriteSafe(Sn_DIP2(sockindex), dip[2]);
    CH394Q_WriteSafe(Sn_DIP3(sockindex), dip[3]);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_DPORT
 * Description    : Set socket destination port
 * Input          : sockindex: socket number
                    dport: Destination port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_DPORT(uint8_t sockindex, uint16_t dport)
{
    CH394Q_WriteSafe(Sn_DPORT0(sockindex), (uint8_t)((dport & 0xff00) >> 8));
    CH394Q_WriteSafe(Sn_DPORT1(sockindex), (uint8_t)(dport & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_MTU
 * Description    : Set socket maximum segmentation register
 * Input          : sockindex: socket number
                    mtu: Maximum segment size
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_MTU(uint8_t sockindex, uint16_t mtu)
{
    CH394Q_Write(Sn_MTU0(sockindex), (uint8_t)((mtu & 0xff00) >> 8));
    CH394Q_Write(Sn_MTU1(sockindex), (uint8_t)(mtu & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_TOS
 * Description    : Set socket IP service type
 * Input          : sockindex: socket number
                    tos: type of service
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_TOS(uint8_t sockindex, uint8_t tos)
{
    CH394Q_Write(Sn_TOS(sockindex), tos);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_TTL
 * Description    : Set socket IP time to live
 * Input          : sockindex: socket number
                    ttl: Time to live
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_TTL(uint8_t sockindex, uint8_t ttl)
{
    CH394Q_Write(Sn_TTL(sockindex), ttl);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_RXBUF_SIZE
 * Description    : Set socket receive buffer size
 * Input          : sockindex: socket number
                    rxbuf: Receive buffer size
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_RXBUF_SIZE(uint8_t sockindex, uint8_t rxbuf)
{
    CH394Q_Write(Sn_RXBUF_SIZE(sockindex), rxbuf);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_TXBUF_SIZE
 * Description    : Set socket send buffer size
 * Input          : sockindex: socket number
                    txbuf: Send buffer size
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_TXBUF_SIZE(uint8_t sockindex, uint8_t txbuf)
{
    CH394Q_Write(Sn_TXBUF_SIZE(sockindex), txbuf);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_TX_WR
 * Description    : Set socket send write pointer
 * Input          : sockindex: socket number
                    txwr: Send data length
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_TX_WR(uint8_t sockindex, uint16_t txwr)
{
    CH394Q_Write(Sn_TX_WR0(sockindex), (uint8_t)((txwr & 0xff00) >> 8));
    CH394Q_Write(Sn_TX_WR1(sockindex), (uint8_t)(txwr & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_RX_RD
 * Description    : Set socket receive read pointer
 * Input          : sockindex: socket number
                    rxrd: Receive data length
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_RX_RD(uint8_t sockindex, uint16_t rxrd)
{
    CH394Q_Write(Sn_RX_RD0(sockindex), (uint8_t)((rxrd & 0xff00) >> 8));
    CH394Q_Write(Sn_RX_RD1(sockindex), (uint8_t)(rxrd & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_INTE
 * Description    : Enable socket interrupt
 * Input          : sockindex: socket number
                    inte: Enable socket interrupt
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_INTE(uint8_t sockindex, uint8_t inte)
{
    CH394Q_Write(Sn_INTE(sockindex), inte);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_IPF
 * Description    : Set socket IP header fragmentation
 * Input          : sockindex: socket number
                    ipf: IP fragmentation
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_IPF(uint8_t sockindex, uint16_t ipf)
{
    CH394Q_Write(Sn_IPF0(sockindex), (uint8_t)((ipf & 0xff00) >> 8));
    CH394Q_Write(Sn_IPF1(sockindex), (uint8_t)(ipf & 0x00ff));
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_KEEPALIVE
 * Description    : Set keep a live interval
 * Input          : sockindex: socket number
                    val: Time interval (unit time is 5s)
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_KEEPALIVE(uint8_t sockindex, uint8_t val)
{
    CH394Q_Write(Sn_KEEPALIVE(sockindex), val);
}

/********************************************************************************
 * Function Name  : CH394Q_SetLLA
 * Description    : Set IPv6 local link address
 * Input          : lla: IPv6 local link address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetLLA(uint8_t *lla)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        CH394Q_Write(LLA0 + (i << 8), lla[i]);
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_SetGUA
 * Description    : Set local IPv6 global unicast address
 * Input          : gua: Local IPv6 global unicast address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetGUA(uint8_t *gua)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        CH394Q_Write(GUA0 + (i << 8), gua[i]);
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_SetGWIP6
 * Description    : Set local IPv6 gateway
 * Input          : gwip6: Local IPv6 gateway
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetGWIP6(uint8_t *gwip6)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        CH394Q_Write(GWIP60 + (i << 8), gwip6[i]);
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSUBPL
 * Description    : Set the length of the global unicast address subnet prefix comparison
 * Input          : len: Compare lengths
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSUBPL(uint8_t len)
{
    CH394Q_Set_REG_PAGE(1);
    CH394Q_Write(SUBPL, len);
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_DIP6
 * Description    : Set Socket n destination IPv6 address register
 * Input          : sockindex: socket number
                  : dip6: DestinationIPv6 address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_DIP6(uint8_t sockindex, uint8_t *dip6)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        CH394Q_Write(Sn_DIP60(sockindex) + (i << 8), dip6[i]);
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_SetSn_IPPRO
 * Description    : Set the IP protocol type
 * Input          : sockindex: socket number
                  : ippro: IP protocol type
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetSn_IPPRO(uint8_t sockindex, uint8_t ippro)
{
    CH394Q_Write(Sn_IPPRO(sockindex), ippro);
}

/********************************************************************************
 * Function Name  : CH394Q_SetICMP6BK
 * Description    : Set ICMP6 block
 * Input          : icmp6bk: ICMP6 block
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetICMP6BK(uint8_t icmp6bk)
{
    CH394Q_Set_REG_PAGE(2);
    CH394Q_Write(ICMP6BK, icmp6bk);
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_GetMODE
 * Description    : Get mode
 * Input          : None
 * Output         : None
 * Return         : Mode
 *******************************************************************************/
uint8_t CH394Q_GetMODE(void)
{
    return CH394Q_Read(MODE);
}

/********************************************************************************
 * Function Name  : CH394Q_GetGWIP
 * Description    : Get CH394Q gateway address
 * Input          : gwip: Gateway address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetGWIP(uint8_t *gwip)
{
    gwip[0] = CH394Q_Read(GWIP0);
    gwip[1] = CH394Q_Read(GWIP1);
    gwip[2] = CH394Q_Read(GWIP2);
    gwip[3] = CH394Q_Read(GWIP3);
}

/********************************************************************************
 * Function Name  : CH394Q_GetSMIP
 * Description    : Get CH394Q subnet mask address
 * Input          : smip: Subnet mask address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetSMIP(uint8_t *smip)
{
    smip[0] = CH394Q_Read(SMIP0);
    smip[1] = CH394Q_Read(SMIP1);
    smip[2] = CH394Q_Read(SMIP2);
    smip[3] = CH394Q_Read(SMIP3);
}

/********************************************************************************
 * Function Name  : CH394Q_GetMAC
 * Description    : Get CH394Q MAC address
 * Input          : mac: MAC address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetMAC(uint8_t *mac)
{
    mac[0] = CH394Q_Read(MAC0);
    mac[1] = CH394Q_Read(MAC1);
    mac[2] = CH394Q_Read(MAC2);
    mac[3] = CH394Q_Read(MAC3);
    mac[4] = CH394Q_Read(MAC4);
    mac[5] = CH394Q_Read(MAC5);
}

/********************************************************************************
 * Function Name  : CH394Q_GetIP
 * Description    : Get CH394Q source IP address
 * Input          : ip: Source IP address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetIP(uint8_t *ip)
{
    ip[0] = CH394Q_Read(IP0);
    ip[1] = CH394Q_Read(IP1);
    ip[2] = CH394Q_Read(IP2);
    ip[3] = CH394Q_Read(IP3);
}

/********************************************************************************
 * Function Name  : CH394Q_GetIIT
 * Description    : Get interrupt interval time
 * Input          : None
 * Output         : None
 * Return         : Interval time
 *******************************************************************************/
uint16_t CH394Q_GetIIT(void)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(IIT0) << 8) & 0xff00;
    i |= CH394Q_Read(IIT1) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetGINT
 * Description    : Get global interrupt status
 * Input          : None
 * Output         : None
 * Return         : Global Interrupt Status
 *******************************************************************************/
uint8_t CH394Q_GetGINT(void)
{
    return CH394Q_Read(GINT);
}

/********************************************************************************
 * Function Name  : CH394Q_GetGINTE
 * Description    : Get interrupt enable status
 * Input          : None
 * Output         : None
 * Return         : Enable interrupt status
 *******************************************************************************/
uint8_t CH394Q_GetGINTE(void)
{
    return CH394Q_Read(GINTE);
}

/********************************************************************************
 * Function Name  : CH394Q_GetSINT
 * Description    : Get socket interrupt status
 * Input          : None
 * Output         : None
 * Return         : Socket interrupt status
 *******************************************************************************/
uint8_t CH394Q_GetSINT(void)
{
    return CH394Q_Read(SINT);
}

/********************************************************************************
 * Function Name  : CH394Q_GetSINTE
 * Description    : Get enable socket interrupt status
 * Input          : None
 * Output         : None
 * Return         : Enable socket interrupt status
 *******************************************************************************/
uint8_t CH394Q_GetSINTE(void)
{
    return CH394Q_Read(SINTE);
}

/********************************************************************************
 * Function Name  : CH394Q_GetRTIME
 * Description    : Get retransmission timeout duration (unit time is 100us)
 * Input          : None
 * Output         : None
 * Return         : Retransmission timeout time
 *******************************************************************************/
uint16_t CH394Q_GetRTIME(void)
{
    uint16_t i = 0;
    i = (CH394Q_Read(RTIME0) << 8) & 0xff00;
    i |= CH394Q_Read(RTIME1) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetRCNT
 * Description    : Get retransmission count
 * Input          : None
 * Output         : None
 * Return         : Retransmission count
 *******************************************************************************/
uint8_t CH394Q_GetRCNT(void)
{
    return CH394Q_Read(RCNT);
}

/********************************************************************************
 * Function Name  : CH394Q_GetUNIP
 * Description    : Get unable to reach IP address
 * Input          : unip: Unable to reach IP address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetUNIP(uint8_t *unip)
{
    unip[0] = CH394Q_Read(UNIP0);
    unip[1] = CH394Q_Read(UNIP1);
    unip[2] = CH394Q_Read(UNIP2);
    unip[3] = CH394Q_Read(UNIP3);
}

/********************************************************************************
 * Function Name  : CH394Q_GetUNPORT
 * Description    : Get unreachable port
 * Input          : None
 * Output         : None
 * Return         : Unreachable port
 *******************************************************************************/
uint16_t CH394Q_GetUNPORT(void)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(UNPORT0) << 8) & 0xff00;
    i |= CH394Q_Read(UNPORT1) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetPHYStatus
 * Description    : Get PHY status
 * Input          : None
 * Output         : None
 * Return         : PHY status
 *******************************************************************************/
uint8_t CH394Q_GetPHYStatus(void)
{
    return CH394Q_Read(PHY_CFG);
}

/********************************************************************************
 * Function Name  : CH394Q_GetCHIPV
 * Description    : Get CH394Q version number
 * Input          : None
 * Output         : None
 * Return         : Version number
 *******************************************************************************/
uint8_t CH394Q_GetCHIPV(void)
{
    return CH394Q_Read(CHIPV);
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_MODE
 * Description    : Get socket mode
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket mode
 *******************************************************************************/
uint8_t CH394Q_GetSn_MODE(uint8_t sockindex)
{
    return CH394Q_Read(Sn_MODE(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_CTRL
 * Description    : Get socket control command status
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket control command status
 *******************************************************************************/
uint8_t CH394Q_GetSn_CTRL(uint8_t sockindex)
{
    return CH394Q_Read(Sn_CTRL(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_INT
 * Description    : Get interrupt status of socket n
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : The interrupt state of socket n
 *******************************************************************************/
uint8_t CH394Q_GetSn_INT(uint8_t sockindex)
{
    return CH394Q_Read(Sn_INT(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_STA
 * Description    : Get socket status
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket status
 *******************************************************************************/
uint8_t CH394Q_GetSn_STA(uint8_t sockindex)
{
    return CH394Q_Read(Sn_STA(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_PORT
 * Description    : Get socket source port
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket source port
 *******************************************************************************/
uint16_t CH394Q_GetSn_PORT(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_PORT0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_PORT1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_DPORT
 * Description    : Get socket destination port
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket destination port
 *******************************************************************************/
uint16_t CH394Q_GetSn_DPORT(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_DPORT0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_DPORT1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_MTU
 * Description    : Get socket maximum segment
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket maximum segment
 *******************************************************************************/
uint16_t CH394Q_GetSn_MTU(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_MTU0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_MTU1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_TOS
 * Description    : Get socket service type
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket service type
 *******************************************************************************/
uint8_t CH394Q_GetSn_TOS(uint8_t sockindex)
{
    return CH394Q_Read(Sn_TOS(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_TTL
 * Description    : Get the socket IP time to live
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket IP time to live
 *******************************************************************************/
uint8_t CH394Q_GetSn_TTL(uint8_t sockindex)
{
    return CH394Q_Read(Sn_TTL(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_RXBUF_SIZE
 * Description    : Get socket receive buffer size
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket receive buffer size
 *******************************************************************************/
uint8_t CH394Q_GetSn_RXBUF_SIZE(uint8_t sockindex)
{
    return CH394Q_Read(Sn_RXBUF_SIZE(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_TXBUF_SIZE
 * Description    : Get socket send buffer size
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket send buffer size
 *******************************************************************************/
uint8_t CH394Q_GetSn_TXBUF_SIZE(uint8_t sockindex)
{
    return CH394Q_Read(Sn_TXBUF_SIZE(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_TX_FS
 * Description    : Get socket free send buffer size
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket free send buffer size
 *******************************************************************************/
uint16_t CH394Q_GetSn_TX_FS(uint8_t sockindex)
{
    uint16_t i = 0, t = 0;
    do
    {
        t = (CH394Q_Read(Sn_TX_FS0(sockindex)) << 8) & 0xff00;
        t |= CH394Q_Read(Sn_TX_FS1(sockindex)) & 0x00ff;
        if (t != 0)
        {
            i = (CH394Q_Read(Sn_TX_FS0(sockindex)) << 8) & 0xff00;
            i |= CH394Q_Read(Sn_TX_FS1(sockindex)) & 0x00ff;
        }
    } while (i != t);
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_RX_RS
 * Description    : Get socket free receive buffer size
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket free receive buffer size
 *******************************************************************************/
uint16_t CH394Q_GetSn_RX_RS(uint8_t sockindex)
{
    uint16_t i = 0, t = 0;
    do
    {
        t = (CH394Q_Read(Sn_RX_RS0(sockindex)) << 8) & 0xff00;
        t |= CH394Q_Read(Sn_RX_RS1(sockindex)) & 0x00ff;
        if (t != 0)
        {
            i = (CH394Q_Read(Sn_RX_RS0(sockindex)) << 8) & 0xff00;
            i |= CH394Q_Read(Sn_RX_RS1(sockindex)) & 0x00ff;
        }
    } while (i != t);
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_TX_RD
 * Description    : Get socket send read pointer
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket send read pointer
 *******************************************************************************/
uint16_t CH394Q_GetSn_TX_RD(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_TX_RD0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_TX_RD1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_TX_WR
 * Description    : Get socket send write pointer
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket send write pointer
 *******************************************************************************/
uint16_t CH394Q_GetSn_TX_WR(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_TX_WR0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_TX_WR1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_RX_RD
 * Description    : Get socket receive read pointer
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket receive read pointer
 *******************************************************************************/
uint16_t CH394Q_GetSn_RX_RD(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_RX_RD0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_RX_RD1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_RX_WR
 * Description    : Get socket receive write pointer
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket receive write pointer
 *******************************************************************************/
uint16_t CH394Q_GetSn_RX_WR(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_RX_WR0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_RX_WR1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_INTE
 * Description    : Get socket n enable interrupt status
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket n enable interrupt status
 *******************************************************************************/
uint8_t CH394Q_GetSn_INTE(uint8_t sockindex)
{
    return CH394Q_Read(Sn_INTE(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_IPF
 * Description    : Get socket segment status
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket segment status
 *******************************************************************************/
uint16_t CH394Q_GetSn_IPF(uint8_t sockindex)
{
    uint16_t i = 0;
    i |= (CH394Q_Read(Sn_IPF0(sockindex)) << 8) & 0xff00;
    i |= CH394Q_Read(Sn_IPF1(sockindex)) & 0x00ff;
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_KEEPALIVE
 * Description    : Get socket keep a live transmission time (unit time is 5s)
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket keep a live transmission time
 *******************************************************************************/
uint8_t CH394Q_GetSn_KEEPALIVE(uint8_t sockindex)
{
    return CH394Q_Read(Sn_KEEPALIVE(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetLLA
 * Description    : Get local IPv6 address
 * Input          : lla: local IPv6 address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetLLA(uint8_t *lla)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        lla[i] = CH394Q_Read(LLA0 + (i << 8));
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_GetGUA
 * Description    : Get local IPv6 global unicast address
 * Input          : gua: local IPv6 global unicast address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetGUA(uint8_t *gua)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        gua[i] = CH394Q_Read(GUA0 + (i << 8));
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_GetGWIP6
 * Description    : Get local IPv6 gateway address
 * Input          : gwip6: local IPv6 gateway address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetGWIP6(uint8_t *gwip6)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        gwip6[i] = CH394Q_Read(GWIP60 + (i << 8));
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_DIP
 * Description    : Get socket destination IP
 * Input          : sockindex: socket number
                    dip: socket destination IP
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetSn_DIP(uint8_t sockindex, uint8_t *dip)
{
    dip[0] = CH394Q_Read(Sn_DIP0(sockindex));
    dip[1] = CH394Q_Read(Sn_DIP1(sockindex));
    dip[2] = CH394Q_Read(Sn_DIP2(sockindex));
    dip[3] = CH394Q_Read(Sn_DIP3(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_DMAC
 * Description    : Get socket destination MAC address
 * Input          : sockindex: socket number
                    dmac: destination MAC address
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetSn_DMAC(uint8_t sockindex, uint8_t *dmac)
{
    dmac[0] = CH394Q_Read(Sn_DMAC0(sockindex));
    dmac[1] = CH394Q_Read(Sn_DMAC1(sockindex));
    dmac[2] = CH394Q_Read(Sn_DMAC2(sockindex));
    dmac[3] = CH394Q_Read(Sn_DMAC3(sockindex));
    dmac[4] = CH394Q_Read(Sn_DMAC4(sockindex));
    dmac[5] = CH394Q_Read(Sn_DMAC5(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_DIP6
 * Description    : Get the destination IPv6 address of Socket n
 * Input          : sockindex: socket number
                  : dip6: Destination IPv6 address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetSn_DIP6(uint8_t sockindex, uint8_t *dip6)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    for (i = 0; i < 16; i++)
    {
        dip6[i] = CH394Q_Read(Sn_DIP60(sockindex) + (i << 8));
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_GetRAVLT
 * Description    : Get RA Valid Lifetime
 * Input          : None
 * Output         : None
 * Return         : RA Valid Lifetime
 *******************************************************************************/
uint32_t CH394Q_GetRAVLT(void)
{
    uint32_t vltr = 0;
    CH394Q_Set_REG_PAGE(1);
    vltr |= (uint32_t)CH394Q_Read(RAVLT0) << 24;
    vltr |= (uint32_t)CH394Q_Read(RAVLT1) << 16;
    vltr |= (uint32_t)CH394Q_Read(RAVLT2) << 8;
    vltr |= (uint32_t)CH394Q_Read(RAVLT3);
    CH394Q_Set_REG_PAGE(0);
    return vltr;
}

/********************************************************************************
 * Function Name  : CH394Q_GetRAPLT
 * Description    : Get RA Preferred Time to Live
 * Input          : None
 * Output         : None
 * Return         : RA Preferred Time to Live
 *******************************************************************************/
uint32_t CH394Q_GetRAPLT(void)
{
    uint32_t pltr = 0;
    CH394Q_Set_REG_PAGE(1);
    pltr |= (uint32_t)CH394Q_Read(RAPLT0) << 24;
    pltr |= (uint32_t)CH394Q_Read(RAPLT1) << 16;
    pltr |= (uint32_t)CH394Q_Read(RAPLT2) << 8;
    pltr |= (uint32_t)CH394Q_Read(RAPLT3);
    CH394Q_Set_REG_PAGE(0);
    return pltr;
}

/********************************************************************************
 * Function Name  : CH394Q_GetRAPL
 * Description    : Get the length of the RA prefix
 * Input          : None
 * Output         : None
 * Return         : RA prefix length
 *******************************************************************************/
uint8_t CH394Q_GetRAPL(void)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    i = CH394Q_Read(RAPL);
    CH394Q_Set_REG_PAGE(0);
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetRAPF
 * Description    : Get RA prefix flag
 * Input          : None
 * Output         : None
 * Return         : RA prefix flag
 *******************************************************************************/
uint8_t CH394Q_GetRAPF(void)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    i = CH394Q_Read(RAPF);
    CH394Q_Set_REG_PAGE(0);
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetPA
 * Description    : Get RA prefix information
 * Input          : pa: RA prefix information address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetPA(uint8_t *pa)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(2);
    for (i = 0; i < 16; i++)
    {
        pa[i] = CH394Q_Read(PA0 + (i << 8));
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_GetUNIP6
 * Description    : Get unreachable IPv6 information
 * Input          : unip: Unreachable IPv6 address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GetUNIP6(uint8_t *unip)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(2);
    for (i = 0; i < 16; i++)
    {
        unip[i] = CH394Q_Read(UNIP60 + (i << 8));
    }
    CH394Q_Set_REG_PAGE(0);
}

/********************************************************************************
 * Function Name  : CH394Q_GetUNPORT6
 * Description    : Get unreachable IPv6 port
 * Input          : None
 * Output         : None
 * Return         : Unreachable IPv6 port
 *******************************************************************************/
uint16_t CH394Q_GetUNPORT6(void)
{
    uint16_t uport6r = 0;
    CH394Q_Set_REG_PAGE(2);
    uport6r |= (uint16_t)CH394Q_Read(UNPORT60) << 8;
    uport6r |= (uint16_t)CH394Q_Read(UNPORT61);
    CH394Q_Set_REG_PAGE(0);
    return uport6r;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSUBPL
 * Description    : Get the comparison length of the subnet prefix of the set global unicast address
 * Input          : None
 * Output         : None
 * Return         : Compare lengths
 *******************************************************************************/
uint8_t CH394Q_GetSUBPL(void)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    i = CH394Q_Read(SUBPL);
    CH394Q_Set_REG_PAGE(0);
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetICMP6BK
 * Description    : Get ICMP6 block
 * Input          : None
 * Output         : None
 * Return         : ICMP6 block
 *******************************************************************************/
uint8_t CH394Q_GetICMP6BK(void)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(2);
    i = CH394Q_Read(ICMP6BK);
    CH394Q_Set_REG_PAGE(0);
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_GetSn_ESR
 * Description    : Get Socket n extension status
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : Extended state
 *******************************************************************************/
uint8_t CH394Q_GetSn_ESR(uint8_t sockindex)
{
    uint8_t i = 0;
    CH394Q_Set_REG_PAGE(1);
    i = CH394Q_Read(Sn_ESR(sockindex));
    CH394Q_Set_REG_PAGE(0);
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_SocketSendData
 * Description    : socket send data
 * Input          : sockindex: socket number
                    buf: Send data buffer
                    len: Data length
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SocketSendData(uint8_t sockindex, uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;
    uint32_t address = 0;
    i = CH394Q_GetSn_TX_WR(sockindex);
    address = (uint32_t)(i << 8) + (sockindex << 5) + 0x10;
    CH394Q_WriteBuf(address, buf, len);
    i += len;
    CH394Q_SetSn_TX_WR(sockindex, i);
}

/********************************************************************************
 * Function Name  : CH394Q_SocketRecvData
 * Description    : socket receive data
 * Input          : sockindex: socket number
                    buf: Receive data buffer
                    len: Data length
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SocketRecvData(uint8_t sockindex, uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;
    uint32_t address = 0;
    i = CH394Q_GetSn_RX_RD(sockindex);
    address = (uint32_t)(i << 8) + (sockindex << 5) + 0x18;
    CH394Q_ReadBuf(address, buf, len);
    i += len;
    CH394Q_SetSn_RX_RD(sockindex, i);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_RECV);
    while (CH394Q_GetSn_CTRL(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_SocketTCPSend
 * Description    : Send data in TCP mode
 * Input          : sockindex: socket number
                    buf: Send data buffer
                    len: Data length
 * Output         : None
 * Return         : Send successful return data length, fail return 0
 *******************************************************************************/
uint16_t CH394Q_SocketTCPSend(uint8_t sockindex, const uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;
    uint16_t ferrbuf = 0;
    uint8_t Sn_STA_state = CH394Q_GetSn_STA(sockindex);
    if (len > CH394Q_GetTxMax(sockindex))
    {
        i = CH394Q_GetTxMax(sockindex);
    }
    else i = len;
    while (ferrbuf < i)
    {
        ferrbuf = CH394Q_GetSn_TX_FS(sockindex);
        Sn_STA_state = CH394Q_GetSn_STA(sockindex);
        if ((Sn_STA_state != SOCK_TCP_ESTABLISHED) && (Sn_STA_state != SOCK_CLOSE_WAIT))
        {
            printf("err\r\n");
            return 0;
        }
    }
    CH394Q_SocketSendData(sockindex, (uint8_t *)buf, i);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_SEND);
    while (CH394Q_GetSn_CTRL(sockindex));
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_SocketTCPRecv
 * Description    : Receive data in TCP mode
 * Input          : sockindex: socket number
                    buf: Receive data buffer
                    len: Data length
 * Output         : None
 * Return         : Return data length
 *******************************************************************************/
uint16_t CH394Q_SocketTCPRecv(uint8_t sockindex, uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;
    if (len > 0)
    {
        CH394Q_SocketRecvData(sockindex, buf, len);
        i = len;
    }
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_SocketUDPSendTo
 * Description    : Send data in UDP mode
 * Input          : sockindex: socket number
                    buf: Send data buffer
                    len: Data length
                    desip: destination IP address
                    desport: destination port
 * Output         : None
 * Return         : data length
 *******************************************************************************/
uint16_t CH394Q_SocketSendTo(uint8_t sockindex, const uint8_t *buf, uint16_t len, uint8_t *desip, uint16_t desport)
{
    uint16_t i = 0;
    uint16_t ferrbuf = 0;
    uint8_t Sn_STA_state = CH394Q_GetSn_STA(sockindex);
    if (len > CH394Q_GetTxMax(sockindex))
    {
        i = CH394Q_GetTxMax(sockindex);
    }
    else i = len;
    while (ferrbuf < i)
    {
        ferrbuf = CH394Q_GetSn_TX_FS(sockindex);
    }
    CH394Q_SetSn_DIP(sockindex, desip);
    CH394Q_SetSn_DPORT(sockindex, desport);
    CH394Q_SocketSendData(sockindex, (uint8_t *)buf, i);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_SEND);
    while (CH394Q_GetSn_CTRL(sockindex));
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_UDP_Recv
 * Description    : IPv4 mode and IPv6 mode UDP receive data
 * Input          : sockindex: socket number
                    buf: Receive data buffer
                    len: Data length
                    desip: Destination IP address
                    desport: Destination Port
                    flag: IPv4 or IPv6 flag
 * Output         : None
 * Return         : Data length
 *******************************************************************************/
uint16_t CH394Q_Socket_UDP_Recv(uint8_t sockindex, uint8_t *buf, uint16_t len, uint8_t *desip, uint16_t *desport, uint8_t *flag)
{
    uint8_t msg[20];
    uint16_t data_len = 0;
    if (len > 0)
    {
#if IPv6_MODE
        CH394Q_SocketRecvData(sockindex, msg, 2);
        if ((msg[0] & 0x80) == 0) // IPv4 mode
        {
            *flag = 0; // IPv4 flag
            data_len = ((msg[0] & 0x07) << 8) + msg[1];
            CH394Q_SocketRecvData(sockindex, msg, 6);
            desip[0] = msg[0];
            desip[1] = msg[1];
            desip[2] = msg[2];
            desip[3] = msg[3];
            *desport = msg[4];
            *desport = (*desport << 8) + msg[5];
            CH394Q_SocketRecvData(sockindex, buf, data_len);
        }
        else
        {
            uint8_t i = 0;
            *flag = 1; // IPv6 mode and flag
            data_len = ((msg[0] & 0x07) << 8) + msg[1];
            CH394Q_SocketRecvData(sockindex, msg, 18);
            for (i = 0; i < 16; i++)
            {
                desip[i] = msg[i];
            }
            *desport = msg[16];
            *desport = (*desport << 8) + msg[17];
            CH394Q_SocketRecvData(sockindex, buf, data_len);
        }
#else
        CH394Q_SocketRecvData(sockindex, msg, 0x08);
        desip[0] = msg[0];
        desip[1] = msg[1];
        desip[2] = msg[2];
        desip[3] = msg[3];
        *desport = msg[4];
        *desport = (*desport << 8) + msg[5];
        data_len = msg[6];
        data_len = (data_len << 8) + msg[7];
        CH394Q_SocketRecvData(sockindex, buf, data_len);
#endif
    }
    return data_len;
}
/********************************************************************************
 * Function Name  : CH394Q_Socket_MACRAW_Send
 * Description    : Send data in MACRAW mode
 * Input          : sockindex: socket number
                    buf: Send data buffer
                    len: Data length
 * Output         : None
 * Return         : data length
 *******************************************************************************/
uint16_t CH394Q_Socket_MACRAW_Send(uint8_t sockindex, const uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;
    uint16_t ferrbuf = 0;
    uint8_t Sn_STA_state = CH394Q_GetSn_STA(sockindex);
    if (len > CH394Q_GetTxMax(sockindex))
    {
        i = CH394Q_GetTxMax(sockindex);
    }
    else i = len;
    while (ferrbuf < i)
    {
        ferrbuf = CH394Q_GetSn_TX_FS(sockindex);
    }
    CH394Q_SocketSendData(sockindex, (uint8_t *)buf, i);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_SEND);
    while (CH394Q_GetSn_CTRL(sockindex));
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_MACRAW_Recv
 * Description    : Receive data in MACRAW mode
 * Input          : sockindex: socket number
                    buf: Receive data buffer
                    len: Data length
 * Output         : None
 * Return         : Send successful return data length, fail return 0
 *******************************************************************************/
uint16_t CH394Q_Socket_MACRAW_Recv(uint8_t sockindex, uint8_t *buf, uint16_t len)
{
    uint8_t msg[2];
    uint16_t data_len = 0;
    uint8_t socket_mode = CH394Q_GetSn_MODE(sockindex);
    if (len > 0)
    {
        if (socket_mode & Sn_MODE_MACRAW)
        {
            CH394Q_SocketRecvData(sockindex, msg, 0x02);
            data_len = msg[0];
            data_len = (data_len << 8) + msg[1] - 2;
            if (data_len > 1514)
            {
                CH394Q_SocketRecvData(sockindex, buf, len - 2);
                printf(" The received data length is more than 1514\r\n");
                return 0;
            }
            CH394Q_SocketRecvData(sockindex, buf, data_len);
        }
    }
    return data_len;
}

/********************************************************************************
 * Function Name  : CH394Q_SocketSendMAC
 * Description    : Use the send_mac command to send data
 * Input          : sockindex: socket number
                    buf: Send data buffer
                    len: Data length
                    desmac: Destination MAC address
                    desip: Destination IP address
                    desport: Destination Port
 * Output         : None
 * Return         : Data length
 *******************************************************************************/
uint16_t CH394Q_SocketSendMAC(uint8_t sockindex, const uint8_t *buf, uint16_t len, uint8_t *desmac, uint8_t *desip, uint16_t desport)
{
    uint16_t i = 0;
    uint16_t ferrbuf = 0;
    uint8_t Sn_STA_state = CH394Q_GetSn_STA(sockindex);
    if (len > CH394Q_GetTxMax(sockindex))
    {
        i = CH394Q_GetTxMax(sockindex);
    }
    else i = len;
    while (ferrbuf < i)
    {
        ferrbuf = CH394Q_GetSn_TX_FS(sockindex);
    }
    CH394Q_SetSn_DMAC(sockindex, desmac);
    CH394Q_SetSn_DIP(sockindex, desip);
    CH394Q_SetSn_DPORT(sockindex, desport);
    CH394Q_SocketSendData(sockindex, (uint8_t *)buf, i);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_SEND_MAC);
    while (CH394Q_GetSn_CTRL(sockindex));
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_SocketSendTo_v6
 * Description    : UDP IPv6 mode send data
 * Input          : sockindex: socket number
                    buf: Send data buffer
                    len: Data length
                    desip: Destination IP address
                    desport: Destination Port
 * Output         : None
 * Return         : Data length
 *******************************************************************************/
uint16_t CH394Q_SocketSendTo_v6(uint8_t sockindex, const uint8_t *buf, uint16_t len, uint8_t *desip, uint16_t desport)
{
    uint16_t i = 0;
    uint16_t ferrbuf = 0;
    uint8_t Sn_STA_state = CH394Q_GetSn_STA(sockindex);
    if (len > CH394Q_GetTxMax(sockindex))
    {
        i = CH394Q_GetTxMax(sockindex);
    }
    else i = len;
    while (ferrbuf < i)
    {
        ferrbuf = CH394Q_GetSn_TX_FS(sockindex);
    }
    CH394Q_SetSn_DIP6(sockindex, desip);
    CH394Q_SetSn_DPORT(sockindex, desport);
    CH394Q_SocketSendData(sockindex, (uint8_t *)buf, i);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_SEND6);
    while (CH394Q_GetSn_CTRL(sockindex));
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_IPRAW6_Send
 * Description    : IPv6 IPRAW mode send
 * Input          : sockindex: socket number
                    buf: Send data buffer
                    len: Data length
                    desip: Destination IP address
 * Output         : None
 * Return         : Data length
 *******************************************************************************/
uint16_t CH394Q_Socket_IPRAW6_Send(uint8_t sockindex, const uint8_t *buf, uint16_t len, uint8_t *desip)
{
    uint16_t i = 0;
    uint16_t ferrbuf = 0;
    uint8_t Sn_STA_state = CH394Q_GetSn_STA(sockindex);
    if (len > CH394Q_GetTxMax(sockindex))
    {
        i = CH394Q_GetTxMax(sockindex);
    }
    else i = len;
    while (ferrbuf < i)
    {
        ferrbuf = CH394Q_GetSn_TX_FS(sockindex);
    }
    CH394Q_SetSn_DIP6(sockindex, desip);
    CH394Q_SocketSendData(sockindex, (uint8_t *)buf, i);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_SEND6);
    while (CH394Q_GetSn_CTRL(sockindex));
    return i;
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_IPRAW6_Recv
 * Description    : IPv6 IPRAW mode receive
 * Input          : sockindex: socket number
                    buf: Receive data buffer
                    len: Data length
                    desip: Destination IP address
 * Output         : None
 * Return         : Data length
 *******************************************************************************/
uint16_t CH394Q_Socket_IPRAW6_Recv(uint8_t sockindex, uint8_t *buf, uint16_t len, uint8_t *desip)
{
    uint8_t i = 0;
    uint8_t msg[18];
    uint16_t data_len = 0;
    uint8_t socket_mode = CH394Q_GetSn_MODE(sockindex);
    if (len > 0)
    {
        CH394Q_SocketRecvData(sockindex, msg, 2);
        if (socket_mode & Sn_MODE_IPRAW6)
        {
            data_len = ((msg[0] & 0x07) << 8) + msg[1];
            CH394Q_SocketRecvData(sockindex, msg, 16);
            for (i = 0; i < 16; i++)
            {
                desip[i] = msg[i];
            }
            CH394Q_SocketRecvData(sockindex, buf, data_len);
        }
    }
    return data_len;
}

/********************************************************************************
 * Function Name  : CH394Q_GetRxMax
 * Description    : Get socket n maximum receive buffer
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket n maximum receive buffer
 *******************************************************************************/
uint16_t CH394Q_GetRxMax(uint8_t sockindex)
{
    return RX_BUFF[sockindex] * 1024;
}

/********************************************************************************
 * Function Name  : CH394Q_GetTxMax
 * Description    : Get socket n maximum send buffer
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : socket n max send buffer
 *******************************************************************************/
uint16_t CH394Q_GetTxMax(uint8_t sockindex)
{
    return TX_BUFF[sockindex] * 1024;
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_Init
 * Description    : CH394Q socket initialization
 * Input          : sockindex: socket number
                    mode: socket mode
                    port: Source Port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_Socket_Init(uint8_t sockindex, uint8_t mode, uint16_t port)
{
    uint16_t t;
    CH394Q_Socket_Close(sockindex);
    CH394Q_SetSn_MODE(sockindex, mode);
    if (port != 0)
    {
        CH394Q_SetSn_PORT(sockindex, port);
    }
    else
    {
        t = 8000 + sockindex;
        CH394Q_SetSn_PORT(sockindex, t);
    }
    CH394Q_Socket_Open(sockindex);
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_Open
 * Description    : Open socket
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_Socket_Open(uint8_t sockindex)
{
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_OPEN);
    while (CH394Q_GetSn_CTRL(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_Close
 * Description    : Close socket
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_Socket_Close(uint8_t sockindex)
{
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_CLOSE);
    while (CH394Q_GetSn_CTRL(sockindex));
    CH394Q_SetSn_INT(sockindex, 0xFF);
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_Listen
 * Description    : Open listening
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_Socket_Listen(uint8_t sockindex)
{
    if (CH394Q_GetSn_STA(sockindex) == SOCK_INIT)
    {
        CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_LISTEN);
        while (CH394Q_GetSn_CTRL(sockindex));
    }
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_Connect
 * Description    : Establish connection
 * Input          : sockindex: socket number
                    desip: Destination server address
                    desport: Destination server port
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_Socket_Connect(uint8_t sockindex, uint8_t *desip, uint16_t desport)
{
    CH394Q_SetSn_DIP(sockindex, desip);
    CH394Q_SetSn_DPORT(sockindex, desport);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_CONNECT);
    while (CH394Q_GetSn_CTRL(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_Connect6
 * Description    : IPv6 IPRAW mode receive
 * Input          : sockindex: socket number
                    desip: Destination IP address
                    desport: Destination Port
 * Output         : None
 * Return         : Data length
 *******************************************************************************/
void CH394Q_Socket_Connect6(uint8_t sockindex, uint8_t *desip, uint16_t desport)
{
    CH394Q_SetSn_DIP6(sockindex, desip);
    CH394Q_SetSn_DPORT(sockindex, desport);
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_CONNECT6);
    while (CH394Q_GetSn_CTRL(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_Socket_Disconnect
 * Description    : socket disconnect
 * Input          : sockindex: socket number
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_Socket_Disconnect(uint8_t sockindex)
{
    CH394Q_SetSn_CTRL(sockindex, Sn_CTRL_DISCONNECT);
    while (CH394Q_GetSn_CTRL(sockindex));
}

/********************************************************************************
 * Function Name  : CH394Q_SocketBuf_Init
 * Description    : Initialize socket receive and send buffer size
 * Input          : tx_size: Set send buffer size
                    rx_size: Set receive buffer size
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SocketBuf_Init(uint8_t *tx_size, uint8_t *rx_size)
{
    uint16_t i;
    for (i = 0; i < SOCKET_NUM; i++)
    {
        TX_BUFF[i] = tx_size[i];
        CH394Q_SetSn_TXBUF_SIZE(i, tx_size[i]);
    }
    for (i = 0; i < SOCKET_NUM; i++)
    {
        RX_BUFF[i] = rx_size[i];
        CH394Q_SetSn_RXBUF_SIZE(i, rx_size[i]);
    }
    Delay_Ms(1);
}

/********************************************************************************
 * Function Name  : CH394Q_PHY_Check
 * Description    : PHY connection check
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_PHY_Check(void)
{
    uint8_t PHY_state = 0;
    while (1)
    {
        PHY_state = CH394Q_GetPHYStatus();
        if ((PHY_state & 0x01) == 0)
        {
            Delay_Ms(500);
        }
        else
        {
            printf(" Link up..\r\n");
            break;
        }
    }
}

/********************************************************************************
 * Function Name  : CH394Q_ResetSW
 * Description    : CH394Q software reset
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_ResetSW(void)
{
    CH394Q_SetMODE(MODE_RST);
    Delay_Ms(500);
}

/********************************************************************************
 * Function Name  : CH394Q_GPIO_Init
 * Description    : CH394Q GPIO initialization
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_GPIO_Init(void)
{
    CH394Q_SCS_HIGH();
}

/********************************************************************************
 * Function Name  : CH394Q_ResetHW
 * Description    : CH394Q hardware reset via RSTB pin
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_ResetHW(void)
{
}

/********************************************************************************
 * Function Name  : CH394Q_SetCHIP_CONFIG
 * Description    : Switch firmware mode
 * Input          : config: Switch mode
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_SetCHIP_CONFIG(uint8_t config)
{
    CH394Q_Write(CHIP_CONFIG, config);
    while (!CH394Q_Read(CHIP_CONFIG));
}

/********************************************************************************
 * Function Name  : CH394Q_GetCHIP_CONFIG
 * Description    : Get the firmware mode
 * Input          : None
 * Output         : None
 * Return         : Firmware mode
 *******************************************************************************/
uint8_t CH394Q_GetCHIP_CONFIG(void)
{
    return CH394Q_Read(CHIP_CONFIG);
}

/********************************************************************************
 * Function Name  : CH394Q_Set_REG_PAGE
 * Description    : Select the page register
 * Input          : page: Page register
 * Output         : None
 * Return         : None
 *******************************************************************************/
void CH394Q_Set_REG_PAGE(uint8_t page)
{
    CH394Q_Write(REG_PAGE, page);
    while (CH394Q_Get_REG_PAGE() != page);
}

/********************************************************************************
 * Function Name  : CH394Q_Get_REG_PAGE
 * Description    : Get the page
 * Input          : None
 * Output         : None
 * Return         : Current page
 *******************************************************************************/
uint8_t CH394Q_Get_REG_PAGE(void)
{
    return CH394Q_Read(REG_PAGE);
}

/********************************************************************************
 * Function Name  : CH394Q_Compare_PA
 * Description    : Compare subnet prefixes
 * Input          : par_1: Subnet prefix 1
                  : par_2: Subnet prefix 2
 * Output         : None
 * Return         : 0 different, 1 same
 *******************************************************************************/
uint8_t CH394Q_Compare_PA(uint8_t *par_1, uint8_t *par_2)
{
    uint8_t i = 0;
    for (i = 0; i < 8; i++)
    {
        if (par_1[i] != par_2[i]) return 0;
    }
    return 1;
}

/********************************************************************************
 * Function Name  : print_ipv6_addr
 * Description    : Print IPv6 format address
 * Input          : addr: Address pointer
 * Output         : None
 * Return         : None
 *******************************************************************************/
void print_ipv6_addr(uint8_t *addr)
{
    int i, skip = 0;
    for (i = 0; i < 16; i += 2)
    {
        if (!skip && i <= 12 && addr[i] == 0 && addr[i + 1] == 0 && addr[i + 2] == 0 && addr[i + 3] == 0)
        {
            printf("::");
            skip = 1;
            i += 2;
						while (i < 14 && addr[i + 2] == 0 && addr[i + 3] == 0) i += 2;
        }
        else
        {
            if (i > 0 && !((i - 2) <= 12 && addr[i - 2] == 0 && addr[i - 1] == 0))
						printf(":");
            printf("%x", (addr[i] << 8) | addr[i + 1]);
        }
    }
    printf("\n");
}
