/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH394Q.h
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2025/07/01
 * Description        : CH394Q application program header file
 *******************************************************************************/
#ifndef  _CH394Q_H_
#define  _CH394Q_H_

#define SOCKET_NUM 8

#define MODE                        (0x000000)  /* Mode register */
#define GWIP0                       (0x000100)  /* Gateway address register */
#define GWIP1                       (0x000200)
#define GWIP2                       (0x000300)
#define GWIP3                       (0x000400)

#define SMIP0                       (0x000500)  /* Subnet mask register */
#define SMIP1                       (0x000600)
#define SMIP2                       (0x000700)
#define SMIP3                       (0x000800)

#define MAC0                        (0x000900)  /* Source MAC address register */
#define MAC1                        (0x000A00)
#define MAC2                        (0x000B00)
#define MAC3                        (0x000C00)
#define MAC4                        (0x000D00)
#define MAC5                        (0x000E00)

#define IP0                         (0x000F00)  /* Source IP address register */
#define IP1                         (0x001000)
#define IP2                         (0x001100)
#define IP3                         (0x001200)

#define IIT0                        (0x001300)  /* Interrupt interval time register */
#define IIT1                        (0x001400)
#define GINT                        (0x001500)  /* Global interrupt register */
#define GINTE                       (0x001600)  /* Global interrupt enable register */
#define SINT                        (0x001700)  /* socket interrupt register */
#define SINTE                       (0x001800)  /* socket interrupt enable register */
#define RTIME0                      (0x001900)  /* Retransmission timeout register (unit value: 100us) */
#define RTIME1                      (0x001A00)
#define RCNT                        (0x001B00)  /* Retransmission counter register */

#define UNIP0                       (0x002800)  /* Unable to reach IP address register */
#define UNIP1                       (0x002900)
#define UNIP2                       (0x002A00)
#define UNIP3                       (0x002B00)

#define UNPORT0                     (0x002C00)  /* Unable to reach port register */
#define UNPORT1                     (0x002D00)
#define PHY_CFG                     (0x002E00)  /* PHY configuration register */
#define CHIPV                       (0x003900)  /* Chip version register */
#define Sn_MODE(s)                  (0x000008 + (s<<5))  /* Socket n mode register */
#define Sn_CTRL(s)                  (0x000108 + (s<<5))  /* Socket n control register */
#define Sn_INT(s)                   (0x000208 + (s<<5))  /* Socket n interrupt register */
#define Sn_STA(s)                   (0x000308 + (s<<5))  /* Socket n status register */
#define Sn_PORT0(s)                 (0x000408 + (s<<5))  /* Socket n source port register */
#define Sn_PORT1(s)                 (0x000508 + (s<<5))

#define Sn_DMAC0(s)                 (0x000608 + (s<<5))  /* Socket n destination MAC address register */
#define Sn_DMAC1(s)                 (0x000708 + (s<<5))
#define Sn_DMAC2(s)                 (0x000808 + (s<<5))
#define Sn_DMAC3(s)                 (0x000908 + (s<<5))
#define Sn_DMAC4(s)                 (0x000A08 + (s<<5))
#define Sn_DMAC5(s)                 (0x000B08 + (s<<5))

#define Sn_DIP0(s)                  (0x000C08 + (s<<5))  /* Socket destination IP address register */
#define Sn_DIP1(s)                  (0x000D08 + (s<<5))
#define Sn_DIP2(s)                  (0x000E08 + (s<<5))
#define Sn_DIP3(s)                  (0x000F08 + (s<<5))

#define Sn_DPORT0(s)                (0x001008 + (s<<5))  /* Socket n destination port register */
#define Sn_DPORT1(s)                (0x001108 + (s<<5))
#define Sn_MTU0(s)                  (0x001208 + (s<<5))  /* Socket n maximum segment register */
#define Sn_MTU1(s)                  (0x001308 + (s<<5))
#define Sn_TOS(s)                   (0x001508 + (s<<5))  /* Socket IP service type register */
#define Sn_TTL(s)                   (0x001608 + (s<<5))  /* Socket IP time to live register */
#define Sn_RXBUF_SIZE(s)            (0x001E08 + (s<<5))  /* Socket n receive buffer size register */
#define Sn_TXBUF_SIZE(s)            (0x001F08 + (s<<5))  /* Socket n send buffer size register */
#define Sn_TX_FS0(s)                (0x002008 + (s<<5))  /* Socket n free send buffer register */
#define Sn_TX_FS1(s)                (0x002108 + (s<<5))
#define Sn_TX_RD0(s)                (0x002208 + (s<<5))  /* Socket n send read pointer register */
#define Sn_TX_RD1(s)                (0x002308 + (s<<5))
#define Sn_TX_WR0(s)                (0x002408 + (s<<5))  /* Socket n send write pointer register */
#define Sn_TX_WR1(s)                (0x002508 + (s<<5))
#define Sn_RX_RS0(s)                (0x002608 + (s<<5))  /* Socket n free receive buffer register */
#define Sn_RX_RS1(s)                (0x002708 + (s<<5))
#define Sn_RX_RD0(s)                (0x002808 + (s<<5))  /* Socket n receive pointer register */
#define Sn_RX_RD1(s)                (0x002908 + (s<<5))
#define Sn_RX_WR0(s)                (0x002A08 + (s<<5))  /* Socket n receive write pointer register */
#define Sn_RX_WR1(s)                (0x002B08 + (s<<5))
#define Sn_INTE(s)                  (0x002C08 + (s<<5))  /* Socket n interrupt enable register */
#define Sn_IPF0(s)                  (0x002D08 + (s<<5))  /* Socket n segment register */
#define Sn_IPF1(s)                  (0x002E08 + (s<<5))
#define Sn_KEEPALIVE(s)             (0x002F08 + (s<<5))  /* Socket online time register */

/* Mode register */
#define MODE_RST                     0x80     /* Internal register reset */
#define MODE_WOL                     0x20     /* Wake on LAN */
#define MODE_PB                      0x10     /* Ping packet blocking enabled */
#define MODE_UDP_FARP                0x02     /* Enable forced ARP */
/* Global Interrupt Register */
#define GINT_IP_CONFLI               0x80     /* IP conflict */
#define GINT_UNREACH                 0x40     /* Destination port unreachable */
#define GINT_MP                      0x10     /* Magic packet interrupt */

/* Page 0 - GINT Interrupt Register */
#define GINT_UNREACH6                0x20     /* IPv6 destination port unreachable */
#define GINT_RA                      0x08     /* RA */
#define GINT_IPv6_CONFLI             0x04     /* IPv6 conflict */

/* Socket n mode register */
#define Sn_MODE_CLOSE                0x00     /* socket not used */
#define Sn_MODE_TCP                  0x01     /* TCP mode */
#define Sn_MODE_UDP                  0x02     /* UDP mode */
#define Sn_MODE_MACRAW               0x04     /* MACRAW mode */
#define Sn_MODE_UCASTB               0x10     /* Unicast filtering */
#define Sn_MODE_MIP6B                0x10     /* MACRAW mode enable IPv6 packet filtering */
#define Sn_MODE_NA                   0x20     /* Enable no delay ACK */
#define Sn_MODE_MV                   0x20     /* Multicast uses IGMP version 1 */
#define Sn_MODE_MM                   0x20     /* Enable multicast filtering in MACRAW mode */
#define Sn_MODE_BCASTB               0x40     /* Enable broadcast filtering */
#define Sn_MODE_MUL                  0x80     /* Enable multicast */
#define Sn_MODE_MFEN                 0x80     /* Enable MAC address filtering in MACRAW mode */
/* Socket n control register */
#define Sn_CTRL_OPEN                 0x01     /* Open socket n */
#define Sn_CTRL_LISTEN               0x02     /* Listening, waiting for connections as TCP server mode */
#define Sn_CTRL_CONNECT              0x04     /* Connect, initiate a connection request in TCP client mode */
#define Sn_CTRL_DISCONNECT           0x08     /* Disconnect */
#define Sn_CTRL_CLOSE                0x10     /* Close socket n*/
#define Sn_CTRL_SEND                 0x20     /* Update send buffer pointer, send data */
#define Sn_CTRL_SEND_MAC             0x21     /* The set destination MAC address is automatically used when sending data, and the destination MAC address is obtained without ARP */
#define Sn_CTRL_SEND_KEEP            0x22     /* Send a 1 byte keep a live packet to check connection status */
#define Sn_CTRL_RECV                 0x40     /* Update receive buffer pointer, receive data */
/* Socket n interrupt register */
#define Sn_INT_SEND_SUC              0x10     /* Send */
#define Sn_INT_TIMEOUT               0x08     /* Timeout */
#define Sn_INT_RECV                  0x04     /* Receive */
#define Sn_INT_DISCONNECT            0x02     /* Disconnect */
#define Sn_INT_CONNECT               0x01     /* Establish connection */
/* Socket n status register */
#define SOCK_CLOSE                   0x00     /* Closed state */
#define SOCK_INIT                    0x13     /* Initialization state */
#define SOCK_LISTEN                  0x14     /* listening state */
#define SOCK_SYN_SENT                0x15     /* Send connection request packet to the destination */
#define SOCK_SYN_RECV                0x16     /* Received connection request packet */
#define SOCK_TCP_ESTABLISHED         0x17     /* Established connection successfully */
#define SOCK_FIN_WAIT                0x18
#define SOCK_CLOSING                 0x1A
#define SOCK_TIME_WAIT               0x1B
#define SOCK_CLOSE_WAIT              0x1C
#define SOCK_LAST_ACK                0x1D
#define SOCK_UDP                     0x22     /* In UDP mode */
#define SOCK_MACRAW                  0x42     /* In MACRAW mode */

/***********************   Page register   *************************************************/
//Page 0 register
#define CHIP_CONFIG                 (0x003E00)  /*Page 0 - Switch to v6 firmware*/
#define REG_PAGE                    (0x003F00)  /*Page 0 - Register page switch*/
//Page 1 register
#define LLA0                        (0x000000)  /*Page 1 - IPv6 local link address*/
#define LLA1                        (0x000100)
#define LLA2                        (0x000200)
#define LLA3                        (0x000300)
#define LLA4                        (0x000400)
#define LLA5                        (0x000500)
#define LLA6                        (0x000600)
#define LLA7                        (0x000700)
#define LLA8                        (0x000800)
#define LLA9                        (0x000900)
#define LLA10                       (0x000A00)
#define LLA11                       (0x000B00)
#define LLA12                       (0x000C00)
#define LLA13                       (0x000D00)
#define LLA14                       (0x000E00)
#define LLA15                       (0x000F00)

#define GUA0                        (0x001000)  /*Page 1 - IPv6 global unicast address*/
#define GUA1                        (0x001100)
#define GUA2                        (0x001200)
#define GUA3                        (0x001300)
#define GUA4                        (0x001400)
#define GUA5                        (0x001500)
#define GUA6                        (0x001600)
#define GUA7                        (0x001700)
#define GUA8                        (0x001800)
#define GUA9                        (0x001900)
#define GUA10                       (0x001A00)
#define GUA11                       (0x001B00)
#define GUA12                       (0x001C00)
#define GUA13                       (0x001D00)
#define GUA14                       (0x001E00)
#define GUA15                       (0x001F00)

#define GWIP60                      (0x002000)  /*Page 1 - IPv6 gateway*/
#define GWIP61                      (0x002100)
#define GWIP62                      (0x002200)
#define GWIP63                      (0x002300)
#define GWIP64                      (0x002400)
#define GWIP65                      (0x002500)
#define GWIP66                      (0x002600)
#define GWIP67                      (0x002700)
#define GWIP68                      (0x002800)
#define GWIP69                      (0x002900)
#define GWIP610                     (0x002A00)
#define GWIP611                     (0x002B00)
#define GWIP612                     (0x002C00)
#define GWIP613                     (0x002D00)
#define GWIP614                     (0x002E00)
#define GWIP615                     (0x002F00)

#define RAVLT0                      (0x003000)  /*Page 1 - RA-Effective Lifetime*/
#define RAVLT1                      (0x003100)
#define RAVLT2                      (0x003200)
#define RAVLT3                      (0x003300)

#define RAPLT0                      (0x003400)  /*Page 1 - RA-Preferred Lifetime*/
#define RAPLT1                      (0x003500)
#define RAPLT2                      (0x003600)
#define RAPLT3                      (0x003700)

#define RAPL                        (0x003800)  /*Page 1 - RA - Prefix length*/
#define RAPF                        (0x003900)  /*Page 1 - RA - Prefix flag*/
#define SUBPL                       (0x003a00)  /*Page 1 - Subnet prefix length, directly compared to GUA, static length*/
//Page 2 register
#define PA0                         (0x000000)  /*Page 2 - RA - Prefix information*/
#define PA1                         (0x000100)
#define PA2                         (0x000200)
#define PA3                         (0x000300)
#define PA4                         (0x000400)
#define PA5                         (0x000500)
#define PA6                         (0x000600)
#define PA7                         (0x000700)
#define PA8                         (0x000800)
#define PA9                         (0x000900)
#define PA10                        (0x000A00)
#define PA11                        (0x000B00)
#define PA12                        (0x000C00)
#define PA13                        (0x000D00)
#define PA14                        (0x000E00)
#define PA15                        (0x000F00)

#define UNIP60                      (0x002000)  /*Page 2 - Unreachable IPv6*/
#define UNIP61                      (0x002100)
#define UNIP62                      (0x002200)
#define UNIP63                      (0x002300)
#define UNIP64                      (0x002400)
#define UNIP65                      (0x002500)
#define UNIP66                      (0x002600)
#define UNIP67                      (0x002700)
#define UNIP68                      (0x002800)
#define UNIP69                      (0x002900)
#define UNIP610                     (0x002A00)
#define UNIP611                     (0x002B00)
#define UNIP612                     (0x002C00)
#define UNIP613                     (0x002D00)
#define UNIP614                     (0x002E00)
#define UNIP615                     (0x002F00)

#define UNPORT60                    (0x003000)  /*Page 2 - Unreachable IPv6 port*/
#define UNPORT61                    (0x003100)
#define ICMP6BK                     (0x003200)  /*Page 2 - ICMPv6 blocking*/
//Page 0 socket register
//Sn_MODE
#define Sn_MODE_TCPD                 0x0D  //TCP dual protocol supporting IPv4 and IPv6
#define Sn_MODE_UDPD                 0x0E  //UDP Double (UDPD) mode supporting IPv4 and IPv6
#define Sn_MODE_TCP6                 0x09  //Only supports IPv6
#define Sn_MODE_UDP6                 0x0A  //Only supports IPv6
#define Sn_MODE_IPRAW6               0x0B  //Only supports IPv6
//Sn_CTRL
#define Sn_CTRL_CONNECT6             0x84  //Connect to TCP server with IPv6 target IP
#define Sn_CTRL_SEND6                0xA0  //IPv6 send
//Sn_STA
#define Sn_STA_IPRAW6                0x33  //Only supports IPv6

#define Sn_IPPRO(s)                 (0x001408 + (s<<5))  //socket IP type register
//Page 1 socket register
#define Sn_DIP60(s)                 (0x000008 + (s<<5))  /*Page 1 - Socket n peer IP register*/
#define Sn_DIP61(s)                 (0x000108 + (s<<5))
#define Sn_DIP62(s)                 (0x000208 + (s<<5))
#define Sn_DIP63(s)                 (0x000308 + (s<<5))
#define Sn_DIP64(s)                 (0x000408 + (s<<5))
#define Sn_DIP65(s)                 (0x000508 + (s<<5))
#define Sn_DIP66(s)                 (0x000608 + (s<<5))
#define Sn_DIP67(s)                 (0x000708 + (s<<5))
#define Sn_DIP68(s)                 (0x000808 + (s<<5))
#define Sn_DIP69(s)                 (0x000908 + (s<<5))
#define Sn_DIP610(s)                (0x000A08 + (s<<5))
#define Sn_DIP611(s)                (0x000B08 + (s<<5))
#define Sn_DIP612(s)                (0x000C08 + (s<<5))
#define Sn_DIP613(s)                (0x000D08 + (s<<5))
#define Sn_DIP614(s)                (0x000E08 + (s<<5))
#define Sn_DIP615(s)                (0x000F08 + (s<<5))
#define Sn_ESR(s)                   (0x001008 + (s<<5))  /*Page 1 - Socket n extension status register*/

/*********************************************************
* CH394 access function
*********************************************************/
void CH394Q_SetMODE(uint8_t mode);

void CH394Q_SetGWIP(uint8_t * gwip);

void CH394Q_SetSMIP(uint8_t * smip);

void CH394Q_SetMAC(uint8_t * mac);

void CH394Q_SetIP(uint8_t * ip);

void CH394Q_SetIIT(uint16_t iit);

void CH394Q_SetGINT(uint8_t gint);

void CH394Q_SetGINTE(uint8_t ginte);

void CH394Q_SetSINTE(uint8_t sinte);

void CH394Q_SetRTIME(uint16_t rtime);

void CH394Q_SetRCNT(uint8_t rcnt);

void CH394Q_SetPHY_CFG(uint8_t phycfg);

void CH394Q_SetSn_MODE(uint8_t sockindex, uint8_t mode);

void CH394Q_SetSn_CTRL(uint8_t sockindex, uint8_t ctrl);

void CH394Q_SetSn_INT(uint8_t sockindex, uint8_t val);

void CH394Q_SetSn_PORT(uint8_t sockindex, uint16_t port);

void CH394Q_SetSn_DMAC(uint8_t sockindex, uint8_t * dmac);

void CH394Q_SetSn_DIP(uint8_t sockindex, uint8_t * dip);

void CH394Q_SetSn_DPORT(uint8_t sockindex, uint16_t dport);

void CH394Q_SetSn_MTU(uint8_t sockindex, uint16_t mtu);

void CH394Q_SetSn_TOS(uint8_t sockindex, uint8_t tos);

void CH394Q_SetSn_TTL(uint8_t sockindex, uint8_t ttl);

void CH394Q_SetSn_RXBUF_SIZE(uint8_t sockindex, uint8_t rxbuf);

void CH394Q_SetSn_TXBUF_SIZE(uint8_t sockindex, uint8_t txbuf);

void CH394Q_SetSn_TX_WR(uint8_t sockindex, uint16_t txwr);

void CH394Q_SetSn_RX_RD(uint8_t sockindex, uint16_t rxrd);

void CH394Q_SetSn_INTE(uint8_t sockindex, uint8_t inte);

void CH394Q_SetSn_IPF(uint8_t sockindex, uint16_t ipf);

void CH394Q_SetSn_KEEPALIVE(uint8_t sockindex,uint8_t val);

void CH394Q_SetLLA(uint8_t * lla);

void CH394Q_SetGUA(uint8_t * gua);

void CH394Q_SetGWIP6(uint8_t * gwip6);

void CH394Q_SetSUBPL(uint8_t len);

void CH394Q_SetSn_DIP6(uint8_t sockindex , uint8_t * dip6);

void CH394Q_SetSn_IPPRO(uint8_t sockindex, uint8_t ippro);

void CH394Q_SetICMP6BK(uint8_t icmp6bk);

uint8_t CH394Q_GetMODE(void);

void CH394Q_GetGWIP(uint8_t * gwip);

void CH394Q_GetSMIP(uint8_t * smip);

void CH394Q_GetMAC(uint8_t * mac);

void CH394Q_GetIP(uint8_t * ip);

uint16_t CH394Q_GetIIT(void);

uint8_t  CH394Q_GetGINT( void );

uint8_t  CH394Q_GetGINTE( void );

uint8_t  CH394Q_GetSINT( void );

uint8_t  CH394Q_GetSINTE( void );

uint16_t CH394Q_GetRTIME( void );

uint8_t  CH394Q_GetRCNT( void );

void CH394Q_GetUNIP(uint8_t * unip);

uint16_t CH394Q_GetUNPORT( void );

uint8_t  CH394Q_GetPHYStatus( void );

uint8_t  CH394Q_GetCHIPV(void);

uint8_t  CH394Q_GetSn_MODE(uint8_t sockindex);

uint8_t  CH394Q_GetSn_CTRL(uint8_t sockindex);

uint8_t  CH394Q_GetSn_INT(uint8_t sockindex);

uint8_t  CH394Q_GetSn_STA(uint8_t sockindex);

uint16_t CH394Q_GetSn_PORT(uint8_t sockindex);

uint16_t CH394Q_GetSn_DPORT(uint8_t sockindex);

uint16_t CH394Q_GetSn_MTU(uint8_t sockindex);

uint8_t  CH394Q_GetSn_TOS(uint8_t sockindex);

uint8_t  CH394Q_GetSn_TTL(uint8_t sockindex);

uint8_t  CH394Q_GetSn_RXBUF_SIZE(uint8_t sockindex);

uint8_t  CH394Q_GetSn_TXBUF_SIZE(uint8_t sockindex);

uint16_t CH394Q_GetSn_TX_FS(uint8_t sockindex);

uint16_t CH394Q_GetSn_RX_RS(uint8_t sockindex);

uint16_t CH394Q_GetSn_TX_RD(uint8_t sockindex);

uint16_t CH394Q_GetSn_TX_WR(uint8_t sockindex);

uint16_t CH394Q_GetSn_RX_RD(uint8_t sockindex);

uint16_t CH394Q_GetSn_RX_WR(uint8_t sockindex);

uint8_t  CH394Q_GetSn_INTE(uint8_t sockindex);

uint16_t CH394Q_GetSn_IPF(uint8_t sockindex);

uint8_t  CH394Q_GetSn_KEEPALIVE(uint8_t sockindex);

void CH394Q_GetLLA(uint8_t * lla);

void CH394Q_GetGUA(uint8_t * gua);

void CH394Q_GetGWIP6(uint8_t * gwip6);

void CH394Q_GetSn_DIP(uint8_t sockindex, uint8_t * dip);

void CH394Q_GetSn_DMAC(uint8_t sockindex, uint8_t * dmac);

void CH394Q_GetSn_DIP6(uint8_t sockindex , uint8_t * dip6);

uint32_t CH394Q_GetRAVLT(void);

uint32_t CH394Q_GetRAPLT(void);

uint8_t CH394Q_GetRAPL(void);

uint8_t CH394Q_GetRAPF(void);

void CH394Q_GetPA(uint8_t * pa);

void CH394Q_GetUNIP6(uint8_t * unip);

uint16_t CH394Q_GetUNPORT6(void);

uint8_t CH394Q_GetSUBPL(void);

uint8_t CH394Q_GetICMP6BK(void);

uint8_t CH394Q_GetSn_ESR(uint8_t sockindex);

void CH394Q_SocketSendData(uint8_t sockindex, uint8_t *buf, uint16_t len);

void CH394Q_SocketRecvData(uint8_t sockindex, uint8_t *buf, uint16_t len);

uint16_t CH394Q_SocketTCPSend(uint8_t sockindex, const uint8_t * buf, uint16_t len);

uint16_t CH394Q_SocketTCPRecv(uint8_t sockindex, uint8_t * buf, uint16_t len);

uint16_t CH394Q_SocketSendTo(uint8_t sockindex, const uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t port);

uint16_t CH394Q_Socket_UDP_Recv(uint8_t sockindex, uint8_t * buf, uint16_t len, uint8_t * desip, uint16_t *desport, uint8_t *flag);

uint16_t CH394Q_Socket_MACRAW_Send(uint8_t sockindex, const uint8_t * buf, uint16_t len);

uint16_t CH394Q_Socket_MACRAW_Recv(uint8_t sockindex, uint8_t * buf, uint16_t len);

uint16_t CH394Q_SocketSendMAC(uint8_t sockindex, const uint8_t * buf, uint16_t len, uint8_t * desmac, uint8_t * desip, uint16_t desport);

uint16_t CH394Q_SocketSendTo_v6(uint8_t sockindex, const uint8_t * buf, uint16_t len, uint8_t * desip, uint16_t desport);

uint16_t CH394Q_Socket_IPRAW6_Send(uint8_t sockindex, const uint8_t * buf, uint16_t len, uint8_t * desip);

uint16_t CH394Q_Socket_IPRAW6_Recv(uint8_t sockindex, uint8_t * buf, uint16_t len, uint8_t * desip);

uint16_t CH394Q_GetRxMax(uint8_t sockindex);

uint16_t CH394Q_GetTxMax(uint8_t sockindex);

void CH394Q_Socket_Init(uint8_t sockindex, uint8_t mode, uint16_t port);

void CH394Q_Socket_Open(uint8_t sockindex);

void CH394Q_Socket_Close(uint8_t sockindex);

void CH394Q_Socket_Listen(uint8_t sockindex);

void CH394Q_Socket_Connect(uint8_t sockindex, uint8_t * desip, uint16_t desport);

void CH394Q_Socket_Connect6(uint8_t sockindex, uint8_t * desip, uint16_t desport);

void CH394Q_Socket_Disconnect(uint8_t sockindex);

void CH394Q_SocketBuf_Init( uint8_t * tx_size, uint8_t * rx_size);

void CH394Q_GPIO_Init(void);

void CH394Q_PHY_Check(void);

void CH394Q_ResetHW(void);

void CH394Q_ResetSW(void);

void CH394Q_SetCHIP_CONFIG(uint8_t config);

uint8_t CH394Q_GetCHIP_CONFIG(void);

void CH394Q_Set_REG_PAGE(uint8_t page);

uint8_t CH394Q_Get_REG_PAGE(void);

uint8_t CH394Q_Compare_PA(uint8_t * par_1,uint8_t * par_2);

void print_ipv6_addr(uint8_t *addr);

#endif
