/*
 * valves.c
 *
 *  Created on: May 9, 2025
 *      Author: RAGHUL
 */


#include "command_processor.h"  // HAL_GPIO functions
#include "valves.h" // Assuming valve_t is defined here

void Valve_On(valve_t valve) {
    HAL_GPIO_WritePin(valve.port, valve.pin, GPIO_PIN_SET);
   // HAL_GPIO_WritePin(valve.port, valve.pin, GPIO_PIN_RESET);
}

void Valve_Off(valve_t valve) {
    HAL_GPIO_WritePin(valve.port, valve.pin, GPIO_PIN_RESET);
  //  HAL_GPIO_WritePin(valve.port, valve.pin, GPIO_PIN_SET);
}


void LED_On(LED Led) {
    HAL_GPIO_WritePin(Led.port, Led.pin, GPIO_PIN_SET);
}

void LED_Off(LED Led) {
    HAL_GPIO_WritePin(Led.port, Led.pin, GPIO_PIN_RESET);
}
void Rising_Edge(GATE_t clk_pin)
{
 HAL_GPIO_WritePin(clk_pin.port,clk_pin.pin, GPIO_PIN_RESET);
 HAL_Delay(1);
 HAL_GPIO_WritePin(clk_pin.port,clk_pin.pin, GPIO_PIN_SET);
 HAL_Delay(1);
 HAL_GPIO_WritePin(clk_pin.port,clk_pin.pin, GPIO_PIN_RESET);
 HAL_Delay(1);
}

void Alarm_On(ALARM Alarm ) {
	HAL_GPIO_WritePin(Alarm.port, Alarm.pin, GPIO_PIN_SET);
}
void Alarm_Off(ALARM Alarm){
	HAL_GPIO_WritePin(Alarm.port, Alarm.pin, GPIO_PIN_RESET);
}
