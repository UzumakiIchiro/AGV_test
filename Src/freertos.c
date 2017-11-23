/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "gpio.h"
#include "sdmmc.h"
#include "fatfs.h"
#include "rtc.h"

#include "AGV_Followline.h"
#include "IO.h"
#include "AGVConfig.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId taskInputHandle;
osThreadId TaskSDHandle;

/* USER CODE BEGIN Variables */
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef DateToUpdate;
	uint8_t Second;
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Date;
	uint8_t Day;
	uint8_t Month;
	uint8_t Year;	
	
	uint8_t RS485_data[200];
	uint8_t RS485_datasize = 5;
	uint16_t RS485_timeout = 1000;

extern IO_output OUTPUT;
extern AGVValue AGV;
extern IO_input  INPUT;

uint8_t flag;

extern uint8_t _isSDCard;
extern uint8_t retSD;    /* Return value for SD */
extern char SDPath[4];   /* SD logical drive path */
extern FATFS SDFatFS;    /* File system object for SD logical drive */
extern FIL SDFile;       /* File object for SD */
extern FRESULT fress;

		FATFS fatfs;
		FIL myfile;
		FRESULT fres;

extern UART_HandleTypeDef huart7;

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void StarttaskInput(void const * argument);
void StartTaskSD(void const * argument);

extern void MX_FATFS_Init(void);
extern void MX_LWIP_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */
void StarttaskSDCard(void const * argument);
void StarttaskRS485(void const * argument);
void StarttaskFollowline(void const * argument);
/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of taskInput */
  osThreadDef(taskInput, StarttaskInput, osPriorityNormal, 0, 128);
  taskInputHandle = osThreadCreate(osThread(taskInput), NULL);

  /* definition and creation of TaskSD */
  osThreadDef(TaskSD, StartTaskSD, osPriorityNormal, 0, 1024);
  TaskSDHandle = osThreadCreate(osThread(TaskSD), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	osThreadDef(TaskFL, StarttaskFollowline, osPriorityNormal, 0, 128);
  TaskSDHandle = osThreadCreate(osThread(TaskFL), NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{
  /* init code for FATFS */
  MX_FATFS_Init();

  /* init code for LWIP */
  MX_LWIP_Init();

  /* USER CODE BEGIN StartDefaultTask */
	
  /* Infinite loop */
  for(;;)
  {

		
//		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
//		HAL_RTC_GetDate(&hrtc,&DateToUpdate,RTC_FORMAT_BIN);
//		Second=sTime.Seconds;
//		Minute=sTime.Minutes;
//		Hour=sTime.Hours;
//		Day=DateToUpdate.Date;
//		Date=DateToUpdate.WeekDay;
//		Month=DateToUpdate.Month;
//		Year=DateToUpdate.Year;
		
		//HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* StarttaskInput function */
void StarttaskInput(void const * argument)
{
  /* USER CODE BEGIN StarttaskInput */
  /* Infinite loop */
	uint8_t i;
  for(;;)
  {
		IO_Inputupdate();
		IO_outputupdate();
  }
  /* USER CODE END StarttaskInput */
}

/* StartTaskSD function */
void StartTaskSD(void const * argument)
{
  /* USER CODE BEGIN StartTaskSD */
  /* Infinite loop */
	
  for(;;)
  {
		osDelay(10000);
    if(BSP_SD_Init() == MSD_OK)
		{
			
			fres = f_mount(&fatfs,"",1);
			fres = f_open(&myfile,"Config.agv",FA_CREATE_ALWAYS|FA_WRITE);
			f_printf(&myfile,"Bui Manh Can /r/nAGV v4.0.0");
			
			fres = f_close(&myfile);
			osDelay(1000);
		}
		
//			}
    osDelay(1);
  }
  /* USER CODE END StartTaskSD */
}

/* USER CODE BEGIN Application */
void StarttaskSDCard(void const * argument)
{
  for(;;)
  {
		if(!HAL_GPIO_ReadPin(SD_DetectCard_GPIO_Port, SD_DetectCard_Pin))
		{
			if(!_isSDCard)
			{
				if(BSP_SD_Init() == MSD_OK) 
				{
					taskENTER_CRITICAL();
					fres = f_mount(&SDFatFS, (TCHAR const*)SDPath, 1);
//					fres = f_mkfs((TCHAR const*)SDPath, 0, 0);
					fres = f_open(&SDFile,"config.agv",FA_CREATE_ALWAYS|FA_WRITE);
					taskEXIT_CRITICAL();
					f_printf(&SDFile,"Configuration File - AGV v4.0.0\r\n");
					f_close(&SDFile);
					HAL_GPIO_WritePin(LED_3_GPIO_Port,LED_3_Pin,1);
					_isSDCard = TRUE;
				}
				else 
				{
					HAL_GPIO_WritePin(LED_3_GPIO_Port,LED_3_Pin,0);
					_isSDCard = FALSE;
					osDelay(2000);
				}
			}
		}
		else
		{
			HAL_GPIO_WritePin(LED_3_GPIO_Port,LED_3_Pin,0);
			_isSDCard = FALSE;
		}
		osDelay(1);
  }
}

void StarttaskRS485(void const * argument)
{
  for(;;)
  {
//			if(HAL_UART_Receive_IT(&huart7, RS485_data, RS485_datasize) == HAL_OK)
//			{
//				if(HAL_UART_Transmit_IT(&huart7, &RS485_data[0], RS485_datasize) == HAL_OK)
//				{
//					HAL_GPIO_TogglePin(LED_2_GPIO_Port,LED_2_Pin);
//				}
//			}

  }
}

void StarttaskFollowline(void const * argument)
{
  for(;;)
  {
		FollowLine_Control();
  }
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
