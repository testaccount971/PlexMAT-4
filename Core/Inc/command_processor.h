/*
 * command_processor.h
 *
 *  Created on: May 8, 2025
 *      Author: RAGHUL
 */

#ifndef INC_COMMAND_PROCESSOR_H_
#define INC_COMMAND_PROCESSOR_H_

#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
#include<stdint.h>
#include"define.h"
#include"commands.h"
#include "usart.h"
#include "sensors.h"
#include "pump.h"
#include "valves.h"
#include "Rocking_Motor.h"
#include "Nozzle_Motor_Z.h"
#include "Probe_Motor_Z.h"
#include "Syringe_Motor.h"
#include "X_Motor.h"
#include "Fluid_Sense.h"
#include "i2c.h"

extern volatile uint8_t rxIndex;
extern volatile uint8_t receptionActive;
extern uint8_t commandDetected;    //when the microcontroller receives the valid command
extern uint8_t rxBuffer[RX_BUFFER_SIZE]; // adjust size as needed
extern uint8_t rxByte;
extern char command[RX_BUFFER_SIZE];  // or the appropriate size
extern unsigned int Sensor_Sensed ;

extern char *Error;
extern char *Error_Source;
extern volatile uint8_t sample_ready_flag;
extern volatile uint32_t last_capture_tick;

// Variables used in input capture callback and main loop
extern volatile uint32_t capture_val_1;     ///< First captured timer value (rising edge)
extern volatile uint32_t capture_val_2;     ///< Second captured timer value (next rising edge)


void module_executed();
void Start_Process();
void send_ACK()	;
void send_NAK()	;
void processCommand(char *command);
void delay_ms(unsigned int time);
void Send_Count(uint32_t count);


#endif /* INC_COMMAND_PROCESSOR_H_ */
