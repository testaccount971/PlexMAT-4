/*
 * pump.c
 *
 *  Created on: May 9, 2025
 *      Author: RAGHUL
 */

#include "pump.h"

void Pump_On(Pump* pump, PumpDirection direction)
{
    if (direction == CLOCKWISE) {
        HAL_GPIO_WritePin(pump->pin1_port, pump->pin1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(pump->pin2_port, pump->pin2, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(pump->pin1_port, pump->pin1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(pump->pin2_port, pump->pin2, GPIO_PIN_SET);
    }
}


void Pump_Off(Pump* pump)
{
    HAL_GPIO_WritePin(pump->pin1_port, pump->pin1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(pump->pin2_port, pump->pin2, GPIO_PIN_RESET);
}



void WashOrUniversal_Buffer_Pump_Function(unsigned int volume)
{
	Pump_On(&WashandUniversalBuffer_Pump,CLOCKWISE);
	Rising_Edge(P1_P4_GATE);
	delay_ms(volume);
	Pump_Off(&WashandUniversalBuffer_Pump);
	Rising_Edge(P1_P4_GATE);
	HAL_Delay(1000);
	Pump_On(&WashandUniversalBuffer_Pump,ANTICLOCKWISE);
	Rising_Edge(P1_P4_GATE);
	delay_ms(PUMP_REVERSE_COUNT);
	Pump_Off(&WashandUniversalBuffer_Pump);
	Rising_Edge(P1_P4_GATE);
	HAL_Delay(300);
}

void Waste_Pump_Function(unsigned int volume)
{
	Valve_On(Waste_Outlet);
	HAL_Delay(300);
	Pump_On(&Waste_RemovalPump,CLOCKWISE);
	Rising_Edge(P1_P4_GATE);
	HAL_Delay(volume);
	Pump_Off(&Waste_RemovalPump);
	Rising_Edge(P1_P4_GATE);
	HAL_Delay(300);
	Valve_Off(Waste_Outlet);
	HAL_Delay(100);

}

