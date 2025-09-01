/*
 * define.c
 *
 *  Created on: May 9, 2025
 *      Author: RAGHUL
 */
#include "define.h"

Pump WashandUniversalBuffer_Pump     = {GPIOC, GPIO_PIN_1,GPIOC, GPIO_PIN_2};
Pump Waste_RemovalPump               = {GPIOC, GPIO_PIN_3,GPIOE, GPIO_PIN_9};


valve_t DI_Probe_Inlet = {GPIOC, GPIO_PIN_5};
valve_t Waste_Outlet   = {GPIOA, GPIO_PIN_7};

GATE_t P1_P4_GATE = { GPIOD, GPIO_PIN_11 };
GATE_t P5_P7_GATE = { GPIOD, GPIO_PIN_13 };
GATE_t VL_EXLED_GATE = { GPIOD, GPIO_PIN_10 };

// Sensors
  Sensor Reagent_Probe_Position_Sensor   = {GPIOD, GPIO_PIN_1};	    //PD1
  Sensor Nozzle_Probe_Position_Sensor    = {GPIOD, GPIO_PIN_0};		//PC12
  Sensor Z_Home_Sensor 		           	 = {GPIOA, GPIO_PIN_12};    				    //PC10
  Sensor Z_EOT_Sensor 			         = {GPIOA, GPIO_PIN_11};  				        //pc11
  Sensor X_EOT_Sensor				     = {GPIOC, GPIO_PIN_9};						// PC9
  Sensor Syringe_Home_Sensor 			 = {GPIOA, GPIO_PIN_8};//PA8
  Sensor Rocking_Home_Sensor 			 = {GPIOC, GPIO_PIN_7};
  Sensor Rocking_Plate_Sensor 		     = {GPIOC, GPIO_PIN_6};
  Sensor Door_Switch                     = { GPIOD, GPIO_PIN_15 };  //PD3
  Sensor Probe_Crash_Sensor 			 = { GPIOE, GPIO_PIN_14 };


  Sensor WashOrUniversal_Buffer_Sensor   = { GPIOB, GPIO_PIN_7 };  //PB7
  Sensor DI_Water_Sensor                 = { GPIOD, GPIO_PIN_7 };  //PD7



  // Helper arrays to map device ID to GPIOs and I2C addresses
  GPIO_TypeDef* EPOT_WP_Ports[4] = {EPOT1_WP_PORT, EPOT2_WP_PORT, EPOT3_WP_PORT, EPOT4_WP_PORT};
  uint16_t      EPOT_WP_Pins[4]  = {EPOT1_WP_PIN,  EPOT2_WP_PIN,  EPOT3_WP_PIN,  EPOT4_WP_PIN};
  uint8_t       EPOT_I2C_Addrs[4] = {MCP4661_ADDR_EPOT1, MCP4661_ADDR_EPOT2, MCP4661_ADDR_EPOT3, MCP4661_ADDR_EPOT4};


// LEDs & Alarm
 LED       GreenLED           = { GPIOA, GPIO_PIN_4 };
 LED       RedLED             = { GPIOA, GPIO_PIN_5 };
 LED       YellowLED          = { GPIOA, GPIO_PIN_3 };
 ALARM     Alarm              = { GPIOA, GPIO_PIN_0 };



