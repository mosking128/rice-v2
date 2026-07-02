#ifndef CH394Q_SPI_H_
#define CH394Q_SPI_H_

#include "main.h"
#include "debug.h"

#define SPI_MODE      1
#define SPI_DMA_MODE  0

#define IPv6_MODE     0

#define CH394Q_SCS_LOW()   HAL_GPIO_WritePin(CH394Q_SCS_GPIO_Port, CH394Q_SCS_Pin, GPIO_PIN_RESET)
#define CH394Q_SCS_HIGH()  HAL_GPIO_WritePin(CH394Q_SCS_GPIO_Port, CH394Q_SCS_Pin, GPIO_PIN_SET)
#define Execute_IPv6()     Delay_Us(1)

void CH394Q_SPIPort_Init(void);
void DMA_Tx_Init(void *DMA_CHx, uint32_t ppadr);
void DMA_Rx_Init(void *DMA_CHx, uint32_t ppadr);
void SPIWriteCH394QData(uint8_t mdata);
uint8_t SPIReadCH394QData(void);

void CH394Q_Write(uint32_t addr, uint8_t data);
void CH394Q_WriteSafe(uint32_t addr, uint8_t data);
uint8_t CH394Q_Read(uint32_t addr);
uint16_t CH394Q_WriteBuf(uint32_t addr, uint8_t *buf, uint16_t len);
uint16_t CH394Q_ReadBuf(uint32_t addr, uint8_t *buf, uint16_t len);

#endif
