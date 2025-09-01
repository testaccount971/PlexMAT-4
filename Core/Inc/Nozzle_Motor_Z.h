/*
 * Nozzle_Motor_Z.h
 *
 *  Created on: May 20, 2025
 *      Author: RAGHUL
 */



#include "tim.h"
#include "main.h"
#include "string.h"


// External variable declarations
extern TIM_HandleTypeDef htim3;
extern volatile uint32_t pulse_count;






// Define motor control macros


// Rocking motor functions
void Start_Z_Nozzle_Motor();
void Stop_Z_Nozzle_Motor();
void Home_Z_Nozzle_Motor(uint32_t Maximum_Pulses);
void Move_Z_Nozzle_Motor(int Direction, int Disatance );
void Home_Z_Nozzle_Motor_Distance(uint32_t Maximum_Pulses);


// Low-level utility functions
void Start_PWM(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t frequency, uint32_t duty_cycle, uint32_t num_pulses);

