/*
 * Syringe_Motor.c
 *
 *  Created on: May 21, 2025
 *      Author: RAGHUL
 */


#include "command_processor.h"
#include "Syringe_Motor.h"
extern char *Error;
unsigned int  syringe_motor_speed=1000;
unsigned int  syringe_pulses=0;

void Start_Syringe_Motor()
{

	 Start_PWM(SYRINGE_TIMER, SYRINGE_TIMER_CHANNEL, syringe_motor_speed, 50, syringe_pulses);  // 1kHz, 50% duty, 500 pulses

}
void Stop_Syringe_Motor()
{
//	Stop_PWM(SYRINGE_TIMER, SYRINGE_TIMER_CHANNEL);
	HAL_TIM_PWM_Stop(&htim9 , TIM_CHANNEL_1);
		HAL_TIM_Base_Stop_IT(&htim9); // Stop interrupt
}

void Home_Syringe_Motor(uint32_t Maximum_Pulses)
{
	 pulse_count=0;
//	 int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
//	 int Encoder=0;
	 Syringe_Motor_Dir_Clk;
	 Syringe_Motor_En;
	 if(!Sensor_Read(Syringe_Home_Sensor))	 // If already it is at Z home do not move
	   {
		   Start_Syringe_Motor()  ;// 1kHz, 50% duty, 500 pulses
		   while(pulse_count<=Maximum_Pulses )
		   {
				if(Sensor_Read(Syringe_Home_Sensor)) // After 3 pulses if it is reached Z home, do not give further pusles
				{
	//				sensor_reached =1;
//					Encoder=9000;
					break;
				}
				if(pulse_count==Maximum_Pulses)  Error= "N";
		   }
	    }
	// sensor_reached=0;
	 Syringe_Motor_Dis;
	 Stop_Syringe_Motor();
}

void Move_Syringe_Motor(int Direction, int Distance )
{
		   pulse_count=0;
	      int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
	      int Encoder=0;
	      int Initially_Home=0;
	      if(Direction)Syringe_Motor_Dir_AClk;
	    	else Syringe_Motor_Dir_Clk;
	        Syringe_Motor_En;
	//        HAL_Delay(20000);
	//        Syringe_Motor_Dis;
           if(Sensor_Read(Syringe_Home_Sensor))
           {
        	   Initially_Home=1;
           }
		   if(Direction)
		   {
			   Start_Syringe_Motor() ; // 1kHz, 50% duty, 500 pulses
			   while(pulse_count<Distance )
			   {
				   if((pulse_count==200) &&(Sensor_Read(Syringe_Home_Sensor))&&(Initially_Home))
					{
			           Error= "S";
					   break;
					}
				   if((pulse_count>200) &&(Sensor_Read(Syringe_Home_Sensor)))
					{
					   Error= "T";
					   break;
					}
			   }
			   Stop_Syringe_Motor();
		   }
		   else if(!Direction)
		   {
			  uint8_t a= Sensor_Read(Syringe_Home_Sensor);
	//		  Send_Count(a);
			  if(!a)	 // If already it is at Z home do not move
			   {
				  Start_Syringe_Motor()  ;// 1kHz, 50% duty, 500 pulses
				   while(pulse_count<=Distance )
				   {
						if(Sensor_Read(Syringe_Home_Sensor)) // After 3 pulses if it is reached Z home, do not give further pusles
						{
							Error= "T";
						    break;
						}
				   }
				   Stop_Syringe_Motor();
		       }
		   }
		   	sensor_reached=0;
		    Syringe_Motor_Dis;
		   	Stop_Syringe_Motor();

}
