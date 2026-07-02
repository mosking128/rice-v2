/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    debug.h
  * @brief   UART printf and delay helpers for the CH394Q demo.
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef __DEBUG_H
#define __DEBUG_H

#include "main.h"
#include <stdio.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

void Delay_Init(void);
void Delay_Us(uint32_t n);
void Delay_Ms(uint32_t n);
void USART_Printf_Init(uint32_t baudrate);

#endif
