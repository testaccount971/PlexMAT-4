/*
 * command_processor.c
 *
 *  Created on: May 8, 2025
 *      Author: RAGHUL
 *
 */

#include "command_processor.h"

uint8_t rxByte;                // Temporary buffer for 1-byte reception
uint8_t rxBuffer[RX_BUFFER_SIZE]; // Main buffer for message storage
char command[RX_BUFFER_SIZE]; // For command stroage
char *Error ="00";

uint8_t commandDetected  =0;    //when the microcontroller receives the valid command
int Tube_Liquid_sensor_Activate=1;

volatile uint8_t rxIndex;
volatile uint8_t receptionActive;


// Variables to store capture values
volatile uint32_t capture_val_1 = 0;
volatile uint32_t capture_val_2 = 0;
volatile uint8_t capture_ready = 0;
volatile uint32_t last_capture_tick = 0;



#define SIGNAL_TIMEOUT_MS   100

void Start_Process()
{

	 if(commandDetected == 1)
		  {
			  processCommand(command);
			  commandDetected=0;
		  }

}

int CompareToBrace( char* definedCommand)
{
	  char extractedDefinedCommand[20];
	  char extractedGUICommand[20];
	// Find the '(' character, which indicates the start of parameters
	    char *position = strchr(definedCommand, '(');
	    if (position != NULL) {
	        // Calculate the length of the command name (everything before '(')
	        size_t len = position - definedCommand;

	        // Copy the command name into the output buffer
	        strncpy(extractedDefinedCommand, definedCommand, len);

	        // Ensure the copied string is null-terminated
	        extractedDefinedCommand[len] = '\0';

	    }

	   	// Find the '(' character, which indicates the start of parameters
	   	   position = strchr(command, '(');
	   	    if (position != NULL) {
	   	        // Calculate the length of the command name (everything before '(')
	   	        size_t len = position - command;

	   	        // Copy the command name into the output buffer
	   	        strncpy(extractedGUICommand, command, len);

	   	        // Ensure the copied string is null-terminated
	   	     extractedGUICommand[len] = '\0';

	   	    }
//	   	 memset(extractedDefinedCommand, 0, sizeof(extractedDefinedCommand));
//	      HAL_UART_Transmit(&huart3, (uint8_t *)extractedDefinedCommand,strlen(extractedDefinedCommand), HAL_MAX_DELAY);
//	      HAL_UART_Transmit(&huart3, (uint8_t *)extractedGUICommand,strlen(extractedGUICommand), HAL_MAX_DELAY);

	    if (strcmp(extractedDefinedCommand, extractedGUICommand) == 0)
	       {
	    	  memset(extractedDefinedCommand, 0, sizeof(extractedDefinedCommand));
	    	  memset(extractedGUICommand, 0, sizeof(extractedGUICommand));
	    	  HAL_UART_Transmit(&huart3, (uint8_t *)command, strlen((const char *)command), HAL_MAX_DELAY); //echo command
	          return 1;
	       }
	    else
	       {
	    	  memset(extractedDefinedCommand, 0, sizeof(extractedDefinedCommand));
	          memset(extractedGUICommand, 0, sizeof(extractedGUICommand));
	          return 0;
	       }
}
void send_ACK()								//Sending Acknowledgment
{
	putchr(0x06); // send ACK
	putchr(0x0D); // CR
}
void send_NAK()								//Sending NoAcknowledgement
{
	putchr(0x15); // send NAK
	putchr(0x0D); //CR
	delay_ms(200);

}
void module_executed()
{
	if(strcmp("00",Error)!=0)
			{
				putstr(Error);
			}
	    putchr('$');
		Error="00";   //Clear Error variable
		Error_Source = "None";
}

void Send_Count(uint32_t count) {
    char buffer[16];  // Buffer to hold the converted string (enough for 32-bit int + newline)

    // Convert the integer to a string with carriage return and newline
    int length = snprintf(buffer, sizeof(buffer), "%lu", (long)count);

    // Transmit the string via UART2 (blocking mode)
    HAL_UART_Transmit(&huart3, (uint8_t *)buffer, length, HAL_MAX_DELAY);
}
void processCommand(char *command)
{

	 if((CompareToBrace(Firmware_Version))==1)//		  char Firmware_Version[]          = "!VERS()";
	 		{
	 			 send_ACK();
	 			 putstr("V3.0");
	 			 putchr('$');
	 		}
	 else if((CompareToBrace(Check_Probe_Z_Home_Sensor))==1)//		 Check_Probe_Z_Home_Sensor[] ="!CZPHS()";
		{
			 send_ACK();
			 if(Sensor_Read(Z_Home_Sensor))putchr('1');
			 else putchr('0');
			 putchr('$');
		}
	else if((CompareToBrace(Check_Probe_Z_EOT_Sensor))==1)//		char Check_Probe_Z_EOT_Sensor[] ="CZPRS()";
		{
			send_ACK();
			if(Sensor_Read(Z_EOT_Sensor))putchr('1');
			else putchr('0');
		    putchr('$');
		}
	else if((CompareToBrace(Check_Probe_X_EOT_Sensor))==1)//		char Check_Probe_X_EOT_Sensor[] ="!CXRS()";
		{
			send_ACK();
			if(Sensor_Read(X_EOT_Sensor))putchr('1');
			else putchr('0');
		    putchr('$');
		}

	else if((CompareToBrace(Check_Reagent_Probe_Position_Sensor))==1)//		char Check_Reagent_Probe_Position_Sensor[] ="!CRPOS()";
		{
			send_ACK();
			if(Sensor_Read(Reagent_Probe_Position_Sensor))putchr('1');
			else putchr('0');
		    putchr('$');
		}

	else if((CompareToBrace(Check_Nozzle_Probe_Position_Sensor))==1)//		char Check_Nozzle_Probe_Position_Sensor[] ="!CNPOS()";
		{
			send_ACK();
			 if(Sensor_Read(Nozzle_Probe_Position_Sensor))putchr('1');
			 else putchr('0');
		    putchr('$');
		}

	else if((CompareToBrace(Check_Syringe_Home_Sensor))==1)//		char Check_Syringe_Home_Sensor[] ="!CSHS()";
		{
			send_ACK();
			if(Sensor_Read(Syringe_Home_Sensor))putchr('1');
			else putchr('0');
		    putchr('$');
		}

	else if((CompareToBrace(Check_Probe_Crash_Sensor))==1)//		char Check_Probe_Crash_Sensor[] ="!CPCS()";
		{
			send_ACK();
			if(!Sensor_Read(Probe_Crash_Sensor))putchr('1');
			else putchr('0');
		    putchr('$');
		}
	else if((CompareToBrace(Check_Rocking_Home_Sensor))==1)//		char Check_Rocking_Home_Sensor[] ="!CRHS()";
		{
			send_ACK();
			if(Sensor_Read(Rocking_Home_Sensor))putchr('1');
			else putchr('0');
		    putchr('$');
		}
	else if((CompareToBrace(Check_Rocking_Plate_Sensor))==1)//		char Check_Rocking_Home_Sensor[] ="!CRHS()";
		{
			send_ACK();
			if(Sensor_Read(Rocking_Plate_Sensor))putchr('1');
			else putchr('0');
		    putchr('$');
		}
	 else if(((CompareToBrace(Check_Tube_Sensor))==1)) //har  Check_Tube_Sensor[]           = "!CTSE()";
		 			 {
		 			 unsigned int Sensor_No	    = 0;
		 			 send_ACK();
		 			 int extracted = sscanf(command, "!CTSE(%d)",&Sensor_No);
		 			 if (extracted != 1) {
		 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
		 				 return;
		 				}
		 			 if(Tube_Liquid_sensor_Activate)
		 				 {

		 				 Liquid_Sensor_Check(Sensor_No);
		 				 }
		 			 else  ;
		 			 module_executed();
		 			  }
		 else if(((CompareToBrace(Tube_Liquid_Sensor_Enable))==1)) //char  Tube_Liquid_sensor_Enable     = "!TLSE()";
		 	 			 {

		 	 			 send_ACK();
		 	 			 int extracted = sscanf(command, "!TLSE(%d)",&Tube_Liquid_sensor_Activate);
		 	 			 if (extracted != 1) {
		 	 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
		 	 				 return;
		 	 				}
		 	 			 module_executed();
		 	 			 }
	else if((CompareToBrace(Check_WashOrUniversal_Buffer_Pump))==1)//	 char WashOrUniversal_Buffer_Pump ="!CP1";
		{
		       int volume=0;
			   send_ACK();
				int extracted = sscanf(command, "!CP1(%d)", &volume);
				if (extracted != 1) {
				HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
				return;
				}
				Pump_On(&WashandUniversalBuffer_Pump,CLOCKWISE);
				Rising_Edge(P1_P4_GATE);
				delay_ms(volume);
				Pump_Off(&WashandUniversalBuffer_Pump);
				Rising_Edge(P1_P4_GATE);
				HAL_Delay(1000);
				Pump_On(&WashandUniversalBuffer_Pump,ANTICLOCKWISE);
				Rising_Edge(P1_P4_GATE);
				delay_ms(volume);
				Pump_Off(&WashandUniversalBuffer_Pump);
				Rising_Edge(P1_P4_GATE);
				module_executed();
		}
	else if((CompareToBrace(Check_Waste_Pump))==1)//	 char Waste_Pump                  ="CP2";
		{
		    int volume=0;
		    send_ACK();
			int extracted = sscanf(command, "!CP2(%d)", &volume);
			if (extracted != 1) {
			HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
			return;
			}
			Pump_On(&Waste_RemovalPump,CLOCKWISE);
			Rising_Edge(P1_P4_GATE);
			delay_ms(volume);
			Pump_Off(&Waste_RemovalPump);
			Rising_Edge(P1_P4_GATE);
			HAL_Delay(1000);
			Pump_On(&Waste_RemovalPump,ANTICLOCKWISE);
			Rising_Edge(P1_P4_GATE);
			delay_ms(volume);
			Pump_Off(&Waste_RemovalPump);
			Rising_Edge(P1_P4_GATE);
			module_executed();
		}


	 else if((CompareToBrace(Waste_pump_On))==1)//	 char Waste_pump_On[]                = "!P2ON()" ;
	 		{
	 			send_ACK();
	 			Pump_On(&Waste_RemovalPump,CLOCKWISE);
	 			Rising_Edge(P1_P4_GATE);
	 			HAL_Delay(200);
	 			module_executed();
	 		}
	else if((CompareToBrace(Waste_pump_Off))==1)//	 char Waste_pump_Off[]               ="!P2OFF()" ;
		{
			send_ACK();
			Pump_Off(&Waste_RemovalPump);
			Rising_Edge(P1_P4_GATE);
			HAL_Delay(500);
			module_executed();
		}
	else if((CompareToBrace(WashOrUniversal_Buffer_Pump))==1)//		 char WashOrUniversal_Buffer_Pump[]   ="!P1()";
		{
			int volume=0;
			send_ACK();
			int extracted = sscanf(command, "!P1(%d)", &volume);
			if (extracted != 1) {
			HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
			return;
			}
			Pump_On(&WashandUniversalBuffer_Pump,CLOCKWISE);
			Rising_Edge(P1_P4_GATE);
			delay_ms(volume);
			Pump_Off(&WashandUniversalBuffer_Pump);
			Rising_Edge(P1_P4_GATE);
			HAL_Delay(1000);
			Pump_On(&WashandUniversalBuffer_Pump,ANTICLOCKWISE);
			Rising_Edge(P1_P4_GATE);
			delay_ms(volume);
			Pump_Off(&WashandUniversalBuffer_Pump);
			Rising_Edge(P1_P4_GATE);
			module_executed();
		}
	else if(((CompareToBrace(Yellow_LED_On_Time))==1))//	char  Yellow_LED_ON                 = "!LYEL()";
			{
			 send_ACK();
			 LED_Off(YellowLED);
			 // yellow led
			 LED_On(RedLED);
			 LED_On(GreenLED);
			 Rising_Edge(VL_EXLED_GATE);
			 module_executed();
			 }
		else if(((CompareToBrace(Green_LED_On_Time))==1))//	char  Green_LED_On_Time                  = "!LGRE()";
			{
			 send_ACK();
			 LED_Off(YellowLED);
			 // yellow led
			 LED_Off(RedLED);
			 LED_Off(GreenLED);
			 Rising_Edge(VL_EXLED_GATE);
			 LED_On(GreenLED);
			 Rising_Edge(VL_EXLED_GATE);
			 module_executed();
			 }
		else if(((CompareToBrace(Check_Green_LED))==1))//	  Check_Green_LED[]			    = "!CGLED()";
			{
			 send_ACK();
			 LED_Off(RedLED);
			 Rising_Edge(VL_EXLED_GATE);
			 LED_Off(YellowLED);
			 Rising_Edge(VL_EXLED_GATE);
			 for(int i=1;i<=3;i++)
			 {
				 LED_On(GreenLED);
				 Rising_Edge(VL_EXLED_GATE);
				 HAL_Delay(1000);
				 LED_Off(GreenLED);
				 Rising_Edge(VL_EXLED_GATE);
				 HAL_Delay(1000);
			 }
			 LED_On(GreenLED);
			 Rising_Edge(VL_EXLED_GATE);
			 HAL_Delay(500);
			 module_executed();
			 }
		else if(((CompareToBrace(Check_Red_LED))==1))//	  Check_Red_LED[]			    = "!CRLED()";
		    {
			 send_ACK();
			 LED_Off(YellowLED);
			 Rising_Edge(VL_EXLED_GATE);
			 LED_Off(GreenLED);
			 Rising_Edge(VL_EXLED_GATE);
			 for(int i=1;i<=3;i++)
			 {
				 LED_On(RedLED);
				 Rising_Edge(VL_EXLED_GATE);
				 HAL_Delay(1000);
				 LED_Off(RedLED);
				 Rising_Edge(VL_EXLED_GATE);
				 HAL_Delay(1000);
			 }
			 LED_On(GreenLED);
			 Rising_Edge(VL_EXLED_GATE);
			 HAL_Delay(500);
			module_executed();
			}
	  else if(((CompareToBrace(Check_Yellow_LED))==1))//	  Check_Yellow_LED[]			    = "!CYLED()";
	        {
			 send_ACK();
			 LED_Off(YellowLED);
			 Rising_Edge(VL_EXLED_GATE);
			 for(int i=1;i<=3;i++)
			 {
				 LED_On(RedLED);
				 LED_On(GreenLED);
				 Rising_Edge(VL_EXLED_GATE);
				 HAL_Delay(1000);
				 LED_Off(RedLED);
				 LED_Off(GreenLED);
				 Rising_Edge(VL_EXLED_GATE);
				 HAL_Delay(1000);
			 }
			 LED_On(GreenLED);
			 Rising_Edge(VL_EXLED_GATE);
			 HAL_Delay(1000);
			 module_executed();
			 }
		else if(((CompareToBrace(Check_Alarm_ON))==1)) // ALARM() if 0-> Buzzer check, 1-> continouse ON (error), 2-> rhyme
			{
			unsigned int alarm_type=0 ;
	//		   unsigned int loop=0;
				send_ACK();
				int extracted = sscanf(command, "!ALARM(%d)", &alarm_type);
				if (extracted != 1) {
				HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, 100);
				}

				if(alarm_type ==0) // in service mode alarm/buzzer check
					{
					 LED_Off(YellowLED);
					 LED_Off(GreenLED);
					 LED_On(RedLED);
				     Alarm_On(Alarm);
					 Rising_Edge(VL_EXLED_GATE);
					}

				else if(alarm_type ==1){
					LED_Off(YellowLED);
					 LED_Off(GreenLED);
					 LED_On(RedLED);
					Alarm_On(Alarm); // if error state continoue alarm/ buzer ON
					Rising_Edge(VL_EXLED_GATE);
				}

				else if(alarm_type ==2)
					{

					 LED_Off(YellowLED);
					 LED_Off(GreenLED);
					 LED_On(RedLED);
					Alarm_On(Alarm);
					Rising_Edge(VL_EXLED_GATE);
			       }
				module_executed();
			}
		 else if(((CompareToBrace(Alarm_OFF))==1)) // MUTE()
			{
				send_ACK();
				Alarm_Off(Alarm);
				LED_Off(RedLED);
				Rising_Edge(VL_EXLED_GATE);
				LED_Off(YellowLED);
				Rising_Edge(VL_EXLED_GATE);
				LED_On(RedLED);
				LED_On(GreenLED);
				Rising_Edge(VL_EXLED_GATE);
				HAL_Delay(100);
				module_executed();
			}
	else if((CompareToBrace(DI_Probe_Inlet_Valve))==1)//	char DI_Probe_Inlet[] ="!CV1()";
		{
			send_ACK();
			Valve_On(DI_Probe_Inlet);
			Rising_Edge(VL_EXLED_GATE);
			HAL_Delay(3000);
			Valve_Off(DI_Probe_Inlet);
			Rising_Edge(VL_EXLED_GATE);
		    putchr('$');
		}
	else if((CompareToBrace(Waste_Outlet_Valve))==1)//	char Waste_Outlet[]   ="!CV2()";
		{
			send_ACK();
			Valve_On(Waste_Outlet);
			Rising_Edge(VL_EXLED_GATE);
			HAL_Delay(3000);
			Valve_Off(Waste_Outlet);
			Rising_Edge(VL_EXLED_GATE);
		    putchr('$');
		}
	else if((CompareToBrace(DI_Probe_Inlet_Valve_On))==1)//	char DI_Probe_Inlet_On[] ="!V1ON()";
		{
			send_ACK();
			Valve_On(DI_Probe_Inlet);
			Rising_Edge(VL_EXLED_GATE);
			HAL_Delay(500);
		    putchr('$');
		}
	else if((CompareToBrace(DI_Probe_Inlet_Valve_Off))==1)//	char DI_Probe_Inlet_Off[] ="!V1OFF()";
			{
				send_ACK();
				Valve_Off(DI_Probe_Inlet);
				Rising_Edge(VL_EXLED_GATE);
				HAL_Delay(500);
			    putchr('$');
			}
	else if((CompareToBrace(Waste_Outlet_Valve_On))==1)//	char DI_Probe_Inlet_On[] ="!V2ON()";
			{
				send_ACK();
				Valve_On(Waste_Outlet);
				Rising_Edge(VL_EXLED_GATE);
				HAL_Delay(500);
			    putchr('$');
			}
	else if((CompareToBrace(Waste_Outlet_Valve_Off))==1)//	char DI_Probe_Inlet_Off[] ="!V2OFF()";
			{
				send_ACK();
				Valve_Off(Waste_Outlet);
				Rising_Edge(VL_EXLED_GATE);
				HAL_Delay(500);
				putchr('$');
			}

	 else if(((CompareToBrace(Rocking_motor_Run))==1))//char  Rocking_motor_Run[]			= "!RON()";
			 {

			   send_ACK();
			   Start_Rocking_Motor(RockingFrequencyNormal, 0);
			   module_executed();
			 }
		 else if(((CompareToBrace(Rocking_motor_OFF))==1))//char  Rocking_motor_OFF[]			= "!ROFF()";
		 {
			 send_ACK();
			 Stop_Rocking_Motor();
			 module_executed();
		  }
		 else if(((CompareToBrace(Rocking_motor_HOME))==1))//char  Rocking_motor_HOME[]		    = "!RHOM()";
		 {
			  unsigned int Maximum_Pulses=0;
			   send_ACK();
			   int extracted = sscanf(command, "!RHOM(%d)",&Maximum_Pulses);
				if (extracted != 1) {
				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
				 return;
				}
			   Home_Rocking_Motor( Maximum_Pulses);
		       module_executed();
		 }
		 else if(((CompareToBrace(Rocking_Count_Checker))==1))//char  Rocking_Count_Checker[]				= "!RCNT()";
		  {
			  send_ACK();
			  Rocking_Count_Function();
			  module_executed();
		  }
		 else if(((CompareToBrace(Rock_Slow))==1))//char  Rock_Slow[]           = "!CRA()";
			 {
			 send_ACK();
			 Rocking_Slow(RockingFrequencySlow,0);
			 module_executed();
			  }

	     else if(((CompareToBrace(Z_Nozzle_Home))==1))//  char  Z_Nozzle_Home[]		       = "!ZNHOM()";
			 {
	    	 unsigned int Maximum_Pulses=0;
			 send_ACK();
			   int extracted = sscanf(command, "!ZNHOM(%d)",&Maximum_Pulses);
				if (extracted != 1) {
				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
				 return;
				}
			   Home_Z_Nozzle_Motor( Maximum_Pulses);
			   module_executed();
			  }

	 else if(((CompareToBrace(Z_Nozzle_Move))==1))//  	 char  Z_Nozzle_Move[]             ="!ZNMOV()";
	 			 {
	 	    	 unsigned int Direction=0,Distance=0;

	 			 send_ACK();
	 			 //Error="C"; // Init. no error condition
	 			   int extracted = sscanf(command, "!ZNMOV(%d,%d)",&Direction, &Distance);
	 				if (extracted != 2) {
	 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
	 				 return;
	 				}
	 				Move_Z_Nozzle_Motor(Direction, Distance);
	 			   module_executed();
	 			  }

	 else if(((CompareToBrace(Z_Nozzle_Dispense))==1))//  	 char  Z_Nozzle_Dispense[]             ="!NDIS()";
		 			 {
		 	    	 unsigned int Number_Of_Strips=0;
		 	    	 unsigned int Nozzle_Dispense_Height=0;
		 	    	 unsigned int Volume=0;
		 	    	 unsigned int Strip_Position=2;

		 			 send_ACK();
		 			   int extracted = sscanf(command, "!NDIS(%d,%d,%d)",&Number_Of_Strips, &Nozzle_Dispense_Height,&Volume);
		 				if (extracted != 3) {
		 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
		 				 return;
		 				}
					 if(Tube_Liquid_sensor_Activate)
						 {
						       if(Sensor_Read(WashOrUniversal_Buffer_Sensor)==0) Error="M";
						 }
					 else  ;
					 if(strcmp(Error,"00")==0)
					 {
								//step 2 move nozzle down
								Move_Z_Nozzle_Motor(NOZZLE_DOWN_DIR, Nozzle_Dispense_Height);
								if(strcmp(Error,"00")==0)
								{
									//step 3 dispaense volume
									WashOrUniversal_Buffer_Pump_Function(Volume);

									while((Number_Of_Strips>1)&&(Strip_Position <=Number_Of_Strips))
									{

										//step4 move to next strip
											Move_X_Motor_Next_Position(STRIP_DIRECTION,300,NOZZLE);
											if(strcmp(Error,"00")==0)
											{
												// step 5 dispense volume
												 WashOrUniversal_Buffer_Pump_Function(Volume);
												 Strip_Position++;
											}
											else
											{
												break;
											}

									}
									//step6 Nozzle home
									if(strcmp(Error,"00")==0)
									{
									   Home_Z_Nozzle_Motor(NOZZLE_HOME_MAX_COUNT);
									}
								}
					 }
	//	 			if(strcmp(Error,"00")!=0)
	//	 			{
	//	 				Home_Z_Nozzle_Motor(NOZZLE_HOME_MAX_COUNT);
		 				//Add Xhom function
	//	 			}
				   module_executed();
				  }
	 else if(((CompareToBrace(Z_Probe_Dispense))==1))//  	  char  Z_Probe_Dispense[]            ="!PDIS()";
		 			 {
		 	    	 unsigned int Number_Of_Strips=0;
		 	    	 unsigned int Probe_Dispense_Height=0;
		 	    	 unsigned int Airgap=0;
		 	    	 unsigned int Volume=0;
		 	    	 unsigned int Strip_Position=2;
		 	    	 unsigned int Maximum_Pulses=700;

		 	    	send_ACK();
		 	    	//Error="P"; // Init. no error condition
		 	    	int extracted = sscanf(command, "!PDIS(%d,%d,%d,%d)", &Number_Of_Strips, &Probe_Dispense_Height, &Airgap, &Volume);
		 	    	if (extracted != 4)
						{
							HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
							return;
						}

		 	    	// Step 1: Probe move down
		 	    	Move_Z_Probe_Motor(1, Probe_Dispense_Height);
		 	    	if (strcmp(Error, "00") == 0)
		 	    		{
							// Step 2: Valve ON and Airgap
							Valve_On(DI_Probe_Inlet);  // May not req. Need to recheck
							Rising_Edge(VL_EXLED_GATE);
							HAL_Delay(500);

					//		Move_Syringe_Motor(0, Airgap);

							if (strcmp(Error, "00") == 0)
								{
									// Step 3: Initial Volume Dispense
									Move_Syringe_Motor(0, Volume);
									if (strcmp(Error, "00") == 0)
										{
										    // Step 4: Loop through strips
											while ((Number_Of_Strips > 1) && (Strip_Position <= Number_Of_Strips))
												{
													Move_X_Motor_Next_Position(STRIP_DIRECTION, 300, PROBE);
													if (strcmp(Error, "00") == 0)
														{
															Move_Syringe_Motor(0, Volume);
															if (strcmp(Error, "00") == 0)
																{
																	Strip_Position++;
																}
															else
																{
																  break;
																}
														}
													 else
														 {
														  break;
														 }
													}

													// Step 5: Valve OFF
													Valve_Off(DI_Probe_Inlet);
													HAL_Delay(500);

													// Step 6: Probe Home
													if (strcmp(Error, "00") == 0) Home_Z_Probe_Motor(Maximum_Pulses);
										}
								}
							}

		 	    	module_executed();

		}

	 else if(((CompareToBrace(Complete_Syringe_Prime))==1))//  	 char  Complete_Syringe_Prime[]     ="!SPRI()"
		 			 {
		 	    	 unsigned int Number_of_prime_cycle=0;
		 	    	 unsigned int Probe_Prime_Height=0;
		 			 send_ACK();
		 			 //Error="P";
		 			   int extracted = sscanf(command, "!SPRI(%d,%d)",&Number_of_prime_cycle, &Probe_Prime_Height);
		 				if (extracted != 2) {
		 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
		 				 return;
		 				}

		 			//z probe hoem
		 			 Home_Z_Probe_Motor( PROBE_HOME_MAX_COUNT);

		 			 if(strcmp(Error, "00") == 0)
		 			 {
		 				Valve_Off(DI_Probe_Inlet);

						Rising_Edge(VL_EXLED_GATE);

						HAL_Delay(300);

						 //syringe_home()
						 Home_Syringe_Motor(SYRINGE_HOME_MAX_COUNT);

						 if(strcmp(Error, "00") == 0)
						 {

							 //Move probe down
							Move_Z_Probe_Motor(PROBE_DOWN_DIR , Probe_Prime_Height);

							 if(strcmp(Error, "00") == 0)
							 {

								//waste valve on
								Pump_On(&Waste_RemovalPump,CLOCKWISE);

								Rising_Edge(P1_P4_GATE);
								HAL_Delay(300);
								//to get the DI water inside swithoff the valve
								////switch off di probe inlet valve
								Valve_Off(DI_Probe_Inlet);

								Rising_Edge(VL_EXLED_GATE);

								HAL_Delay(300);
								for(int i=1;i<=Number_of_prime_cycle;i++){

									Move_Syringe_Motor(1,SYRINGE_EOT_MAX_COUNT);

									 if(strcmp(Error, "00") == 0)
									 {

										HAL_Delay(200);
										Valve_On(DI_Probe_Inlet);
										Rising_Edge(VL_EXLED_GATE);
										HAL_Delay(300);
										Home_Syringe_Motor(SYRINGE_HOME_MAX_COUNT);
										 if(strcmp(Error, "00") != 0) break;

										 if(strcmp(Error, "00") != 0) break;
										Valve_Off(DI_Probe_Inlet);
										Rising_Edge(VL_EXLED_GATE);
										HAL_Delay(300);
									 }

									 else
										 {

										    break;
										 }
								}
								//switchoff waste pump``
								Pump_Off(&Waste_RemovalPump);
								Rising_Edge(P1_P4_GATE);
								HAL_Delay(300);
								 if(strcmp(Error, "00") == 0) Home_Z_Probe_Motor( PROBE_HOME_MAX_COUNT);

								 if(strcmp(Error, "00") == 0)
									 {

									 Home_Syringe_Motor(SYRINGE_HOME_MAX_COUNT);
									 }
							 }
						 }
					 }

		 			 if(strcmp(Error, "00") != 0)
		 			 {

		 			//	Home_Syringe_Motor(SYRINGE_HOME_MAX_COUNT);
		 			//	Home_Z_Probe_Motor( PROBE_HOME_MAX_COUNT);
		 				Pump_Off(&Waste_RemovalPump);
		 				Rising_Edge(P1_P4_GATE);
		 				HAL_Delay(300);




		 				Valve_Off(DI_Probe_Inlet);
                        HAL_Delay(300);
		 			 }
	                 module_executed();
		 	 }


else if(((CompareToBrace(Fluid_Pickup))==1))     //  	  char  Fluid_Pickup[]               ="!FLPK()";
{
	unsigned int Number_ofpickup=0;
	unsigned int Volume =0;
	send_ACK();
	int extracted = sscanf(command, "!FLPK(%d,%d)",&Number_ofpickup, &Volume);
	if (extracted != 2) {
	HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
	return;
	}
	//PICK THE VOLIME
	Valve_On(DI_Probe_Inlet);
	Rising_Edge(VL_EXLED_GATE);
	HAL_Delay(300);

	for (int i=1;i<=Number_ofpickup;i++)
	{
		Move_Syringe_Motor(1,Volume );
		 HAL_Delay(1000);
		// MOVE DOWN FURTHER AND CHECK IF THERE IS APROBE CREASH
		if(strcmp(Error, "00") == 0)
		 {

			if(i<Number_ofpickup)
			{
				 Move_Z_Probe_Motor(PROBE_DOWN_DIR , 50);

					// PICK THE VOUMEE
				if ((strcmp(Error, "P") == 0))
					{

						int reverseloop=i; ///No of Z movement is less than the pickup because during first pick up is done by using  MDFS command movemnt
						for(int j=1;j<=reverseloop;j++)
						{

							  Move_Z_Probe_Motor(PROBE_UP_DIR , 50);
							 Move_Syringe_Motor(0,Volume );
							 HAL_Delay(1000);
						}
						break;
					}
				else if((strcmp(Error, "00") == 0))
				{
					;
				}
				else
				{
					break;
				}
			}
		 }
	}
//	Home_Z_Probe_Motor( PROBE_HOME_MAX_COUNT);
//	Home_Syringe_Motor(SYRINGE_HOME_MAX_COUNT);
	if(strcmp(Error, "00") != 0)
	{
	//	Home_Z_Probe_Motor( PROBE_HOME_MAX_COUNT);
	//	Home_Syringe_Motor(SYRINGE_HOME_MAX_COUNT);
		Valve_On(DI_Probe_Inlet);
		Rising_Edge(VL_EXLED_GATE);
		HAL_Delay(300);
	}

	module_executed();
}


	   else if(((CompareToBrace(Prime_Pump))==1))//  	 char  Prime_Pump[]                 ="PPRI()";
	   {
			 	    	 unsigned int Nozzle_Prime_Height=0;
			 	    	 unsigned int Buffer_Prime_Volume =0;
			 			 send_ACK();
			 			   int extracted = sscanf(command, "!PPRI(%d,%d)",&Nozzle_Prime_Height, &Buffer_Prime_Volume);
			 				if (extracted != 2) {
			 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
			 				 return;
			 				}
			 			// move nozzle down
			 				Move_Z_Nozzle_Motor(NOZZLE_DOWN_DIR, Nozzle_Prime_Height);

			 			//waste pump on
			 			  if((strcmp("00",Error)==0))
			 			  {
			 				Pump_On(&Waste_RemovalPump,CLOCKWISE);

			 				Rising_Edge(P1_P4_GATE);
							HAL_Delay(300);
						   //buffer pump on
							Pump_On(&WashandUniversalBuffer_Pump,CLOCKWISE);

							Rising_Edge(P1_P4_GATE);
							delay_ms(Buffer_Prime_Volume);
							Pump_Off(&WashandUniversalBuffer_Pump);

							Rising_Edge(P1_P4_GATE);
							HAL_Delay(1000);
							Pump_On(&WashandUniversalBuffer_Pump,ANTICLOCKWISE);

							Rising_Edge(P1_P4_GATE);
							delay_ms(100);
							Pump_Off(&WashandUniversalBuffer_Pump);

							Rising_Edge(P1_P4_GATE);
							delay_ms(100);
			 			   //waste pump off
							Pump_Off(&Waste_RemovalPump);

							Rising_Edge(P1_P4_GATE);
							HAL_Delay(300);
						   // home Z
							Home_Z_Nozzle_Motor(NOZZLE_HOME_MAX_COUNT);

			 			  }
					       module_executed();
					  }

	 else if(((CompareToBrace(Z_Nozzle_Aspirate))==1))//  	 char  Z_Nozzle_Aspirate[]             ="!NAS()";
				 {
				 unsigned int Number_Of_Strips=0;
				 unsigned int Nozzle_Aspirate_Height=0;
				 unsigned int Waste_Aspirate_Count=0;
				 unsigned int Strip_Position=2;
				 unsigned int Number_Of_Aspiration=0;
				 send_ACK();
				   int extracted = sscanf(command, "!NAS(%d,%d,%d,%d)",&Number_Of_Strips, &Nozzle_Aspirate_Height,&Waste_Aspirate_Count,&Number_Of_Aspiration);
					if (extracted != 4) {
					 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
					 return;
					}
			  for( int i=1;i<=Number_Of_Aspiration;i++)
			  {
				  Send_Count(Strip_Position);

				//step 2 move nozzle down
				Move_Z_Nozzle_Motor(NOZZLE_DOWN_DIR, Nozzle_Aspirate_Height);
				if(strcmp("00",Error)==0)
				{
					//step 3 dispaense volume

					Waste_Pump_Function(Waste_Aspirate_Count);

					Home_Z_Nozzle_Motor(NOZZLE_HOME_MAX_COUNT);
				}
			  }

			  if(strcmp("00",Error)==0)
			  {
				while((Number_Of_Strips>1)&&(Strip_Position <=Number_Of_Strips))
		    	{

					//step4 move to next strip
				 Move_X_Motor_Next_Position(STRIP_DIRECTION,300,NOZZLE);
				  if(strcmp("00",Error)==0)
				  {
					  for( int i=1;i<=Number_Of_Aspiration;i++)
					  {

						  Move_Z_Nozzle_Motor(NOZZLE_DOWN_DIR, Nozzle_Aspirate_Height);
						// step 5 dispense volume
						  if(strcmp("00",Error)==0)
						  {

							 Waste_Pump_Function(Waste_Aspirate_Count);

							 Home_Z_Nozzle_Motor(NOZZLE_HOME_MAX_COUNT);

							  if(strcmp("00",Error)!=0) break;
						  }
						  else
						  {
							  break;
						  }

					  }

				  }
				  else
				  {
					  break;
				  }
				  Strip_Position++;
				  Send_Count(Strip_Position);

				}
			  }

				//step6 Nozzle home
	//			Home_Z_Nozzle_Motor(NOZZLE_HOME_MAX_COUNT);
			   module_executed();
			  }

     else if(((CompareToBrace(Z_Probe_Home))==1))//   char  Z_Probe_Home[]		       ="!ZPHOM()";
			 {
	    	 unsigned int Maximum_Pulses=0;
			 send_ACK();
			 //Error="X";
			   int extracted = sscanf(command, "!ZPHOM(%d)",&Maximum_Pulses);
				if (extracted != 1) {
				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
				 return;
				}
			   Home_Z_Probe_Motor( Maximum_Pulses);
			   module_executed();
			  }
     else if(((CompareToBrace(Z_Probe_Home_Distance))==1))//    char  Z_Probe_Home_Distance[]      ="!ZPECC()";
 			 {
 	    	 unsigned int Maximum_Pulses=0;
 			 send_ACK();
 			   int extracted = sscanf(command, "!ZPECC(%d)",&Maximum_Pulses);
 				if (extracted != 1) {
 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
 				 return;
 				}
 				Home_Z_Probe_Motor_Distance( Maximum_Pulses);
 			   module_executed();
 			  }
     else if(((CompareToBrace(Z_Nozzle_Home_Distance))==1))//   c char  Z_Nozzle_Home_Distance[]    ="!ZNECC()";
     			 {
     	    	 unsigned int Maximum_Pulses=0;
     			 send_ACK();
     			   int extracted = sscanf(command, "!ZNECC(%d)",&Maximum_Pulses);
     				if (extracted != 1) {
     				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
     				 return;
     				}
     				Home_Z_Nozzle_Motor_Distance( Maximum_Pulses);
     			   module_executed();
     			  }

	 else if(((CompareToBrace(Z_Probe_Move))==1))//  	 char  Z_Probe_Move[]              ="!ZPMOV()";
	 			 {
	 	    	 unsigned int Direction=0,Distance=0;

	 			 send_ACK();
	 			//Error="P";
	 			   int extracted = sscanf(command, "!ZPMOV(%d,%d)",&Direction, &Distance);
	 				if (extracted !=2) {
	 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
	 				 return;
	 				}
	 				Move_Z_Probe_Motor(Direction, Distance);
	 			   module_executed();
	 			  }
	 else if(((CompareToBrace(Syringe_Home))==1))//  		 char  Syringe_Home[]		       ="!SHOM()";
	 			 {
		            unsigned int Maximum_Pulses=0;
					 send_ACK();
					   int extracted = sscanf(command, "!SHOM(%d)",&Maximum_Pulses);
						if (extracted != 1) {
						 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
						 return;
						}
				   Home_Syringe_Motor( Maximum_Pulses);
				   module_executed();
	 			  }
	 else if(((CompareToBrace(Syringe_Move))==1))//  	     char  Syringe_Move[]              ="!SMOV()";
	 			 {
	 	    	 unsigned int Direction=0,Distance=0;

	 			 send_ACK();
	 			   int extracted = sscanf(command, "!SMOV(%d,%d)",&Direction, &Distance);
	 				if (extracted != 2) {
	 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
	 				 return;
	 				}
	 				Move_Syringe_Motor(Direction, Distance);
	 			   module_executed();
	 			  }
	 else if(((CompareToBrace(Air_Gap))==1))//  	     char  Air_Gap[]              ="!AIRG()";
	 			 {
	 	    	 unsigned int Direction=1,VolumeCount=0;

	 			 send_ACK();
	 			   int extracted = sscanf(command, "!AIRG(%d)", &VolumeCount);
	 				if (extracted != 1) {
	 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
	 				 return;
	 				}
	 				Valve_On(DI_Probe_Inlet);
	 				Rising_Edge(VL_EXLED_GATE);
	 				HAL_Delay(500);
	 				Move_Syringe_Motor(Direction, VolumeCount);
	 			   module_executed();
	 			  }
	 else if(((CompareToBrace(X_Home))==1))//  	   char  X_Home[]                     ="!XHOM()";
	 			 {
		           unsigned int Maximum_Pulses=0,Direction=0;
					 send_ACK();
					   int extracted = sscanf(command, "!XHOM(%d,%d)",&Direction, &Maximum_Pulses);
						if (extracted != 2) {
						 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
						 return;
						}
				   Home_X_Motor(Direction, Maximum_Pulses);
				   module_executed();
	 			  }
	 else if(((CompareToBrace(X_Move))==1))//  	     char  X_Move[]                     ="XMOV()";
	 			 {
	 	    	 unsigned int Direction=0,Distance=0,position=0;
	 			 send_ACK();
	 			 //Error="F";
	 			    int extracted = sscanf(command, "!XMOV(%d,%d,%d)",&Direction, &Distance, &position);
	 				if (extracted != 3) {
	 				 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
	 				 return;
	 				}
	 				Move_X_Motor(Direction, Distance,position);
	 			   module_executed();
	 			  }
	 else if(((CompareToBrace(Check_Frequency))==1))   //  	   char  Check_Frequency[]            ="!CFREQ()"
	 {
		  float freq_in_MHZ;
		  char freq_str[32];
		  send_ACK();
		  uint32_t freq = read_frequency_tim3();
		  freq_in_MHZ =freq/1000000.0f;
		  sprintf(freq_str, "%.2f \r\n", freq_in_MHZ);
		  putstr(freq_str);
		  HAL_Delay(500);
		 module_executed();
	 }

	 else if (CompareToBrace(Move_Down_Fluid_sense) == 1)  // char  Move_Down_Fluid_sense[]	    ="!MDFS()";
	 {
	     unsigned int Unconditional_Movement = 0, Maximum_Distance = 0;

//	     char msg[128];

	     send_ACK();

	     int extracted = sscanf(command, "!MDFS(%u,%u)", &Unconditional_Movement, &Maximum_Distance);
	     if (extracted != 2)
	     {
	         HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, HAL_MAX_DELAY);
	         return;
	     }

	     // Step 1: Take baseline frequency at no movement
//	     uint32_t avg_frequency = Read_Average_Frequency();-------------------------not used
/*
	     snprintf(msg, sizeof(msg), "avg_frequency: %lu Hz\r\n", avg_frequency);
	     HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
*/

	     // Step 2: Move unconditionally
	     Move_Z_Probe_Motor(PROBE_DOWN_DIR, Unconditional_Movement);

	     // Step 3: Move and monitor frequency if no prior error
	     if (strcmp(Error, "00") == 0)
	     {
	         Move_And_Monitor_Frequency(Maximum_Distance);
	     }

	     // Step 4: Extra movement after detection (e.g. 50 pulses)
	    if (strcmp(Error, "00") == 0)
	    {
	     const uint32_t Extra_Movement_Pulses = 20;
	     Move_Z_Probe_Motor(PROBE_DOWN_DIR, Extra_Movement_Pulses);
	      }
	     module_executed();

	 }

	  else if(((CompareToBrace(Read_Sensor_Voltage))==1))// char  Read_Sensor_Voltage[]          ="!RSEN()";
				 {
				 unsigned int Sensor_No  			= 0;
				 char voltage_str[32];                // Buffer to store the voltage string
				 float voltage     =0.0;
				 send_ACK();
				 int extracted = sscanf(command, "!RSEN(%d)",&Sensor_No);
				 Sensor_No=7;
				 if (extracted != 1) {
					 HAL_UART_Transmit(&huart3, (uint8_t *)"Invalid command format\n", 23, I2C_Delay_Ms);
					 return;
					}
				   if (I2C_Device_Check(ADS7828_ADDR))
				  {

					 {
					  voltage = Read_Sensor_Volage(Sensor_No);
					  // Format the voltage into the string buffer
					   if(voltage<=1.0 || voltage>=4.0)
						 {
							 voltage=9.9;
							 sprintf(voltage_str, "%.1f\r\n", voltage);
							 putstr(voltage_str);
					  //  	   I2C2_Recover();

							  //putchr('R');
							  module_executed();
							 return;
						 }
					  sprintf(voltage_str, "%.1f\r\n", voltage);
					  putstr(voltage_str);
					 }
			   	}
				   else Error="R";
				  module_executed();
		 		 }
		  else if(((CompareToBrace(Write_EPOT_Resistance))==1))//  char  Write_EPOT_Resistance[]        ="!WEPOT()";
		  		{
			  unsigned int sensor_no = 0;
			  float voltage = 0.0f;
			  char voltage_str[32];
			  uint8_t wiper_val = 0;
			  send_ACK();
		     sscanf(command, "!WEPOT(%d,%f)", &sensor_no, &voltage);
//		     char msg[64];  // Buffer for UART message
		       // Print desired voltage to UART for debugging
//		       snprintf(msg, sizeof(msg), "Desired Voltage for sensor %d = %.3f V\r\n", sensor_no, voltage);
//		       HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
		     sensor_no=7;


		     wiper_val= voltageToStep(voltage);
/*


		   //for plexmat 4 code
		  switch (sensor_no) {
			case 1:
				      MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 1); // Enable for ePot 2_1
					  // Write to RAM (volatile) wiper 0
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2B, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  // Write to EEPROM (non-volatile) wiper 0
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2B, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 0); // Enable for ePot 2_1
					  break;
			case 2:
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 1); // Enable for ePot 2_2
						// Write to RAM (volatile) wiper 1
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2B, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }

					  // Write to EEPROM (non-volatile) wiper 1
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2B, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 0); // Enable for ePot 2_2
						break ;
			}*/
/////////////////////////////For testing  epot////////////////////////////////////////////////////////////////

	//		I2C_ScanBus();
			switch (sensor_no) {
			case 1:
					   MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 1); // Enable for ePot 1_1
					  // Write to RAM (volatile) wiper 0
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x29, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  // Write to EEPROM (non-volatile) wiper 0
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x29, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 0); // Enable for ePot 1_1
					   break ;

			case 2:
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 1); // Enable for ePot 1_2
					  // Write to RAM (volatile) wiper 0
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x29, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  // Write to EEPROM (non-volatile) wiper 0
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x29, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_5, 0); // Enable for ePot 1_2
					  break ;

			case 3:
				      MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 1); // Enable for ePot 2_1
					  // Write to RAM (volatile) wiper 0
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2B, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  // Write to EEPROM (non-volatile) wiper 0
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2B, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 0); // Enable for ePot 2_1
					  break;

			case 4:
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 1); // Enable for ePot 2_2
						// Write to RAM (volatile) wiper 1
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2B, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }

					  // Write to EEPROM (non-volatile) wiper 1
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2B, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOB, GPIO_PIN_4, 0); // Enable for ePot 2_2
						break ;

			case 5:
				      MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 1); // Enable for ePot 3_1
					  // Write to RAM (volatile) wiper 0
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2D, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  // Write to EEPROM (non-volatile) wiper 0
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2D, 0, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 0); // Enable for ePot 3_1
					  break ;

			case 6:
					  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 1); // Enable for ePot 3_2
					  if (MCP4661_WriteWiperRAM(&hi2c2, 0x2D, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  // Write to EEPROM (non-volatile) wiper 0
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2D, 1, wiper_val) != HAL_OK)
					  {
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_6, 0); // Enable for ePot 3_2
					  break ;

			case 7:
					 MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_5, 1); // Enable for ePot 4_1
					 if (MCP4661_WriteWiperRAM(&hi2c2, 0x2F, 0, wiper_val) != HAL_OK)
					  {
	//					 putchr('1');
						  Error = "W";
					  }
					  // Write to EEPROM (non-volatile) wiper 0
					  if (MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2F, 0, wiper_val) != HAL_OK )
					  {
//					      putchr('2');
						  Error = "W";
					  }
					  MCP4661_SetHardwareWriteProtect(GPIOD, GPIO_PIN_5, 0); // Enable for ePot 4_1
	//				  putstr(Error);
					  break ;

			default:
					 break ;
			}

/////////////////////////////For testing  epot////////////////////////////////////////////////////////////////
			 if(strcmp(Error, "00") == 0)
			{
		          voltage = Read_Sensor_Volage(sensor_no);
				  // Format the voltage into the string buffer
		//          putstr(Error);
		          if(voltage<=1.0 || voltage>=4.0)
		     		     {
		     		    	 voltage=9.9;
		     		    	 sprintf(voltage_str, "%.1f\r\n", voltage);
		     		    	 putstr(voltage_str);
		     		  //  	   I2C2_Recover();

		     				  //putchr('R');
		     				  module_executed();
		     		    	 return;
		     		     }

		          sprintf(voltage_str, "%.1f\n", voltage);
				  putstr(voltage_str);
			 }
			      I2C2_Recover();
	//		      putstr(Error);
			  //putchr('R');
			  module_executed();
/*************For Debugging EPOT use the below functions***********/
//			  uint16_t eeprom_value;
//			  uint16_t status;
//Test the corrected functions
//Test_MCP4661_Corrected(&hi2c2, 0x2D);
//HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_RESET);// for epot 3
//HAL_Delay(1000);
//MCP4661_ReadStatusRegister(&hi2c2, 0x2D, &status);
//HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);// for epot 3
//HAL_Delay(1000);
//MCP4661_ReadStatusRegister(&hi2c2, 0x2D, &status);
//MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2D, 0, wiper_val);
//MCP4661_WriteWiper_EEPROM(&hi2c2, 0x2D, 1, wiper_val);
//
//MCP4661_ReadWiper_EEPROM(&hi2c2, 0x2D, 0, &eeprom_value); // Reads EEPROM Wiper0
//MCP4661_ReadWiper_EEPROM(&hi2c2, 0x2D, 1, &eeprom_value); // Reads EEPROM Wiper1
//HAL_NVIC_SystemReset();  // This causes a software-triggered full MCU reset


		  }
	   else
	       {
		     send_ACK();
	         putchr('W');
           }

	// Restart UART reception for continuous data flow
	   HAL_UART_Receive_IT(&huart3, &rxByte, 1);
}
