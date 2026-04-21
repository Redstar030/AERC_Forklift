/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M2_BIN1_Pin GPIO_PIN_2
#define M2_BIN1_GPIO_Port GPIOE
#define M2_BIN2_Pin GPIO_PIN_3
#define M2_BIN2_GPIO_Port GPIOE
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOE
#define LED4_Pin GPIO_PIN_5
#define LED4_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOE
#define ENC1A_Pin GPIO_PIN_5
#define ENC1A_GPIO_Port GPIOA
#define M1_PWMA_Pin GPIO_PIN_6
#define M1_PWMA_GPIO_Port GPIOA
#define M1_PWMB_Pin GPIO_PIN_7
#define M1_PWMB_GPIO_Port GPIOA
#define M3_PWMA_Pin GPIO_PIN_0
#define M3_PWMA_GPIO_Port GPIOB
#define M3_PWMB_Pin GPIO_PIN_1
#define M3_PWMB_GPIO_Port GPIOB
#define M6_PWMA_Pin GPIO_PIN_8
#define M6_PWMA_GPIO_Port GPIOE
#define ENC2A_Pin GPIO_PIN_9
#define ENC2A_GPIO_Port GPIOE
#define ENC2B_Pin GPIO_PIN_11
#define ENC2B_GPIO_Port GPIOE
#define M6_PWMB_Pin GPIO_PIN_13
#define M6_PWMB_GPIO_Port GPIOE
#define M2_AIN1_Pin GPIO_PIN_12
#define M2_AIN1_GPIO_Port GPIOB
#define M2_AIN2_Pin GPIO_PIN_13
#define M2_AIN2_GPIO_Port GPIOB
#define ENC4A_Pin GPIO_PIN_14
#define ENC4A_GPIO_Port GPIOB
#define ENC4B_Pin GPIO_PIN_15
#define ENC4B_GPIO_Port GPIOB
#define slider1A_Pin GPIO_PIN_8
#define slider1A_GPIO_Port GPIOD
#define slider1B_Pin GPIO_PIN_9
#define slider1B_GPIO_Port GPIOD
#define slider2A_Pin GPIO_PIN_10
#define slider2A_GPIO_Port GPIOD
#define slider2B_Pin GPIO_PIN_11
#define slider2B_GPIO_Port GPIOD
#define ENC3A_Pin GPIO_PIN_6
#define ENC3A_GPIO_Port GPIOC
#define ENC3B_Pin GPIO_PIN_7
#define ENC3B_GPIO_Port GPIOC
#define STBY_ALL_Pin GPIO_PIN_10
#define STBY_ALL_GPIO_Port GPIOC
#define But2_Pin GPIO_PIN_0
#define But2_GPIO_Port GPIOD
#define But1_Pin GPIO_PIN_1
#define But1_GPIO_Port GPIOD
#define M3_AIN1_Pin GPIO_PIN_2
#define M3_AIN1_GPIO_Port GPIOD
#define M3_AIN2_Pin GPIO_PIN_3
#define M3_AIN2_GPIO_Port GPIOD
#define M3_BIN1_Pin GPIO_PIN_4
#define M3_BIN1_GPIO_Port GPIOD
#define M3_BIN2_Pin GPIO_PIN_7
#define M3_BIN2_GPIO_Port GPIOD
#define ENC1B_Pin GPIO_PIN_3
#define ENC1B_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
