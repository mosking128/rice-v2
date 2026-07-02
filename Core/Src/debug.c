/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    debug.c
  * @brief   UART printf and delay helpers for the CH394Q demo.
  ******************************************************************************
  */
/* USER CODE END Header */

#include "debug.h"
#include "usart.h"
#include "serial_app.h"

static uint32_t fac_us = 0;

void Delay_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    fac_us = HAL_RCC_GetHCLKFreq() / 1000000U;
}

void Delay_Us(uint32_t n)
{
    if (fac_us == 0)
    {
        Delay_Init();
    }
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = n * fac_us;
    while ((DWT->CYCCNT - start) < ticks)
    {
    }
}

void Delay_Ms(uint32_t n)
{
    HAL_Delay(n);
}

void USART_Printf_Init(uint32_t baudrate)
{
    (void)baudrate;
    Delay_Init();
}

int fputc(int ch, FILE *f)
{
    uint8_t byte = (uint8_t)ch;
    (void)f;
    SerialApp_Write(&byte, 1U);
    return ch;
}
