/*
 * Probe_Motor_Z.c
 *
 *  Created on: May 21, 2025
 *      Author: RAGHUL
 */


#include "command_processor.h"
#include "Probe_Motor_Z.h"
 extern char *Error;
unsigned int  Z_Probe_motor_speed=1000;
unsigned int  Z_Probe_pulses=0;
void Start_Z_Probe_Motor()
{
	 Start_PWM(PROBE_TIMER, PROBE_TIMER_CHANNEL, Z_Probe_motor_speed, 50, Z_Probe_pulses);  // 1kHz, 50% duty, 500 pulses

}
void Stop_Z_Probe_Motor()
{
	//Stop_PWM(PROBE_TIMER, PROBE_TIMER_CHANNEL);

	 HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);
	    HAL_TIM_Base_Stop_IT(&htim11); // Stop interrupt
}
void Home_Z_Probe_Motor(uint32_t Maximum_Pulses)
{
	 pulse_count=0;
	  int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
	  int direction_reset=0;
	  Probe_Motor_Dir_AClk;
	  Probe_Motor_En;
	  if(!Sensor_Read(Z_Home_Sensor))	 // If already it is at Z home do not move
	   {
		  Start_Z_Probe_Motor()  ;// 1kHz, 50% duty, 500 pulses
		   while(pulse_count<=Maximum_Pulses )
		   {
				if(Sensor_Read(Z_Home_Sensor)) // After 3 pulses if it is reached Z home, do not give further pusles
				{
					sensor_reached =1;
					break;
				}
				else if(Sensor_Read(Z_EOT_Sensor))
				{
					pulse_count=0;
					direction_reset=1;
					Probe_Motor_Dir_Clk;
				}
				if(pulse_count==Maximum_Pulses )
				{
					Error="X";
				}
		   }
	  }
	  if((sensor_reached==1) &&(direction_reset==1))
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
			  if(Sensor_Read(Z_Home_Sensor))  break;
		  }
		  if((pulse_count==100) && (!Sensor_Read(Z_Home_Sensor)))
			  {
				  Error="X";

			  }
	  }
	  direction_reset=0;
	  Stop_Z_Probe_Motor();
}

void Home_Z_Probe_Motor_Distance(uint32_t Maximum_Pulses)
{
	 pulse_count=0;
	  int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
	  int direction_reset=0;
	  Probe_Motor_Dir_AClk;
	  Probe_Motor_En;
	  if(!Sensor_Read(Z_Home_Sensor))	 // If already it is at Z home do not move
	   {
		  Start_Z_Probe_Motor()  ;// 1kHz, 50% duty, 500 pulses
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
					pulse_count=0;
					direction_reset=1;
					Probe_Motor_Dir_Clk;
				}
				if(pulse_count==Maximum_Pulses )
				{
					Error="X";
				}
		   }
	  }
	  if((sensor_reached==1) &&(direction_reset==1))
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
			  if(Sensor_Read(Z_Home_Sensor))  break;
		  }
		  if((pulse_count==100) && (!Sensor_Read(Z_Home_Sensor)))
			  {
				  Error="X";

			  }
	  }
	  direction_reset=0;
	  Stop_Z_Probe_Motor();
}

void Z_Probe_MHotor(uint32_t Maximum_Pulses)
{
	 pulse_count=0;
	  int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
	  int direction_reset=0;
	  Probe_Motor_Dir_AClk;
	  Probe_Motor_En;
	  if(!Sensor_Read(Z_Home_Sensor))	 // If already it is at Z home do not move
	   {
		  Start_Z_Probe_Motor()  ;// 1kHz, 50% duty, 500 pulses
		   while(pulse_count<=Maximum_Pulses )
		   {
				if(Sensor_Read(Z_Home_Sensor)) // After 3 pulses if it is reached Z home, do not give further pusles
				{
					sensor_reached =1;
					break;
				}
				else if(Sensor_Read(Z_EOT_Sensor))
				{
					pulse_count=0;
					direction_reset=1;
					Probe_Motor_Dir_Clk;
				}
				if(pulse_count==Maximum_Pulses )
				{
					Error="X";
				}
		   }
	  }
	  if((sensor_reached==1) &&(direction_reset==1))
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
			  if(Sensor_Read(Z_Home_Sensor))  break;
		  }
		  if((pulse_count==100) && (!Sensor_Read(Z_Home_Sensor)))
			  {
				  Error="X";

			  }
	  }
	  direction_reset=0;
	  Stop_Z_Probe_Motor();
}


void Move_Z_Probe_Motor(int Direction, int Distance )
{
		  pulse_count=0;
	      int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
	      int Z_Home_Check=0;
	      int Intially_Home=0;
	      if(Direction)Probe_Motor_Dir_Clk;
	      else Probe_Motor_Dir_AClk;
	      Probe_Motor_En;
	      if(Sensor_Read(Z_Home_Sensor))
	      {
	    	  Intially_Home=1;
	      }
		   if(Direction)  //Direction 1 - Down
		   {
			   Start_Z_Probe_Motor() ; // 1kHz, 50% duty, 500 pulses
			   while(pulse_count<Distance )
			   {
				   if(Sensor_Read(Probe_Crash_Sensor))
					{
					   Error ="P";
					   break;
					}
					if(((pulse_count==50)&& (Sensor_Read(Z_Home_Sensor))&&(Intially_Home)))
						{
							Error="Y";
							break;
						}
					if(((pulse_count>50)&& (Sensor_Read(Z_Home_Sensor))))
						{
							Error="Z";
							break;
						}

			   }
			   Stop_Z_Probe_Motor();
		   }
		   else if(!Direction)
		   {

				   Start_Z_Probe_Motor()  ;// 1kHz, 50% duty, 500 pulses
				   while(pulse_count<=Distance )
				   {

					   if(Sensor_Read(Z_EOT_Sensor))
						{

						   break;
						}
				   }
				   Stop_Z_Probe_Motor();

		     }

		   	sensor_reached=0;
		   	Stop_Z_Probe_Motor();

}

void Move_Z_Probe_Motor_Fluid_Sense(int Direction, int Distance )
{
  pulse_count=0;
  int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
  int Encoder=0, Z_Home_Check=0;
  if(Direction)Probe_Motor_Dir_Clk;
  else Probe_Motor_Dir_AClk;
  Probe_Motor_En;
   if(Direction)  //Direction 1 - Down
   {
	   if(Sensor_Read(Z_Home_Sensor))Z_Home_Check=1;
	   Start_Z_Probe_Motor() ; // 1kHz, 50% duty, 500 pulses
	   while(pulse_count<Distance )
	   {
		   if(Sensor_Read(Probe_Crash_Sensor))//temp change to test the code
			{
			   Error ="P";
			   break;
			}
			if((pulse_count==100)&& (Sensor_Read(Z_Home_Sensor)) && (Z_Home_Check==1))
				{
					Error="Y";
				}
			if((pulse_count>=100)&& (Sensor_Read(Z_Home_Sensor)) && (Z_Home_Check==1))
				{
					Error="Z";
				}

	   }
	   Stop_Z_Probe_Motor();
	   Send_Count(Distance);
	   Send_Count(pulse_count);
   }
   else if(!Direction)
   {

		   Start_Z_Probe_Motor()  ;// 1kHz, 50% duty, 500 pulses
		   while(pulse_count<=Distance )
		   {

			   if(Sensor_Read(Z_EOT_Sensor))
				{
				   break;
				}
		   }
		   Stop_Z_Nozzle_Motor();

	 }
	sensor_reached=0;
	Stop_Z_Probe_Motor();

}
