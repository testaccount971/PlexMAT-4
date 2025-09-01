/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.h
  * @brief   This file contains all the function prototypes for
  *          the i2c.c file
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
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_I2C2_Init(void);

/* USER CODE BEGIN Prototypes */
float Read_Sensor_Volage(int Sensor_No);
uint8_t I2C_Device_Check(uint8_t dev_addr);

void I2C2_Recover(void);
HAL_StatusTypeDef MCP4661_WriteWiperRAM(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint8_t wiper, uint8_t value);

HAL_StatusTypeDef MCP4661_ReadWiper0_RAM(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint16_t *value);

HAL_StatusTypeDef MCP4661_WriteWiper0_RAM(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint16_t wiper_value);

void Test_MCP4661_Corrected(I2C_HandleTypeDef *hi2c, uint8_t dev_addr);

HAL_StatusTypeDef MCP4661_ReadStatusRegister(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint16_t *status_value);
HAL_StatusTypeDef MCP4661_WriteWiper_EEPROM(
    I2C_HandleTypeDef *hi2c,
    uint8_t dev_addr,
    uint8_t wiper_index,
    uint16_t wiper_value);

HAL_StatusTypeDef MCP4661_ReadWiper_EEPROM(
    I2C_HandleTypeDef *hi2c,
    uint8_t dev_addr,
    uint8_t wiper_index,
    uint16_t *wiper_value);

void MCP4661_SetHardwareWriteProtect(GPIO_TypeDef* hw_wp_port, uint16_t hw_wp_pin, uint8_t enable);
uint8_t voltageToStep(float voltage);
void I2C_ScanBus();
uint8_t voltageToStep_Calibrated(uint8_t sensor_no, float desired_voltage);
float ADS7828_ConvertToVoltage_Calibrated(uint16_t adc_val);
float CalibrateADCValue(uint16_t adc_raw);
uint8_t voltageToStep(float voltage);
uint16_t ADS7828_ReadChannelAdcValue(uint8_t channel);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

