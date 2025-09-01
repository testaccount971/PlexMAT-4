/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
#include "Fluid_Sense.h"

/* USER CODE END Includes */

extern TIM_HandleTypeDef htim3;

extern TIM_HandleTypeDef htim4;

extern TIM_HandleTypeDef htim5;

extern TIM_HandleTypeDef htim9;

extern TIM_HandleTypeDef htim10;

extern TIM_HandleTypeDef htim11;

extern TIM_HandleTypeDef htim12;

extern TIM_HandleTypeDef htim13;

/* USER CODE BEGIN Private defines */
extern volatile uint32_t pulse_count;
extern volatile uint32_t target_pulses;
extern volatile uint32_t tim3_overflow;
/* USER CODE END Private defines */

void MX_TIM3_Init(void);
void MX_TIM4_Init(void);
void MX_TIM5_Init(void);
void MX_TIM9_Init(void);
void MX_TIM10_Init(void);
void MX_TIM11_Init(void);
void MX_TIM12_Init(void);
void MX_TIM13_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* USER CODE BEGIN Prototypes */
/**
 * @brief Start PWM with custom frequency, duty cycle, and pulse count
 * @param htim        Pointer to TIM_HandleTypeDef (e.g., &htim3)
 * @param channel     TIM Channel (e.g., TIM_CHANNEL_1)
 * @param frequency   Desired PWM frequency in Hz
 * @param duty_cycle  Duty cycle in percentage (0–100)
 * @param num_pulses  Number of PWM pulses to generate
 */
void Start_PWM(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t frequency, uint32_t duty_cycle, uint32_t num_pulses);

void Stop_PWM(TIM_HandleTypeDef *htim, uint32_t channel);


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

