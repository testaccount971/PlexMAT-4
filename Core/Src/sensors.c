/*
 * sensors.c
 *
 *  Created on: May 9, 2025
 *      Author: RAGHUL
 */
#include"sensors.h"

uint8_t Sensor_Read(Sensor sensor) {
    return (!HAL_GPIO_ReadPin(sensor.port, sensor.pin)); //inverted the output because we want 1 when interuupted. To change at all instance we changed here
}

void Liquid_Sensor_Check(uint8_t sensor_no)
{

    switch (sensor_no)
    {


        case 1:
                if(Sensor_Read(WashOrUniversal_Buffer_Sensor)==0)  putchr('M');
                 break;
        case 2:
               	  if(Sensor_Read(DI_Water_Sensor)==0)  putchr('M');
                   break;

        default:

            return;
    }
}

