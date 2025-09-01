/*
 * Nozzle_Motor_Z.c
 *
 *  Created on: May 20, 2025
 *      Author: RAGHUL
 */


#include "command_processor.h"
#include "Nozzle_Motor_Z.h"
 extern char *Error;
unsigned int  Z_Nozzle_motor_speed=1000;
unsigned int  Z_Nozzle_pulses=0;

void Start_Z_Nozzle_Motor()
{

	 Start_PWM(NOZZLE_TIMER, NOZZLE_TIMER_CHANNEL, Z_Nozzle_motor_speed, 50, Z_Nozzle_pulses);  // 1kHz, 50% duty, 500 pulses

}
void Stop_Z_Nozzle_Motor()
{
//	Stop_PWM(NOZZLE_TIMER, NOZZLE_TIMER_CHANNEL);

	 HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);
	    HAL_TIM_Base_Stop_IT(&htim11); // Stop interrupt

}
void Home_Z_Nozzle_Motor(uint32_t Maximum_Pulses)
{
	      pulse_count=0;
		  int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
		  Probe_Motor_Dir_Clk;
		  Probe_Motor_En;
//		 if(Sensor_Read(Z_Home_Sensor))
	//	 {
		  if(!Sensor_Read(Z_Home_Sensor))	 // If already it is at Z home do not move
		   {
			  Start_Z_Nozzle_Motor()  ;// 1kHz, 50% duty, 500 pulses
			   while(pulse_count<=Maximum_Pulses )
			   {
					if(Sensor_Read(Z_Home_Sensor)) // After 3 pulses if it is reached Z home, do not give further pusles
					{
						sensor_reached =1;
						break;
					}
					else if(Sensor_Read(Z_EOT_Sensor))
					{
						break;
					}
					if((pulse_count==Maximum_Pulses) && (!Sensor_Read(Z_Home_Sensor)))
		              {
		            	  Error="A";
		              }
			   }
		  }
		  if((sensor_reached==1))
		  {
			  pulse_count=0;
			  while(pulse_count<10);
			  while(pulse_count<100)
				{
						  if(!Sensor_Read(Z_Home_Sensor))
						  {
						   break;
						  }
				}
			  pulse_count=0;
			  Probe_Motor_Dir_AClk;
			  while(pulse_count<100)
			  {
				  if(Sensor_Read(Z_Home_Sensor))  break;// After 3 pulses if it is reached Z home, do not give further pusles
			  }
			  if((pulse_count==100) && (!Sensor_Read(Z_Home_Sensor)))
			  {
				  Error="A";

			  }
		  }
		  Stop_Z_Nozzle_Motor();
//	   }
}

void Home_Z_Nozzle_Motor_Distance(uint32_t Maximum_Pulses)
{
	      pulse_count=0;
		  int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
		  Probe_Motor_Dir_Clk;
		  Probe_Motor_En;
//		 if(Sensor_Read(Z_Home_Sensor))
	//	 {
		  if(!Sensor_Read(Z_Home_Sensor))	 // If already it is at Z home do not move
		   {
			  Start_Z_Nozzle_Motor()  ;// 1kHz, 50% duty, 500 pulses
			   while(pulse_count<=Maximum_Pulses )
			   {
					if(Sensor_Read(Z_Home_Sensor)) // After 3 pulses if it is reached Z home, do not give further pusles
					{
						sensor_reached =1;
						Send_Count(pulse_count);
						break;
					}
					else if(Sensor_Read(Z_EOT_Sensor))
					{
						break;
					}
					if((pulse_count==Maximum_Pulses) && (!Sensor_Read(Z_Home_Sensor)))
		              {
		            	  Error="A";
		              }
			   }
		  }
		  if((sensor_reached==1))
		  {
			  pulse_count=0;
			  while(pulse_count<10);
			  while(pulse_count<100)
				{
						  if(!Sensor_Read(Z_Home_Sensor))
						  {
						   break;
						  }
				}
			  pulse_count=0;
			  Probe_Motor_Dir_AClk;
			  while(pulse_count<100)
			  {
				  if(Sensor_Read(Z_Home_Sensor))  break;// After 3 pulses if it is reached Z home, do not give further pusles
			  }
			  if((pulse_count==100) && (!Sensor_Read(Z_Home_Sensor)))
			  {
				  Error="A";

			  }
		  }
		  Stop_Z_Nozzle_Motor();
//	   }
}
void Move_Z_Nozzle_Motor(int Direction, int Distance )
{
		   pulse_count=0;
	      int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
	//      int Encoder=0;
	      if(Direction)Nozzle_Motor_Dir_Clk;
	    	else Nozzle_Motor_Dir_AClk;
	    	Nozzle_Motor_En;
		   if(!Direction)
		   {
			   Start_Z_Nozzle_Motor() ; // 1kHz, 50% duty, 500 pulses
			   while(pulse_count<Distance )
			   {
				   if(Sensor_Read(Z_EOT_Sensor))
					{
					   break;
					}
				   if((pulse_count==70) && (Sensor_Read(Z_Home_Sensor)))
						{
						  Error="B";
						   break;
						}
				   if((pulse_count>100) && (Sensor_Read(Z_Home_Sensor)))
						{
						  Error="C";
						   break;
						}

			   }
			   Stop_Z_Nozzle_Motor();
		   }
		   else if(Direction)
		   {
			   if(!Sensor_Read(Z_Home_Sensor))	 // If already it is at Z home do not move
			   {
				   Start_Z_Nozzle_Motor()  ;// 1kHz, 50% duty, 500 pulses
				   while(pulse_count<=Distance )
				   {
						if(Sensor_Read(Z_EOT_Sensor)) // After 3 pulses if it is reached Z home, do not give further pusles
						{
						    break;
						}
				   }

				   Stop_Z_Nozzle_Motor();
			  }
		   }


		   	sensor_reached=0;
		   	Stop_Z_Nozzle_Motor();

}

