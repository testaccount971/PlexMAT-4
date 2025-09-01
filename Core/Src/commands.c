/*
 * commands.c
 *
 *  Created on: May 8, 2025
 *      Author: RAGHUL
 */


//**************************SERVICE COMMANDS****************************//

//*****************Sensors****************//
char Check_Probe_Z_Home_Sensor[] ="!CZPHS()";
char Check_Probe_Z_EOT_Sensor[] ="!CZPRS()";
char Check_Probe_X_EOT_Sensor[] ="!CXRS()";
char Check_Reagent_Probe_Position_Sensor[] ="!CPPOS()";
char Check_Nozzle_Probe_Position_Sensor[] ="!CNPOS()";
char Check_Syringe_Home_Sensor[] ="!CSHS()";
char Check_Probe_Crash_Sensor[] ="!CPCS()";
char Check_Rocking_Home_Sensor[] ="!CRHS()";
char Check_Rocking_Plate_Sensor[] ="!CPS()";
char  Check_Tube_Sensor[]           = "!CTSE()";
char  Tube_Liquid_Sensor_Enable[]   = "!TLSE()";
char  Check_Frequency[]            ="!CFREQ()";

//*****************Pumps****************//

 char Check_WashOrUniversal_Buffer_Pump[] ="!CP1()";
 char Check_Waste_Pump[]                  = "!CP2()";
 char Waste_pump_On[]              		  = "!P2ON()" ;
 char Waste_pump_Off[]             		  ="!P2OFF()" ;
 char WashOrUniversal_Buffer_Pump[]       ="!P1()";

 //*****************Valves****************//
 char DI_Probe_Inlet_Valve[]        ="!CV1()";
 char Waste_Outlet_Valve[]          ="!CV2()";
 char DI_Probe_Inlet_Valve_On[]     ="!V1ON()";
 char DI_Probe_Inlet_Valve_Off[]    ="!V1OFF()";
 char Waste_Outlet_Valve_On[]   	="!V2ON()";
 char Waste_Outlet_Valve_Off[] 	    ="!V2OFF()";

 //*****************LED****************//
 char Check_Green_LED[]			    = "!CGLED()";
 char Check_Red_LED[]			    = "!CRLED()";
 char Check_Yellow_LED[]			= "!CYLED()";
 char Red_LED_On_Time[]             = "!LRED()";
 char Green_LED_On_Time[]           = "!LGRE()";
 char Yellow_LED_On_Time[]          = "!LYEL()";

 /*******Buzzer**********/
 char  Check_Alarm_ON[]			    = "!ALARM()";
 char  Alarm_OFF[]				    = "!MUTE()";

 /*******Rocking Mech**********/
 char  Rocking_motor_Run[]			= "!RON()";
 char  Rocking_motor_OFF[]			= "!ROFF()";
 char  Rocking_motor_HOME[]		    = "!RHOM()";
 char  Rocking_Count_Checker[]		= "!RCNT()";
 char  Rock_Slow[]                  = "!CRA()";


 /*************X Mech***********/
 char  X_Home[]                     ="!XHOM()";
 char  X_Move[]                     ="!XMOV()";


 /*******Z-NOZZLE Mech**********/
 char  Z_Nozzle_Home[]		       ="!ZNHOM()";
 char  Z_Nozzle_Move[]             ="!ZNMOV()";
 char  Z_Nozzle_Dispense[]         ="!NDIS()";
 char  Z_Nozzle_Aspirate[]         ="!NAS()";
 char  Z_Nozzle_Home_Distance[]    ="!ZNECC()";



 /*******Z-Probe Mech**********/
 char  Z_Probe_Home[]		       ="!ZPHOM()";
 char  Z_Probe_Move[]              ="!ZPMOV()";
 char  Z_Probe_Home_Distance[]      ="!ZPECC()";
 char  Z_Probe_Dispense[]            ="!PDIS()";

 /*******Syringe Mech**********/
 char  Syringe_Home[]		       ="!SHOM()";
 char  Syringe_Move[]              ="!SMOV()";
 char  Air_Gap[]                   ="!AIRG()";

 /*******Hybrid Mech**********/
 char  Move_Down_Fluid_sense[]	    ="!MDFS()";
 char  Complete_Syringe_Prime[]     ="!SPRI()";
 char  Fluid_Pickup[]               ="!FLPK()";
 char  Prime_Pump[]                 ="!PPRI()";


 /*******ADC**********/
 char  Read_Sensor_Voltage[]          ="!RSEN()";

 /*******EPOT**********/
 char  Write_EPOT_Resistance[]        ="!WEPOT()";

 /*******Version**********/
 char Firmware_Version[]          = "!VER()";


