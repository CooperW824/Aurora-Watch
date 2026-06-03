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
#include "stm32u0xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define XL_INT_1_Pin GPIO_PIN_0
#define XL_INT_1_GPIO_Port GPIOA
#define XL_INT_2_Pin GPIO_PIN_1
#define XL_INT_2_GPIO_Port GPIOA
#define MAG_INT_Pin GPIO_PIN_2
#define MAG_INT_GPIO_Port GPIOA
#define CHARGE_STAT_1_Pin GPIO_PIN_3
#define CHARGE_STAT_1_GPIO_Port GPIOA
#define CHARGE_STAT_2_Pin GPIO_PIN_4
#define CHARGE_STAT_2_GPIO_Port GPIOA
#define SOC_ALRT_Pin GPIO_PIN_5
#define SOC_ALRT_GPIO_Port GPIOA
#define CHARGE_EN_Pin GPIO_PIN_6
#define CHARGE_EN_GPIO_Port GPIOA
#define LEFT_BUTTON_Pin GPIO_PIN_11
#define LEFT_BUTTON_GPIO_Port GPIOA
#define RIGHT_BUTTON_Pin GPIO_PIN_12
#define RIGHT_BUTTON_GPIO_Port GPIOA
#define LED_SHUTDOWN_Pin GPIO_PIN_3
#define LED_SHUTDOWN_GPIO_Port GPIOF

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
