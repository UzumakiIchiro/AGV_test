/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define TOUCH_SCK_Pin GPIO_PIN_2
#define TOUCH_SCK_GPIO_Port GPIOE
#define TOUCH_MISO_Pin GPIO_PIN_5
#define TOUCH_MISO_GPIO_Port GPIOE
#define TOUCH_MOSI_Pin GPIO_PIN_6
#define TOUCH_MOSI_GPIO_Port GPIOE
#define ANALOG_VOLTAGE_Pin GPIO_PIN_0
#define ANALOG_VOLTAGE_GPIO_Port GPIOB
#define ANALOG_CURENT_Pin GPIO_PIN_1
#define ANALOG_CURENT_GPIO_Port GPIOB
#define LCD_BACKLED_Pin GPIO_PIN_11
#define LCD_BACKLED_GPIO_Port GPIOE
#define MCU_O8_Pin GPIO_PIN_12
#define MCU_O8_GPIO_Port GPIOE
#define MCU_O9_Pin GPIO_PIN_13
#define MCU_O9_GPIO_Port GPIOE
#define MCU_O6_Pin GPIO_PIN_14
#define MCU_O6_GPIO_Port GPIOE
#define MCU_O7_Pin GPIO_PIN_15
#define MCU_O7_GPIO_Port GPIOE
#define MCU_O4_Pin GPIO_PIN_14
#define MCU_O4_GPIO_Port GPIOB
#define MCU_O5_Pin GPIO_PIN_15
#define MCU_O5_GPIO_Port GPIOB
#define MCU_O2_Pin GPIO_PIN_8
#define MCU_O2_GPIO_Port GPIOD
#define MCU_O3_Pin GPIO_PIN_9
#define MCU_O3_GPIO_Port GPIOD
#define MCU_O0_Pin GPIO_PIN_10
#define MCU_O0_GPIO_Port GPIOD
#define MCU_O1_Pin GPIO_PIN_11
#define MCU_O1_GPIO_Port GPIOD
#define EXT_LOAD_Pin GPIO_PIN_2
#define EXT_LOAD_GPIO_Port GPIOG
#define EXT_CLk_Pin GPIO_PIN_3
#define EXT_CLk_GPIO_Port GPIOG
#define HC595_CLK_Pin GPIO_PIN_4
#define HC595_CLK_GPIO_Port GPIOG
#define HC595_LATC_Pin GPIO_PIN_5
#define HC595_LATC_GPIO_Port GPIOG
#define HC595_DATA_Pin GPIO_PIN_6
#define HC595_DATA_GPIO_Port GPIOG
#define EXT_SO_Pin GPIO_PIN_7
#define EXT_SO_GPIO_Port GPIOG
#define TLV5620_DATA_Pin GPIO_PIN_6
#define TLV5620_DATA_GPIO_Port GPIOC
#define TLV5620_LDAC_Pin GPIO_PIN_8
#define TLV5620_LDAC_GPIO_Port GPIOA
#define TLV5620_CLK_Pin GPIO_PIN_15
#define TLV5620_CLK_GPIO_Port GPIOA
#define MT_LEFT_RB_Pin GPIO_PIN_11
#define MT_LEFT_RB_GPIO_Port GPIOC
#define TLV5620_LOAD_Pin GPIO_PIN_12
#define TLV5620_LOAD_GPIO_Port GPIOC
#define MT_RIGHT_RB_Pin GPIO_PIN_2
#define MT_RIGHT_RB_GPIO_Port GPIOD
#define SD_DetectCard_Pin GPIO_PIN_13
#define SD_DetectCard_GPIO_Port GPIOG
#define LED_4_Pin GPIO_PIN_14
#define LED_4_GPIO_Port GPIOG
#define LED_3_Pin GPIO_PIN_15
#define LED_3_GPIO_Port GPIOG
#define LED_2_Pin GPIO_PIN_3
#define LED_2_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_4
#define LED_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
