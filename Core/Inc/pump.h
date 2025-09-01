/*
 * pump.h
 *
 *  Created on: May 9, 2025
 *      Author: RAGHUL
 */

#ifndef INC_PUMP_H_
#define INC_PUMP_H_
#include "command_processor.h"
void Pump_On(Pump* pump, PumpDirection direction);
void Pump_Off(Pump* pump);
void WashOrUniversal_Buffer_Pump_Function(unsigned int volume);
void Waste_Pump_Function(unsigned int volume);

#endif /* INC_PUMP_H_ */
