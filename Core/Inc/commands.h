/*
 * commands.h
 *
 *  Created on: May 8, 2025
 *      Author: RAGHUL
 */

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_


//**************************SERVICE COMMANDS****************************//

//*****************Sensors****************//
extern char Check_Probe_Z_Home_Sensor[];
extern char Check_Probe_Z_EOT_Sensor[] ;
extern char Check_Probe_X_EOT_Sensor[];
extern char Check_Reagent_Probe_Position_Sensor[] ;
extern char Check_Nozzle_Probe_Position_Sensor[];
extern char Check_Syringe_Home_Sensor[];
extern char Check_Probe_Crash_Sensor[];
extern char Check_Rocking_Home_Sensor[];
extern char Check_Rocking_Plate_Sensor[];
extern char Check_Tube_Sensor[];
extern char  Check_Tube_Sensor[];
extern char  Tube_Liquid_Sensor_Enable[];
extern char  Check_Frequency[];

//*****************Pumps****************//

extern char Check_WashOrUniversal_Buffer_Pump[];
extern char Check_Waste_Pump[];
extern char Waste_pump_On[] ;
extern char Waste_pump_Off[] ;
extern char WashOrUniversal_Buffer_Pump[];

//*****************Valves****************//
extern char DI_Probe_Inlet_Valve[];
extern char Waste_Outlet_Valve[];
extern char DI_Probe_Inlet_Valve_On[] ;
extern char DI_Probe_Inlet_Valve_Off[];
extern char Waste_Outlet_Valve_On[];
extern char Waste_Outlet_Valve_Off[];


//*****************LED****************//
extern char Check_Green_LED[];
extern char Check_Red_LED[];
extern char Check_Yellow_LED[];
extern char Red_LED_On_Time[] ;
extern char Green_LED_On_Time[];
extern char Yellow_LED_On_Time[];

/*******Buzzer**********/
extern char  Check_Alarm_ON[];
extern char  Alarm_OFF[];

/*******Rocking Mech**********/
extern char  Rocking_motor_Run[];
extern char  Rocking_motor_OFF[];
extern char  Rocking_motor_HOME[];
extern char  Rocking_Count_Checker[] ;
extern char  Rock_Slow[]  ;


/*************X Mech***********/
extern char  X_Home[];
extern char  X_Move[];

/*******Z-NOZZLE Mech**********/
extern char  Z_Nozzle_Home[];
extern char  Z_Nozzle_Move[];
extern char  Z_Nozzle_Dispense[];
extern char  Z_Nozzle_Aspirate[];
extern char  Z_Nozzle_Home_Distance[];

/*******Z-Probe Mech**********/
extern char  Z_Probe_Home[];
extern char  Z_Probe_Move[];
extern char  Z_Probe_Home_Distance[];
extern  char  Z_Probe_Dispense[];

/*******Syringe Mech**********/
extern char  Syringe_Home[];
extern char  Syringe_Move[];
extern char  Air_Gap[];

/*******Hybrid Mech**********/
extern char  Move_Down_Fluid_sense[];
extern char  Complete_Syringe_Prime[];
extern char  Fluid_Pickup[];
extern char  Prime_Pump[];


/*******ADC**********/
extern char  Read_Sensor_Voltage[];

/*******EPOT**********/
extern char  Write_EPOT_Resistance[];



/*******Version**********/
extern char Firmware_Version[];



#endif /* INC_COMMANDS_H_ */
