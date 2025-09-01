/*
 * Rocking_Motor.h
 *
 *  Created on: May 19, 2025
 *      Author: RAGHUL
 */

#ifndef INC_ROCKING_MOTOR_H_
#define INC_ROCKING_MOTOR_H_



#include "tim.h"
#include "main.h"
#include "string.h"


// External variable declarations
extern TIM_HandleTypeDef htim3;
extern volatile uint32_t pulse_count;
extern volatile int plate_cnt;

extern uint32_t Rocking_motor_pulses;
extern uint32_t home_cnt;  // Declaration for external use





// Define motor control macros


// Rocking motor functions
void Start_Rocking_Motor(int Rocking_motor_speed, int Rocking_motor_pulses);
void Stop_Rocking_Motor();
void Rocking_Slow(int Rocking_motor_speed, int Rocking_motor_pulses);
void Home_Rocking_Motor(uint32_t Maximum_Pulses);
void Rocking_Count_Function();

// Low-level utility functions
void Start_PWM(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t frequency, uint32_t duty_cycle, uint32_t num_pulses);



#endif /* INC_ROCKING_MOTOR_H_ */
