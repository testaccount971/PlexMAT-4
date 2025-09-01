/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    i2c.c
  * @brief   This file provides code for the configuration
  *          of the I2C instances.
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
/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/* USER CODE BEGIN 0 */
#include"command_processor.h"
#include"tim.h"
/* USER CODE END 0 */

I2C_HandleTypeDef hi2c2;

/* I2C2 init function */
void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspInit 0 */

  /* USER CODE END I2C2_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**I2C2 GPIO Configuration
    PB10     ------> I2C2_SCL
    PC12     ------> I2C2_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* I2C2 clock enable */
    __HAL_RCC_I2C2_CLK_ENABLE();
  /* USER CODE BEGIN I2C2_MspInit 1 */

  /* USER CODE END I2C2_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspDeInit 0 */

  /* USER CODE END I2C2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C2_CLK_DISABLE();

    /**I2C2 GPIO Configuration
    PB10     ------> I2C2_SCL
    PC12     ------> I2C2_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_12);

  /* USER CODE BEGIN I2C2_MspDeInit 1 */

  /* USER CODE END I2C2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void I2C_ScanBus(void)
		  {
	char msg[32];
	          printf("Scanning I2C bus...\r\n");
		      for (uint8_t address = 0x08; address < 0x77; address++)
		      {
		          if (HAL_I2C_IsDeviceReady(&hi2c2, (address << 1), 1, 10) == HAL_OK)
		          {
		        	  snprintf(msg, sizeof(msg), "Found device at 0x%02X\r\n", address);
		        	  HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
		          }
		      }
		  }

/**
 * @brief Control write protection pin for specific MCP4661 device
 * @param device_id: Index (0-3) for ePOT1 to ePOT4
 * @param enable: 0 = disable write protection (drive WP pin HIGH)
 *                1 = enable write protection (drive WP pin LOW)
 */
void MCP4661_SetWriteProtect(uint8_t device_id, uint8_t enable) {
    if (device_id < 4) {
  //      HAL_GPIO_WritePin(EPOT_WP_Ports[device_id], EPOT_WP_Pins[device_id], enable ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }
}

/**
 * @brief Write to non-volatile wiper register on MCP4661
 * @param hi2c: Pointer to initialized I2C handle
 * @param device_id: ePOT device index (0 to 3)
 * @param reg: Wiper register address (0x00 = Wiper0, 0x01 = Wiper1)
 * @param value: 9-bit wiper value to write (0 to 0x1FF)
 */
void MCP4661_WriteWiperNV(I2C_HandleTypeDef *hi2c, uint8_t device_id, uint8_t reg, uint16_t value) {
    if (device_id >= 4) return; // Invalid device ID

//    uint8_t devAddr = EPOT_I2C_Addrs[device_id];
    uint8_t devAddr = MCP4661_ADDR_EPOT1;
    value &= 0x01FF; // Limit to 9-bit range

    // Construct command and data bytes
    uint8_t cmd = reg << 2; // Command format: REG[7:2], CMD[1:0] = 00 (write)
    uint8_t data[2];
    data[0] = (uint8_t)(value >> 1);        // MSB 8 bits
    data[1] = (uint8_t)((value & 0x01) << 7); // LSB bit in bit 7

    uint8_t packet[3] = {cmd, data[0], data[1]};

    // Disable write protection before writing
    MCP4661_SetWriteProtect(device_id, 0);
    HAL_I2C_Master_Transmit(hi2c, devAddr, packet, 3, I2C_Delay_Ms);
    // Re-enable write protection after writing
    MCP4661_SetWriteProtect(device_id, 1);
}



///**
// * @brief Trigger EEPROM recall to volatile wiper register
// * @param hi2c: Pointer to initialized I2C handle
// * @param device_id: ePOT index (0-3)
// * @param wiper: 0 = Wiper0, 1 = Wiper1
// */
//void MCP4661_RecallEEPROM(I2C_HandleTypeDef *hi2c, uint8_t device_id, uint8_t wiper) {
//    if (device_id >= 4) return; // Invalid device ID
//
//    uint8_t devAddr = EPOT_I2C_Addrs[device_id];
//    uint8_t reg = (wiper == 0) ? 0x02 : 0x03; // Recall NV to volatile
//    uint8_t cmdByte = (reg << 2) | 0x0C; // CMD = EEPROM recall
//
//    HAL_I2C_Master_Transmit(hi2c, devAddr, &cmdByte, 1, I2C_Delay_Ms);
//    HAL_Delay(1); // Wait for recall to complete
//
//}

/**
 * @brief Convert voltage to MCP4661 wiper step value
 * @param voltage: Input voltage (0V to 5V)
 * @return 8-bit wiper value scaled to 0–257 (approx. 1 step = ~19.5mV)
 */
uint8_t VoltageToWiper(float voltage) {
    if (voltage < 0.0f) voltage = 0.0f;
    if (voltage > 5.0f) voltage = 5.0f;
    return (uint8_t)((voltage / 5.0f) * 257.0f);
}

/**
 * @brief Convert wiper step back to equivalent voltage
 * @param wiperValue: Wiper step (0 to 257)
 * @return Voltage value (0V to ~5V)
 */
float WiperToVoltage(uint16_t wiperValue) {
    if (wiperValue > 257) wiperValue = 257;
    return (wiperValue / 257.0f) * 5.0f;
}

/**
 * @brief  Check if an I2C device is responding.
 * @param  dev_addr: 7-bit I2C device address (not shifted)
 * @retval 1 if device is present and responding, 0 otherwise
 **/
uint8_t I2C_Device_Check(uint8_t dev_addr)
{
	if(MCP4661_BASE_ADDR==dev_addr)
	{
		if (HAL_I2C_IsDeviceReady(&hi2c2, dev_addr, 3, 100) == HAL_OK) {
			// ACK received
			return 1;
		} else {
			// NACK received or timeout
			return 0;
		}
	}
	else if(ADS7828_ADDR==dev_addr)
	{
		if (HAL_I2C_IsDeviceReady(&hi2c2, dev_addr, 3, 100) == HAL_OK) {
			// ACK received
			return 1;
		} else {
			// NACK received or timeout
			return 0;
		}
    }
	else
	{
	//	debug_print("Invalid device or device not found\r\n");
		return 0;
	}
}
// Function to read a single-ended channel (AIN0 to AIN7)
uint16_t ADS7828_ReadChannel(uint8_t channel) {
    if (channel > 7) return 0xFFFF; // Invalid channel index, return error code

//       char msg[50];
//       snprintf(msg, sizeof(msg), "channel: %d\r\n", channel);
//       HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), I2C_Delay_Ms);

    uint8_t ctrl_byte = 0;  // Control byte to be sent to ADS7828

    // Construct control byte:
    // Bit 7: Always 1 (Start bit)
    // Bits 6-4: Channel selection bits (channel << 4)
    // Bit 3: Single-ended mode (1)
    // Bits 2-0: Power-down selection (PD)
    ctrl_byte |= (1 << 7);                        // Start bit = 1
    ctrl_byte |= (channel & 0x07) << 4;           // Channel selection
    ctrl_byte |= (1 << 3);                        // Single-ended mode
    ctrl_byte |= (PD_ALL_ON & 0x03); // Power-down mode

//    snprintf(msg, sizeof(msg), "ctrl_byte: 0x%02X\r\n", ctrl_byte);  // Format as hex for clarity
//    HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), I2C_Delay_Ms);

    uint8_t raw[2];  // Buffer to store received data (2 bytes)

    // Send control byte to initiate conversion for the selected channel
    if (HAL_I2C_Master_Transmit(&hi2c2, ADS7828_ADDR, &ctrl_byte, 1, I2C_Delay_Ms) != HAL_OK) {
        return 0xFFFF; // Transmission failed
    }
    HAL_Delay(1);
    // Read 2-byte ADC result from ADS7828
    if (HAL_I2C_Master_Receive(&hi2c2, ADS7828_ADDR, raw, 2, I2C_Delay_Ms) != HAL_OK) {
        return 0xFFFF; // Reception failed
    }

    // Combine the 12-bit result from 2 bytes (raw[0]: high 8 bits, raw[1]: low 4 bits)
 //   uint16_t result = (raw[0] << 4) | (raw[1] >> 4);

 //   uint16_t result = ((uint16_t)raw[0] << 4) | (raw[1] >> 4);
    uint16_t result = (((uint16_t)raw[0] << 8) | raw[1]);
 //   char debug[50];
 //   snprintf(debug, sizeof(debug), "ADC Raw: %02X %02X, Value: %u\r\n", raw[0], raw[1], result);
//    HAL_UART_Transmit(&huart3, (uint8_t*)debug, strlen(debug), I2C_Delay_Ms);
    return result; // Return 12-bit ADC value
}

float ADS7828_ConvertToVoltage(uint16_t adc_val) {

       // 1. Convert ADC value to float and divide by 1000 to normalize
          float normalized_adc = (float)adc_val / 1000.0f;

          // 2. Round to 2 decimal places (e.g., 1.2345 -> 1.23, 1.2367 -> 1.24)
          float voltage = roundf(normalized_adc * 100.0f) / 100.0f;

       if (voltage <  0.9f)
           voltage = -0.0f;
       if (voltage > 4.0f)
           voltage = -5.0f;
  //     return voltage;

    // Prepare message buffer
  //  char msg[64];
  //  snprintf(msg, sizeof(msg), "ADC Value: %u, Voltage: %.3f V\r\n", adc_val, voltage);

    // Transmit message over UART
  //  HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);

    return voltage;
}

// Function to read and return the voltage of a specific channel
float ADS7828_ReadChannelVoltage(uint8_t channel) {
    uint16_t adc_val = ADS7828_ReadChannel(channel); // Get raw ADC value
    if (adc_val == 0xFFFF) {
        return -1.0f; // Return error indicator (negative voltage not possible)
    }

    return ADS7828_ConvertToVoltage(adc_val); // Return converted voltage
}

// Function to read and return the voltage of a specific channel
uint16_t ADS7828_ReadChannelAdcValue(uint8_t channel) {
    uint16_t adc_val = ADS7828_ReadChannel(channel); // Get raw ADC value
    if (adc_val == 0xFFFF) {
        return -1.0f; // Return error indicator (negative voltage not possible)
    }

    return adc_val; // Return converted voltage
}
float Read_Sensor_Volage(int Sensor_No)
{
	/*switch (Sensor_No) {
		       case 1:
		            return ADS7828_ReadChannelVoltage(WashOrUniversal_Buffer_ADC); // Reads CH0
		        case 2:
		            return ADS7828_ReadChannelVoltage(DI_Water_ADC); // Reads CH1
		        default:
		            return -1.0f; // Invalid channel
		    }*/

     //* For all EPOT Testing

	switch (Sensor_No) {
	       case 1:
	            return ADS7828_ReadChannelVoltage(SampleOrBlocking_Buffer_ADC); // Reads CH0
	        case 2:
	            return ADS7828_ReadChannelVoltage(WashOrUniversal_Buffer_ADC); // Reads CH1
	        case 3:
	            return ADS7828_ReadChannelVoltage(Conjugate_IgG_ADC); // Reads CH2
	        case 4:
	            return ADS7828_ReadChannelVoltage(Conjugate_IgMOrIgE_ADC); // Reads CH3
	        case 5:
	            return ADS7828_ReadChannelVoltage(Subsrtrate_ADC); // Reads CH4
	        case 6:
	            return ADS7828_ReadChannelVoltage(DI_Water_ADC); // Reads CH5
	        case 7:
	            return ADS7828_ReadChannelVoltage(Waste_Full_ADC); // Reads CH6
	        case 8:
	            return ADS7828_ReadChannelVoltage(Vaccum_Sensor_ADC); // Reads CH7
	        default:
	            return -1.0f; // Invalid channel
	    }


}
/**
 * @brief Writes a value to the RAM wiper (volatile) of MCP4661.
 * @param hi2c Pointer to the I2C handle (e.g., &hi2c2)
 * @param dev_addr 7-bit I2C address of MCP4661 (e.g., 0x29)
 * @param wiper 0 for WIPER0, 1 for WIPER1
 * @param value 8-bit wiper value (0–255)
 * @return HAL status
 */
HAL_StatusTypeDef MCP4661_WriteWiperRAM(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint8_t wiper, uint8_t value)
{
    uint8_t reg = (wiper == 0) ? 0x00 : 0x01;  // 0x00 = WIPER0_VOL, 0x01 = WIPER1_VOL
    uint8_t cmd[2];

    // Command byte:
    // C1:C0 = 00 (write), AD3:AD0 = reg, D9 = 0, D8 = (value >> 8) & 0x01
    uint8_t command = (reg << 4) | (0x0 << 2) | ((value >> 8) & 0x03);

    cmd[0] = command;          // High byte: command + bits 9:8 of value
    cmd[1] = value & 0xFF;     // Low byte: D7–D0

    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(hi2c, (dev_addr << 1), cmd, 2, I2C_Delay_Ms);

//    if (status != HAL_OK)
//    {
//        char err[] = "0x%02X RAM write failed\r\n";
//        char msg[64];
//        snprintf(msg, sizeof(msg), err, dev_addr);
//        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), I2C_Delay_Ms);
//    }

    return status;
}

///////30-7-25
/**
 * @brief Write data to volatile wiper 0 (RAM) - CORRECTED VERSION
 * @param hi2c Pointer to I2C handle
 * @param dev_addr 7-bit I2C device address
 * @param wiper_value 9-bit wiper value (0-256)
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef MCP4661_WriteWiper0_RAM(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint16_t wiper_value)
{
    uint8_t cmd[2];
    char msg[64];

    // Limit to 9-bit range (0-256)
    wiper_value &= 0x01FF;

    // CORRECTED: Command byte format based on MCP4661 datasheet
    // [AD3:AD0 = 0000][C1:C0 = 00][D9:D8]
    // Address 0x00 = Volatile Wiper 0, Command 00 = Write Data
    // D9 is unused (always 0), D8 is bit 8 of the 9-bit value
    cmd[0] = (0x00 << 4) | (0x00 << 2) | ((wiper_value >> 8) & 0x01);
    cmd[1] = wiper_value & 0xFF;  // Lower 8 bits (D7:D0)

    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(hi2c, (dev_addr << 1), cmd, 2, 1000);

    if (status != HAL_OK) {
        snprintf(msg, sizeof(msg), "Wiper0 RAM write failed: 0x%02X\r\n", dev_addr);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
    } else {
        snprintf(msg, sizeof(msg), "Wiper0 RAM: %u written (cmd: 0x%02X 0x%02X)\r\n",
                 wiper_value, cmd[0], cmd[1]);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
    }

    return status;
}

/**
 * @brief Read data from volatile wiper 0 (RAM) - CORRECTED VERSION
 * @param hi2c Pointer to I2C handle
 * @param dev_addr 7-bit I2C device address
 * @param wiper_value Pointer to store read value
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef MCP4661_ReadWiper0_RAM(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint16_t *wiper_value)
{
    uint8_t cmd;
    uint8_t data[2];
    char msg[80];

    // Command byte for read: [AD3:AD0 = 0000][C1:C0 = 11][D9:D8 = 00]
    cmd = (0x00 << 4) | (0x03 << 2) | 0x00;  // 0x0C

    // Send read command
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(hi2c, (dev_addr << 1), &cmd, 1, 1000);
    if (status != HAL_OK) {
        snprintf(msg, sizeof(msg), "Wiper0 RAM read cmd failed: 0x%02X\r\n", dev_addr);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
        return status;
    }

    // Read 2 bytes of data
    status = HAL_I2C_Master_Receive(hi2c, (dev_addr << 1), data, 2, 1000);
    if (status != HAL_OK) {
        snprintf(msg, sizeof(msg), "Wiper0 RAM read data failed: 0x%02X\r\n", dev_addr);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
        return status;
    }

    // CORRECTED: Based on MCP4661 datasheet data format
    // According to the datasheet, the read data format is:
    // First byte (data[0]): D7:D0 (lower 8 bits)
    // Second byte (data[1]): bits 1:0 contain D9:D8 (upper bits)
    *wiper_value = ((data[0] & 0x01) << 8) | data[1];

    snprintf(msg, sizeof(msg), "Wiper0 RAM read: %u (raw bytes: 0x%02X 0x%02X)\r\n",
             *wiper_value, data[0], data[1]);
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);

    return HAL_OK;
}

/**
 * @brief Test function to verify the correction
 */
void Test_MCP4661_Corrected(I2C_HandleTypeDef *hi2c, uint8_t dev_addr)
{
    uint16_t test_values[] = {0, 1, 2, 3, 64, 128, 255, 256};
    uint16_t read_value;
    char msg[80];

    snprintf(msg, sizeof(msg), "=== MCP4661 CORRECTED Test ===\r\n");
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);

    for (int i = 0; i < 8; i++) {
        // Write value
        if (MCP4661_WriteWiper0_RAM(hi2c, dev_addr, test_values[i]) == HAL_OK) {
            HAL_Delay(10);

            // Read back value
            if (MCP4661_ReadWiper0_RAM(hi2c, dev_addr, &read_value) == HAL_OK) {
                snprintf(msg, sizeof(msg), "Test %d: Write=%u, Read=%u %s\r\n",
                        i+1, test_values[i], read_value,
                        (test_values[i] == read_value) ? "PASS" : "FAIL");
                HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
            }
        }
        HAL_Delay(100);
    }

    snprintf(msg, sizeof(msg), "=== Test Complete ===\r\n");
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
}


HAL_StatusTypeDef MCP4661_ReadStatusRegister(I2C_HandleTypeDef *hi2c, uint8_t dev_addr, uint16_t *status_value)
{
    uint8_t cmd = (0x05 << 4) | (0x03 << 2);  // 0x5C: Status reg address, read command
    uint8_t data[2];
    char msg[64];

    // Send command to select Status Register
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(hi2c, (dev_addr << 1), &cmd, 1, 1000);
    if (status != HAL_OK) {
        snprintf(msg, sizeof(msg), "Status reg read cmd failed: 0x%02X\r\n", dev_addr);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
        return status;
    }

    // Read 2 bytes back from device
    status = HAL_I2C_Master_Receive(hi2c, (dev_addr << 1), data, 2, 1000);
    if (status != HAL_OK) {
        snprintf(msg, sizeof(msg), "Status reg read data failed: 0x%02X\r\n", dev_addr);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
        return status;
    }

    // Combine bytes: lower 8 bits in data[0], upper in data[1]
    *status_value = ((data[0] & 0xFF) << 8) | data[1];

    // Debug output
    snprintf(msg, sizeof(msg), "MCP4661 status register = 0x%04X (raw: %02X %02X)\r\n", *status_value, data[0], data[1]);
    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);

    return HAL_OK;
}

uint8_t voltageToStep(float voltage)
{
    char msg[64];  // Buffer for UART message

    // Print the voltage value
//    snprintf(msg, sizeof(msg), "Voltage = %.3f V\r\n", voltage);
//    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);

    if (voltage <= V_LOW) return 0;
    if (voltage >= V_MAX) return MAX_STEP;

    float step = MAX_STEP * (voltage - V_LOW) / (V_MAX - V_LOW);

    // Print the step value (float)
//    snprintf(msg, sizeof(msg), "Step (float) = %.3f\r\n", step);
 //   HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);

    // Print the step value (rounded integer)
    uint8_t step_int = (uint8_t)roundf(step);
 //   snprintf(msg, sizeof(msg), "Step (rounded) = %u\r\n", step_int);
//    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);

    return step_int;
}

//
//float CalibrateADCValue(uint16_t adc_raw)
//{
//    float a = (V_HIGH_CAL - V_LOW_CAL) / (ADC_HIGH_CAL - ADC_LOW_CAL);
//    float b = V_LOW_CAL - a * ADC_LOW_CAL;
//
//    float voltage = a * adc_raw + b;
//
//    // Clamp voltage to valid range
//    if (voltage < V_LOW_CAL) voltage = V_LOW_CAL;
//    if (voltage > V_HIGH_CAL) voltage = V_HIGH_CAL;
//
//    return voltage;
//}
//
//
//float ADS7828_ConvertToVoltage_Calibrated(uint16_t adc_val)
//{
//    return CalibrateADCValue(adc_val);
//}
//
//uint8_t voltageToStep_Calibrated(uint8_t sensor_no, float desired_voltage)
//{
//    char msg[64];  // Buffer for UART message
//    // Print desired voltage to UART for debugging
//    snprintf(msg, sizeof(msg), "Desired Voltage for sensor %d = %.3f V\r\n", sensor_no, desired_voltage);
//    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
//
//	uint8_t wiper_val = voltageToStep(desired_voltage);
//	switch (sensor_no) {
//				case 1:
//						   MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 1); // Enable for ePot 1_1
//						  // Write to RAM (volatile) wiper 0
//						  if (MCP4661_WriteWiperRAM(&hi2c2, 0x29, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  // Write to EEPROM (non-volatile) wiper 0
//						  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x29, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 0); // Enable for ePot 1_1
//						   break ;
//
//				case 2:
//						  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 1); // Enable for ePot 1_2
//						  // Write to RAM (volatile) wiper 0
//						  if (MCP4661_WriteWiperRAM(&hi2c2, 0x29, 1, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  // Write to EEPROM (non-volatile) wiper 0
//						  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x29, 1, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 0); // Enable for ePot 1_2
//						  break ;
//
//				case 3:
//					      MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 1); // Enable for ePot 2_1
//						  // Write to RAM (volatile) wiper 0
//						  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2B, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  // Write to EEPROM (non-volatile) wiper 0
//						  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2B, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 0); // Enable for ePot 2_1
//						  break;
//
//				case 4:
//						  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 1); // Enable for ePot 2_2
//							// Write to RAM (volatile) wiper 1
//						  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2B, 1, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//
//						  // Write to EEPROM (non-volatile) wiper 1
//						  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2B, 1, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 0); // Enable for ePot 2_2
//							break ;
//
//				case 5:
//					      MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 1); // Enable for ePot 3_1
//						  // Write to RAM (volatile) wiper 0
//						  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2D, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  // Write to EEPROM (non-volatile) wiper 0
//						  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2D, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 0); // Enable for ePot 3_1
//						  break ;
//
//				case 6:
//						  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 1); // Enable for ePot 3_2
//						  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2D, 1, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  // Write to EEPROM (non-volatile) wiper 0
//						  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2D, 1, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 0); // Enable for ePot 3_2
//						  break ;
//
//				case 7:
//						 MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_5, 1); // Enable for ePot 4_1
//						 if (MCP4661_WriteWiperRAM(&hi2c2, 0x2F, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  // Write to EEPROM (non-volatile) wiper 0
//						  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2F, 0, wiper_val) != HAL_OK)
//						  {
//							  Error = "W";
//						  }
//						  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_5, 0); // Enable for ePot 4_1
//						  break ;
//
//				default:
//						 break ;
//				}
//
//	   uint16_t adc_val=0;
//
//	   snprintf(msg, sizeof(msg), "Sensor Number: %d\r\n", sensor_no);
//	   HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
//
//	switch (sensor_no) {
//	       case 1:
//	    	   adc_val= ADS7828_ReadChannelAdcValue(SampleOrBlocking_Buffer_ADC); // Reads CH0
//	           break;
//	       case 2:
//	        	 adc_val=ADS7828_ReadChannelAdcValue(WashOrUniversal_Buffer_ADC); // Reads CH1
//	        	 break;
//	        case 3:
//	        	 adc_val=ADS7828_ReadChannelAdcValue(Conjugate_IgG_ADC); // Reads CH2
//	        	 break;
//	        case 4:
//	        	 adc_val= ADS7828_ReadChannelAdcValue(Conjugate_IgMOrIgE_ADC); // Reads CH3
//	        	 break;
//	        case 5:
//	        	 adc_val= ADS7828_ReadChannelAdcValue(Subsrtrate_ADC); // Reads CH4
//	        	 break;
//	        case 6:
//	        	 adc_val= ADS7828_ReadChannelAdcValue(DI_Water_ADC); // Reads CH5
//	        	 break;
//	        case 7:
//	        	 adc_val= ADS7828_ReadChannelAdcValue(Waste_Full_ADC); // Reads CH6
//	        	 break;
//
//	        case 8:
//	        	 adc_val= ADS7828_ReadChannelAdcValue(Vaccum_Sensor_ADC); // Reads CH7
//	        	 break;
//	        default:
//	        	 adc_val= 500; // Invalid channel
//	        	 break;
//	    }
//
//    snprintf(msg, sizeof(msg), "actual ADC Value for sensor %d = %u\r\n", sensor_no, adc_val);
//    HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
//    float calibrated_voltage = ADS7828_ConvertToVoltage_Calibrated(adc_val);
//
//    // Use previously implemented voltageToStep logic here:
//    // (You can call your existing voltageToStep function or inline it)
//    return voltageToStep(calibrated_voltage);
//}



/* * @brief Write a 9-bit value to MCP4661 EEPROM (non-volatile wiper).
 * @param hi2c        Pointer to I2C handle (e.g., &hi2c2)
 * @param dev_addr    7-bit MCP4661 I2C address (e.g., 0x2D)
 * @param wiper_index 0 for Wiper0, 1 for Wiper1
 * @param wiper_value 9-bit value (0–256 for MCP4661)
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef MCP4661_WriteWiper_EEPROM(
    I2C_HandleTypeDef *hi2c,
    uint8_t dev_addr,
    uint8_t wiper_index,
    uint16_t wiper_value)
{
    uint8_t cmd[2];
    char msg[64];
    MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 1); // Enable for ePot 1

    // Limit wiper_value to 9 bits (0–256 for MCP4661)
    wiper_value &= 0x01FF;

    // EEPROM Wiper address: 0x02 (W0), 0x03 (W1)
    uint8_t address = 0x02 + (wiper_index & 0x01);

    // Command byte: [AD3:AD0][C1:C0=00][D8]
    cmd[0] = (address << 4) | (0x00 << 2) | ((wiper_value >> 8) & 0x01);
    cmd[1] = wiper_value & 0xFF;

    // Optional: Check/disable WP and WL bits first as needed (see status register docs)

    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(hi2c, (dev_addr << 1), cmd, 2, 1000);

//    if (status != HAL_OK) {
//        snprintf(msg, sizeof(msg), "EEPROM write FAILED (dev 0x%02X)\r\n", dev_addr);
//        HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), 1000);
//        return status;
//    }

    // Delay for EEPROM write cycle (datasheet: tWR = 5–15ms)
    HAL_Delay(15);

//    snprintf(msg, sizeof(msg), "EEPROM write OK: Wiper%d = %u\r\n", wiper_index, wiper_value);
//    HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), 1000);

    return status;
}

/**
 * @brief Read the 9-bit value from MCP4661 EEPROM (non-volatile wiper 0 or 1).
 * @param hi2c        Pointer to I2C handle (e.g., &hi2c2)
 * @param dev_addr    7-bit device address of MCP4661 (e.g., 0x2D)
 * @param wiper_index 0 for Wiper0, 1 for Wiper1
 * @param wiper_value Pointer to variable that will store the result (0–256)
 * @return HAL_StatusTypeDef
 */
HAL_StatusTypeDef MCP4661_ReadWiper_EEPROM(
    I2C_HandleTypeDef *hi2c,
    uint8_t dev_addr,
    uint8_t wiper_index,
    uint16_t *wiper_value)
{
    // EEPROM Wiper address: 0x02 = W0, 0x03 = W1
    uint8_t address = 0x02 + (wiper_index & 0x01);

    // Command byte for read: [AD3:AD0][C1:C0=11][D9:D8=0]
    uint8_t cmd = (address << 4) | (0x03 << 2);

    uint8_t data[2];
    char msg[80];

    // Send the read command
    HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(hi2c, (dev_addr << 1), &cmd, 1, 1000);
    if (status != HAL_OK) {
        snprintf(msg, sizeof(msg), "EEPROM read cmd FAILED: status=%d\r\n", status);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
        return status;
    }

    // Read 2 bytes
    status = HAL_I2C_Master_Receive(hi2c, (dev_addr << 1), data, 2, 1000);
    if (status != HAL_OK) {
        snprintf(msg, sizeof(msg), "EEPROM read data FAILED: status=%d\r\n", status);
        HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), 1000);
        return status;
    }

    // Reconstruct 9-bit value: data[0]=D7:D0, data[1] bit 0=D8
    *wiper_value = ((data[0] & 0x01) << 8) | data[1];

    snprintf(msg, sizeof(msg), "EEPROM Wiper%d: %u (raw: 0x%02X 0x%02X)\r\n",
             wiper_index, *wiper_value, data[0], data[1]);
    HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), 1000);

    return HAL_OK;
}

/**
 * @brief Enable or disable hardware write protect (HW WP) for an MCP4661 ePot.
 *        Setting HIGH allows EEPROM writes. Setting LOW blocks EEPROM writes.
 * @param hw_wp_port  GPIO port connected to the ePot's HW WP pin (e.g., GPIOB, GPIOD)
 * @param hw_wp_pin   GPIO pin number (e.g., GPIO_PIN_5)
 * @param enable      1 to disable HW WP (set pin HIGH, allows EEPROM writes)
 *                    0 to enable HW WP (set pin LOW, blocks EEPROM writes)
 */
void MCP4661_SetHardwareWriteProtect(GPIO_TypeDef* hw_wp_port, uint16_t hw_wp_pin, uint8_t enable)
{
    // Set HW WP pin: HIGH (GPIO_PIN_SET) disables hardware write protection
    //                LOW  (GPIO_PIN_RESET) enables hardware write protection
    HAL_GPIO_WritePin(hw_wp_port, hw_wp_pin, enable ? GPIO_PIN_SET : GPIO_PIN_RESET);
}



void I2C2_Recover(void)
{

	    GPIO_InitTypeDef GPIO_InitStruct = {0};

	    // 1. DeInit I2C to gain control over pins
	    HAL_I2C_DeInit(&hi2c2);

	    // 2. Enable GPIO clocks if not already enabled
	    __HAL_RCC_GPIOB_CLK_ENABLE();

	    // 3. Configure SCL and SDA as GPIO Output Open Drain
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	    GPIO_InitStruct.Pin = I2C2_SCL_PIN;
	    HAL_GPIO_Init(I2C2_SCL_PORT, &GPIO_InitStruct);

	    GPIO_InitStruct.Pin = I2C2_SDA_PIN;
	    HAL_GPIO_Init(I2C2_SDA_PORT, &GPIO_InitStruct);

	    // 4. Manually clock SCL to free SDA if stuck
	    for (int i = 0; i < 9; i++) {
	        HAL_GPIO_WritePin(I2C2_SCL_PORT, I2C2_SCL_PIN, GPIO_PIN_SET);
	        HAL_Delay(1);
	        HAL_GPIO_WritePin(I2C2_SCL_PORT, I2C2_SCL_PIN, GPIO_PIN_RESET);
	        HAL_Delay(1);
	    }

	    // 5. Generate manual STOP
	    HAL_GPIO_WritePin(I2C2_SDA_PORT, I2C2_SDA_PIN, GPIO_PIN_RESET);
	    HAL_Delay(1);
	    HAL_GPIO_WritePin(I2C2_SCL_PORT, I2C2_SCL_PIN, GPIO_PIN_SET);
	    HAL_Delay(1);
	    HAL_GPIO_WritePin(I2C2_SDA_PORT, I2C2_SDA_PIN, GPIO_PIN_SET);
	    HAL_Delay(1);

	    // 6. Reset I2C2 peripheral
	    __HAL_RCC_I2C2_FORCE_RESET();
	    HAL_Delay(2);
	    __HAL_RCC_I2C2_RELEASE_RESET();

	    // 7. Reconfigure pins back to I2C mode and reinit peripheral
	    MX_I2C2_Init();  // Must be CubeMX-generated function

}

/// Converts desired resistance to wiper value using linear model
uint8_t resistance_to_wiper(float r_target, float r_ab, float r_w) {
    // Ideal formula: wiper = ((Rtarget - Rwiper) / Rab) * 256
    float step = ((r_target - r_w) / r_ab) * 256.0f;

    if (step < 0) step = 0;
    if (step > 255) step = 255;

    return (uint8_t)(step + 0.5f);  // Round to nearest integer
}
/* USER CODE END 1 */
