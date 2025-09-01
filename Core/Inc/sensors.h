/*
 * sensors.h
 *
 *  Created on: May 9, 2025
 *      Author: RAGHUL
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_
#include "command_processor.h"

uint8_t Sensor_Read(Sensor sensor);
void Liquid_Sensor_Check(uint8_t sensor_no);

#endif /* INC_SENSORS_H_ */
