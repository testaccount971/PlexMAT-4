/*
 * Valves.h
 *
 *  Created on: May 9, 2025
 *      Author: RAGHUL
 */

#ifndef INC_VALVES_H_
#define INC_VALVES_H_
#include "define.h"

void Valve_On(valve_t valve);
void Valve_Off(valve_t valve);

void LED_On(LED Led) ;
void LED_Off(LED Led);

void Alarm_On(ALARM Alarm );
void Alarm_Off(ALARM Alarm);
void Rising_Edge(GATE_t clk_pin);
#endif /* INC_VALVES_H_ */
