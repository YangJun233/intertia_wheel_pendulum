/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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
#define BAT_LEVER_Pin GPIO_PIN_0
#define BAT_LEVER_GPIO_Port GPIOA
#define BLE_TX_Pin GPIO_PIN_2
#define BLE_TX_GPIO_Port GPIOA
#define BLE_RX_Pin GPIO_PIN_3
#define BLE_RX_GPIO_Port GPIOA
#define MOTOR_X_PWM_Pin GPIO_PIN_6
#define MOTOR_X_PWM_GPIO_Port GPIOA
#define MOTOR_Y_PWM_Pin GPIO_PIN_7
#define MOTOR_Y_PWM_GPIO_Port GPIOA
#define MOTOR_R_PWM_Pin GPIO_PIN_0
#define MOTOR_R_PWM_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_1
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOB
#define IMU_SCL_Pin GPIO_PIN_10
#define IMU_SCL_GPIO_Port GPIOB
#define IMU_SDA_Pin GPIO_PIN_11
#define IMU_SDA_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_12
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_13
#define OLED_SDA_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_14
#define LED_RED_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_15
#define LED_GREEN_GPIO_Port GPIOB
#define Encoder_X_A_Pin GPIO_PIN_8
#define Encoder_X_A_GPIO_Port GPIOA
#define Encoder_X_B_Pin GPIO_PIN_9
#define Encoder_X_B_GPIO_Port GPIOA
#define Encoder_Y_R_A_Pin GPIO_PIN_15
#define Encoder_Y_R_A_GPIO_Port GPIOA
#define Encoder_Y_R_B_Pin GPIO_PIN_3
#define Encoder_Y_R_B_GPIO_Port GPIOB
#define DEBUG_TX_Pin GPIO_PIN_6
#define DEBUG_TX_GPIO_Port GPIOB
#define DEBUG_RX_Pin GPIO_PIN_7
#define DEBUG_RX_GPIO_Port GPIOB
#define SERVO_PWM_Pin GPIO_PIN_8
#define SERVO_PWM_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
