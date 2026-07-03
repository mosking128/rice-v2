/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CH394Q_NET.h"
#include "serial_app.h"
#include <string.h>
#include "picoc_app.h"
#include "task_msg.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* REMOVED: defaultTask no longer needed */
/*osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};*/
/* Definitions for serialTask */
osThreadId_t serialTaskHandle;
const osThreadAttr_t serialTask_attributes = {
  .name = "serialTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for picocTask */
osThreadId_t picocTaskHandle;
const osThreadAttr_t picocTask_attributes = {
  .name = "picocTask",
  .stack_size = 8192 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for udpTask */
osThreadId_t udpTaskHandle;
const osThreadAttr_t udpTask_attributes = {
  .name = "udpTask",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for uartQuene */
osMessageQueueId_t uartQueneHandle;
const osMessageQueueAttr_t uartQuene_attributes = {
  .name = "uartQuene"
};
/* Definitions for udpQuene */
osMessageQueueId_t udpQueneHandle;
const osMessageQueueAttr_t udpQuene_attributes = {
  .name = "udpQuene"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/*void StartDefaultTask(void *argument);*/
void StartSerialTask(void *argument);
void StartPicocTask(void *argument);
void StartUdpTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  SerialApp_InitMutex();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of uartQuene */
  uartQueneHandle = osMessageQueueNew (16, sizeof(TaskMsg), &uartQuene_attributes);
  /* creation of udpQuene */
  udpQueneHandle = osMessageQueueNew (16, sizeof(TaskMsg), &udpQuene_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* REMOVED: defaultTask no longer needed */
  /*defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);*/

  /* creation of serialTask */
  serialTaskHandle = osThreadNew(StartSerialTask, NULL, &serialTask_attributes);

  /* creation of udpTask */
  udpTaskHandle = osThreadNew(StartUdpTask, NULL, &udpTask_attributes);

  /* creation of picocTask */
  picocTaskHandle = osThreadNew(StartPicocTask, NULL, &picocTask_attributes);
  vTaskSuspend(picocTaskHandle);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
/*void StartDefaultTask(void *argument)
{
  for(;;)
  {
    osDelay(1);
  }
}*/

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the serialTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartSerialTask(void *argument)
{
  /* USER CODE BEGIN StartSerialTask */
  uint8_t buf[256];
  TaskMsg msg;
  (void)argument;
  for(;;)
  {
    ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(10));
    /* picocTask 在调试循环中直接消费输入，serialTask 让出 */
    if (g_console_input_active)
      continue;
    /* 排空 rx_ring：一次性读完所有数据 */
    for (;;)
    {
      uint32_t len = SerialApp_Read(buf, sizeof(buf));
      if (len == 0U)
      {
        /* 无数据时触发延迟提示符检查 */
        (void)PicocApp_ProcessChars(buf, 0U, &msg);
        break;
      }
      if (PicocApp_ProcessChars(buf, len, &msg) != 0)
      {
        switch (msg.type)
        {
          case MSG_UDP_LINE:
            if (udpQueneHandle != NULL)
              (void)osMessageQueuePut(udpQueneHandle, &msg, 0U, 0U);
            break;
          case MSG_RICE_ENABLE:
            g_active_channel = IO_CHANNEL_SERIAL;
            PicocApp_ActivateRice();
            if (picocTaskHandle != NULL)
              vTaskResume(picocTaskHandle);
            break;
          default:
            (void)osMessageQueuePut(uartQueneHandle, &msg, 0U, 0U);
            break;
        }
      }
    }
  }
  /* USER CODE END StartSerialTask */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the picocTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartPicocTask(void *argument)
{
  /* USER CODE BEGIN StartPicocTask */
  TaskMsg msg;
  (void)argument;
  for(;;)
  {
    if (osMessageQueueGet(uartQueneHandle, &msg, NULL, osWaitForever) == osOK)
    {
      switch (msg.type)
      {
        case MSG_SOURCE_LINE:
          PicocApp_RunSourceLine(msg.data);
          break;
        case MSG_LOAD_BEGIN:
          /* mode already transitioned by serialTask */
          break;
        case MSG_LOAD_END:
          PicocApp_ExecuteLoadSource();
          break;
        case MSG_LOAD_ABORT:
          /* load already cancelled by serialTask */
          break;
        case MSG_RESET:
          PicocApp_Reset();
          break;
        default:
          break;
      }
    }
  }
  /* USER CODE END StartPicocTask */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the udpTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartUdpTask(void *argument)
{
  /* USER CODE BEGIN StartUdpTask */
  TaskMsg msg;
  uint8_t rxbuf[256];
  /* 本地行缓冲：桥接模式转发 + 非活跃模式扫描切换命令 + :Rice 检测 */
  uint8_t scan_buf[64];
  uint32_t scan_len = 0U;
  uint8_t scan_last_cr = 0U;
  (void)argument;

  for(;;)
  {
    /* 1. 发送待发的 UDP 输出行 */
    while (udpQueneHandle != NULL && osMessageQueueGet(udpQueneHandle, &msg, NULL, 0U) == osOK)
    {
      if (msg.type == MSG_UDP_LINE && msg.len > 0U)
      {
        msg.data[msg.len] = '\0';
        CH394Q_UDPSendData(0, (const uint8_t *)msg.data, msg.len);
      }
    }

    /* 2. 轮询 CH394Q 接收 UDP 数据 */
    if (HAL_GPIO_ReadPin(CH394Q_INT_GPIO_Port, CH394Q_INT_Pin) == GPIO_PIN_RESET)
    {
      if (CH394Q_GetSn_INT(0) & Sn_INT_RECV)
      {
        CH394Q_SetSn_INT(0, Sn_INT_RECV);
        {
          uint16_t rxlen = CH394Q_GetSn_RX_RS(0);
          uint8_t flag = 0U;
          uint16_t srcport = 0U;
          uint8_t srcip[16];
          uint16_t got = CH394Q_Socket_UDP_Recv(0, rxbuf, rxlen, srcip, &srcport, &flag);
          if (got > 0U)
          {
            rxbuf[got] = '\0';
            DebugChannel_SetSender(srcip, srcport);

            /* === State A: UDP 活跃 + 调试模式 — 喂入调试环形缓冲区 === */
            if (g_active_channel == IO_CHANNEL_UDP && g_console_input_active)
            {
              DebugChannel_UdpInputWrite(rxbuf, got);
              DebugChannel_UdpInputWrite((const uint8_t *)"\r\n", 2U);
            }
            /* === State B: UDP 活跃 + 正常 REPL/LOAD — 注入 rx_ring 由 serialTask 统一解析 === */
            else if (g_active_channel == IO_CHANNEL_UDP)
            {
              SerialApp_InjectData(rxbuf, got);
              SerialApp_InjectData((const uint8_t *)"\r\n", 2U);
            }
            /* === State C: 桥接模式 — 转发UDP→串口，扫描 :Rice（无需换行符） === */
            else if (PicocApp_GetMode() == PICOC_APP_MODE_BRIDGE)
            {
              uint8_t rice_found = 0U;
              /* 扫描 :Rice（可能在数据任意位置，无需等待换行） */
              for (uint16_t i = 0U; i + 5U <= got; i++)
              {
                if (rxbuf[i] == ':' && memcmp(&rxbuf[i], ":Rice", 5U) == 0)
                {
                  rice_found = 1U;
                  g_active_channel = IO_CHANNEL_UDP;
                  g_debug_channel = DEBUG_CHANNEL_UDP;
                  PicocApp_ActivateRice();
                  if (picocTaskHandle != NULL)
                    vTaskResume(picocTaskHandle);
                  /* 回应 :Rice 发送方（走 UDP） */
                  {
                    const char *resp = ":ok rice\r\n";
                    TaskMsg rmsg;
                    rmsg.type = MSG_UDP_LINE;
                    rmsg.len = (uint16_t)strlen(resp);
                    memcpy(rmsg.data, resp, rmsg.len + 1U);
                    if (udpQueneHandle != NULL)
                      (void)osMessageQueuePut(udpQueneHandle, &rmsg, 0U, 0U);
                  }
                  break;
                }
              }
              /* 未命中 :Rice 才转发到串口（命中后通道已切换为UDP，不应再写串口） */
              if (rice_found == 0U)
              {
                SerialApp_Write(rxbuf, got);
                SerialApp_Write((const uint8_t *)"\r\n", 2U);
              }
              /* 清空行缓冲 */
              scan_len = 0U;
              scan_last_cr = 0U;
            }
            /* === State D: 串口活跃（UDP非活跃）— 行扫描 :debug udp === */
            else
            {
              for (uint16_t i = 0U; i < got; i++)
              {
                uint8_t ch = rxbuf[i];
                if (ch == '\r' || ch == '\n')
                {
                  if (ch == '\n' && scan_last_cr) { scan_last_cr = 0U; continue; }
                  scan_last_cr = (ch == '\r') ? 1U : 0U;

                  if (scan_len > 0U)
                  {
                    scan_buf[scan_len] = '\0';
                    uint32_t start = 0U;
                    while (start < scan_len && (scan_buf[start] == ' ' || scan_buf[start] == '\t'))
                      start++;
                    if (scan_len - start >= 10U &&
                        memcmp(&scan_buf[start], ":debug udp", 10U) == 0)
                    {
                      PicocApp_SetDebugChannelMode(DEBUG_CHANNEL_UDP);
                      PicocApp_SendResponse(":ok debug udp\r\n");
                    }
                  }
                  scan_len = 0U;
                  continue;
                }
                scan_last_cr = 0U;
                if (scan_len < sizeof(scan_buf) - 1U)
                  scan_buf[scan_len++] = ch;
              }
            }
          }
        }
      }
      CH394Q_GlobalInterrupt();
    }

    /* 3. UDP 活跃时周期性触发延迟提示符（每次循环安全，ShowPrompt 会清 g_prompt_pending） */
    if (g_active_channel == IO_CHANNEL_UDP && !g_console_input_active)
    {
      TaskMsg dummy;
      (void)PicocApp_ProcessChars(rxbuf, 0U, &dummy);
    }

    osDelay(1);
  }
  /* USER CODE END StartUdpTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
