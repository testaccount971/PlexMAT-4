/*
 * X_Motor.h
 *
 *  Created on: May 22, 2025
 *      Author: RAGHUL
 */

#ifndef INC_X_MOTOR_H_
#define INC_X_MOTOR_H_

#include "tim.h"
#include "main.h"
#include "string.h"


// External variable declarations
extern TIM_HandleTypeDef htim3;
extern volatile uint32_t pulse_count;






// Define motor control macros


// Rocking motor functions
void Start_X_Motor();
void Stop_X_Motor();
void Home_X_Motor(int Direction, uint32_t Maximum_Pulses);

void Move_X_Motor(int Direction,int distance_pulse,unsigned int Num_Of_Strips);
void Move_X_Motor_Next_Position(int Direction,int distance_pulse,unsigned int StripOrNozzle);


#endif /* INC_X_MOTOR_H_ */
