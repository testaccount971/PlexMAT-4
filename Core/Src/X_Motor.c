/*
 * X_Motor.c
 *
 *  Created on: May 22, 2025
 *      Author: RAGHUL
 */


#include "command_processor.h"
#include "X_Motor.h"
 extern char *Error;
unsigned int  X_motor_speed=1500;
unsigned int  X_pulses=0;

void Start_X_Motor()
{
	 Start_PWM(X_MOTOR_TIMER, X_MOTOR_TIMER_CHANNEL, X_motor_speed, 50, X_pulses);  // 1kHz, 50% duty, 500 pulses

}
void Stop_X_Motor()
{
//	Stop_PWM(X_MOTOR_TIMER, X_MOTOR_TIMER_CHANNEL);
	HAL_TIM_PWM_Stop(&htim10 , TIM_CHANNEL_1);
	HAL_TIM_Base_Stop_IT(&htim10); // Stop interrupt
}
void Home_X_Motor(int Direction,uint32_t Maximum_Pulses)
{
	      pulse_count=0;
	      int direction_reset=0,X_Home_Check=0;
		  int sensor_reached=0; // if sesner is sesned con firmy then this bit is set to 1. To take decition at the end of the function based on the bit starte not dpenet on realtime sensor state.
		if(Direction)
		{
		  X_Motor_Dir_AClk;
		  X_Motor_En;
		  if((!Sensor_Read(Reagent_Probe_Position_Sensor))&& (!Sensor_Read(Nozzle_Probe_Position_Sensor)))
		  {
	//		  Start_X_Motor()  ;// 1kHz, 50% duty, 500 pulses
			  sensor_reached=1;
			  X_Home_Check=1;
		  }

		  if(((!Sensor_Read(Reagent_Probe_Position_Sensor)) && (Sensor_Read(Nozzle_Probe_Position_Sensor)))||
			 ((Sensor_Read(Reagent_Probe_Position_Sensor)) && (!Sensor_Read(Nozzle_Probe_Position_Sensor)))||
			 ((Sensor_Read(Reagent_Probe_Position_Sensor)) && (Sensor_Read(Nozzle_Probe_Position_Sensor))) )	 // If already it is at Z home do not move
		   {

			  Start_X_Motor()  ;// 1kHz, 50% duty, 500 pulses
			   while(pulse_count<=Maximum_Pulses )
			   {
					if((!Sensor_Read(Reagent_Probe_Position_Sensor))& (!Sensor_Read(Nozzle_Probe_Position_Sensor))) // hOME
					{
						sensor_reached =1;
						break;
					}
					else if(Sensor_Read(X_EOT_Sensor))
					{
						pulse_count=0;
						direction_reset=1;
						X_Motor_Dir_Clk;
					}
					if(pulse_count==Maximum_Pulses )
					{
						Error="D";
						break;
					}
               }
		  }
		  if((sensor_reached==1)&&((direction_reset==0)||(X_Home_Check==1)))
		  {
			  X_Motor_Dir_AClk;
			  Start_PWM(X_MOTOR_TIMER, X_MOTOR_TIMER_CHANNEL, 500, 50, X_pulses);
			  pulse_count=0;
			  while(pulse_count<50);
			  pulse_count=0;
			  X_Motor_Dir_Clk;
			  while(pulse_count<500)
			  {
				  if((!Sensor_Read(Reagent_Probe_Position_Sensor))&& (!Sensor_Read(Nozzle_Probe_Position_Sensor)))  break;// After 3 pulses if it is reached Z home, do not give further pusles
			  }

		  }
		  Stop_X_Motor();
		}
		if(!Direction)
		{
		    X_Motor_Dir_Clk;
			X_Motor_En;
			 if((!Sensor_Read(Reagent_Probe_Position_Sensor))&& (!Sensor_Read(Nozzle_Probe_Position_Sensor)))
			  {
	//			 Start_X_Motor()  ;// 1kHz, 50% duty, 500 pulses
				  sensor_reached=1;
				  X_Home_Check=1;
			  }

		      if(((!Sensor_Read(Reagent_Probe_Position_Sensor)) && (Sensor_Read(Nozzle_Probe_Position_Sensor)))||
					 ((Sensor_Read(Reagent_Probe_Position_Sensor)) && (!Sensor_Read(Nozzle_Probe_Position_Sensor)))||
					 ((Sensor_Read(Reagent_Probe_Position_Sensor)) && (Sensor_Read(Nozzle_Probe_Position_Sensor))) )	 // If already it is at Z home do not move
				   {
					  Start_X_Motor()  ;// 1kHz, 50% duty, 500 pulses
					   while(pulse_count<=Maximum_Pulses )
					   {
							if((!Sensor_Read(Reagent_Probe_Position_Sensor))&& (!Sensor_Read(Nozzle_Probe_Position_Sensor))) // hOME
							{
								sensor_reached =1;
								break;
							}
							if(pulse_count==Maximum_Pulses )
							{
								Error="D";
								break;
							}
					   }

				  }
		      if((sensor_reached==1)&&(X_Home_Check==1))
			  {
		    	  X_Motor_Dir_AClk;
		    	 			  Start_PWM(X_MOTOR_TIMER, X_MOTOR_TIMER_CHANNEL, 500, 50, X_pulses);
		    	 			  pulse_count=0;
		    	 			  while(pulse_count<50);
		    	 			  pulse_count=0;
		    	 			  X_Motor_Dir_Clk;
		    	 			  while(pulse_count<500)
		    	 			  {
		    	 				  if((!Sensor_Read(Reagent_Probe_Position_Sensor))&& (!Sensor_Read(Nozzle_Probe_Position_Sensor)))  break;// After 3 pulses if it is reached Z home, do not give further pusles
		    	 			  }
			  }
		      Stop_X_Motor();
		}


}


void Move_X_Motor(int Direction,int distance_pulse,unsigned int Num_Of_Strips)
{
	unsigned int Sensor_status,probe_nozzle_strip_gap=300,reagent_bottle_gap=600;
	unsigned char X_DIR=0;
	int sensor_reached=0;
	int half_distance=distance_pulse/2;
	X_DIR = Direction;
	if(X_DIR)
	{
		pulse_count=0;
		X_Motor_En;
		X_Motor_Dir_AClk;

		Start_X_Motor();
		while(pulse_count<distance_pulse)
		{
			Sensor_status =( (!(Sensor_Read(Nozzle_Probe_Position_Sensor))) && (!(Sensor_Read(Reagent_Probe_Position_Sensor)))   );
//			putchr('#');
//			Send_Count(Sensor_status);

			if((pulse_count==50) && (Sensor_status==1))
				{
	              Error="E";
//	              putchr('0');
//	              Send_Count(Sensor_status);
//	              putchr('2');
				 break;
				}
			if((pulse_count>50) && (Sensor_status==1))
				{
				  Error="F";
//				  putchr('3');
//				  Send_Count(Sensor_status);
//				  putchr('4');
				 break;
				}
			if(distance_pulse >500)
			{
				if((pulse_count > 50 ) &&(!(Sensor_Read(Reagent_Probe_Position_Sensor))) &&   ((Sensor_Read(Nozzle_Probe_Position_Sensor)))      )
				{
	//				 putchr('5');
					sensor_reached=1;
					break;
				}
			}
			else
			{
				if((pulse_count > 50 ) &&(!(Sensor_Read(Nozzle_Probe_Position_Sensor))))  //tune 500 to the nearest first osition count
				{
		//			 putchr('6');
					sensor_reached=1;
					break;
				}
			}

		}

		for(int strip_position=2;strip_position<=Num_Of_Strips;strip_position++)
		{
			pulse_count=0;
			while(pulse_count < probe_nozzle_strip_gap)
			{
				if(distance_pulse >500)
							{
								if((pulse_count > 50 ) &&(!(Sensor_Read(Reagent_Probe_Position_Sensor))))
								{
									sensor_reached=1;
									break;
								}
							}
							else
							{
								if((pulse_count > 50 ) &&(!(Sensor_Read(Nozzle_Probe_Position_Sensor))))  //tune 500 to the nearest first osition count
								{
									sensor_reached=1;
									break;
								}
							}

			}
		}
		 Stop_X_Motor();
	}
	if(!X_DIR)
	{
		pulse_count=0;
		X_Motor_En;
		X_Motor_Dir_Clk;
		Start_X_Motor();
		while(pulse_count<distance_pulse)
		{
			Sensor_status =( (!(Sensor_Read(Reagent_Probe_Position_Sensor))) && (!(Sensor_Read(Nozzle_Probe_Position_Sensor)))   );
	//		putchr('@');
	//		Send_Count(Sensor_status);

			if((pulse_count==50) && (Sensor_status==1))
				{
				  Error="E";
				 break;
				}

			if((pulse_count>50) &&  (Sensor_status==1))
				{
				  Error="F";
				 break;
				}

				if((pulse_count > 300 ) &&(!(Sensor_Read(Reagent_Probe_Position_Sensor))))
				{
					sensor_reached=1;
					break;
				}
		}
		for(int strip_position=2;strip_position<=Num_Of_Strips;strip_position++)
		{
			pulse_count=0;
			while(pulse_count < reagent_bottle_gap)
			{

				if((pulse_count > 50 )&&( !Sensor_Read(Reagent_Probe_Position_Sensor)))
				{
					sensor_reached=1;
					break;
				}
			}
		}
	   Stop_X_Motor();
	}
}


void Move_X_Motor_Next_Position(int Direction,int distance_pulse,unsigned int StripOrReagent)
{
//	unsigned int probe_nozzle_strip_gap=300,reagent_bottle_gap=700;
	unsigned char X_DIR=0,strip_position=0;
	int sensor_reached=0;

	X_DIR = Direction;
	if(X_DIR)
	{
		pulse_count=0;
		X_Motor_En;
		X_Motor_Dir_AClk;

		Start_X_Motor();
		while(pulse_count<distance_pulse)
		{

			if(StripOrReagent==NOZZLE)
			{

				 if((pulse_count==50) && ( (!Sensor_Read(Nozzle_Probe_Position_Sensor))))
					{

						Error="G";	// 	Does not leave the last position
						break;
					}
				if((pulse_count >51 ) &&(!(Sensor_Read(Nozzle_Probe_Position_Sensor))))
				{
					sensor_reached=1;
					break;
				}
			}
			else if(StripOrReagent == PROBE)
			{
				 if((pulse_count==50) && ( (!Sensor_Read(Reagent_Probe_Position_Sensor))))
				{

					Error="G";	// 	Does not leave the last position
					break;
				}
				if((pulse_count >50 ) &&(!(Sensor_Read(Reagent_Probe_Position_Sensor))))  //tune 500 to the nearest first osition count
				{
					sensor_reached=1;
					break;
				}
			}
		}
//		 if((pulse_count==100) || (!sensor_reached))
//					 {
//						if(pulse_count==100)Error="E";	// Does not leave X Home
//						else if(!sensor_reached)
//							Error="F";
//			//			Send_Count(pulse_count);
//		             }
		 Stop_X_Motor();

		if((sensor_reached==0)&& (Error!="G"))
		{
		 Error="H";	// Does not reach next position
		}
		HAL_Delay(500);
	}
	if(!X_DIR)
	{
		pulse_count=0;
		X_Motor_En;
		X_Motor_Dir_Clk;
		Start_X_Motor();
		while(pulse_count<distance_pulse)
		{


			   if((pulse_count==50) && ( (!Sensor_Read(Reagent_Probe_Position_Sensor))))
				{

					Error="G";	// 	Does not leave the last position
					break;
				}

				if((pulse_count > 400 ) &&(!(Sensor_Read(Reagent_Probe_Position_Sensor))))
				{
					sensor_reached=1;
					break;
				}

		}
		if((sensor_reached==0)&& (Error!="G"))
			{
			 Error="H";	// Does not reach next position
			}
			HAL_Delay(500);

	   Stop_X_Motor();
	}
}
