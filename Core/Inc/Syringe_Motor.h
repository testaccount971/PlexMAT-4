/*
 * Syringe_Motor.h
 *
 *  Created on: May 21, 2025
 *      Author: RAGHUL
 */

#ifndef INC_SYRINGE_MOTOR_H_
#define INC_SYRINGE_MOTOR_H_

#include "tim.h"
#include "main.h"
#include "string.h"


// External variable declarations
extern TIM_HandleTypeDef htim3;
extern volatile uint32_t pulse_count;






// Define motor control macros


// Rocking motor functions
void Start_Syringe_Motor();
void Stop_Syringe_Motor();
void Home_Syringe_Motor(uint32_t Maximum_Pulses);
void Move_Syringe_Motor(int Direction, int Disatance );

// Low-level utility functions
void Start_PWM(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t frequency, uint32_t duty_cycle, uint32_t num_pulses);

#endif /* INC_SYRINGE_MOTOR_H_ */
