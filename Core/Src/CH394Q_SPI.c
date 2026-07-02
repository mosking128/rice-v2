#include "CH394Q_SPI.h"
#include "spi.h"

void CH394Q_SPIPort_Init(void)
{
    CH394Q_SCS_HIGH();
}

void DMA_Tx_Init(void *DMA_CHx, uint32_t ppadr)
{
    (void)DMA_CHx;
    (void)ppadr;
}

void DMA_Rx_Init(void *DMA_CHx, uint32_t ppadr)
{
    (void)DMA_CHx;
    (void)ppadr;
}

static uint8_t SPI1_WriteRead(uint8_t data)
{
    uint8_t rx = 0;
    HAL_SPI_TransmitReceive(&hspi4, &data, &rx, 1, HAL_MAX_DELAY);
    return rx;
}

void SPIWriteCH394QData(uint8_t mdata)
{
    (void)SPI1_WriteRead(mdata);
}

uint8_t SPIReadCH394QData(void)
{
    return SPI1_WriteRead(0x00);
}

void CH394Q_Write(uint32_t addr, uint8_t data)
{
    CH394Q_SCS_LOW();
    SPIWriteCH394QData((addr & 0x00ff0000) >> 16);
    SPIWriteCH394QData((addr & 0x0000ff00) >> 8);
    SPIWriteCH394QData((addr & 0x000000f8) + 4);
    SPIWriteCH394QData(data);
    CH394Q_SCS_HIGH();
    Execute_IPv6();
}

void CH394Q_WriteSafe(uint32_t addr, uint8_t data)
{
    CH394Q_Write(addr, 0x00);
    CH394Q_Write(addr, data);
}

uint8_t CH394Q_Read(uint32_t addr)
{
    uint8_t data = 0;
    CH394Q_SCS_LOW();
    SPIWriteCH394QData((addr & 0x00ff0000) >> 16);
    SPIWriteCH394QData((addr & 0x0000ff00) >> 8);
    SPIWriteCH394QData((addr & 0x000000f8));
    data = SPIReadCH394QData();
    CH394Q_SCS_HIGH();
    return data;
}

uint16_t CH394Q_WriteBuf(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;
    CH394Q_SCS_LOW();
    SPIWriteCH394QData((addr & 0x00ff0000) >> 16);
    SPIWriteCH394QData((addr & 0x0000ff00) >> 8);
    SPIWriteCH394QData((addr & 0x000000f8) + 4);
    for (i = 0; i < len; i++)
    {
        SPIWriteCH394QData(buf[i]);
    }
    CH394Q_SCS_HIGH();
    return len;
}

uint16_t CH394Q_ReadBuf(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i = 0;
    CH394Q_SCS_LOW();
    SPIWriteCH394QData((addr & 0x00ff0000) >> 16);
    SPIWriteCH394QData((addr & 0x0000ff00) >> 8);
    SPIWriteCH394QData((addr & 0x000000f8));
    for (i = 0; i < len; i++)
    {
        buf[i] = SPIReadCH394QData();
    }
    CH394Q_SCS_HIGH();
    return len;
}
