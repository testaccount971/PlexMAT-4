/*
 * Rocking_Motor.c
 *
 *  Created on: May 19, 2025
 *      Author: RAGHUL
 */
#include "command_processor.h"
#include "Rocking_Motor.h"
 volatile int plate_cnt = 0;
 extern char *Error;
 uint32_t Rocking_motor_pulses = 50;  // default value
 uint32_t home_cnt = 0;  // Definition (and optional initialization)

void Start_Rocking_Motor( int Rocking_motor_speed, int Rocking_motor_pulses)
{
	   plate_cnt=0;
       home_cnt=0;
	   Rck_Motor_Dir_Clk;
       Rck_Motor_En;
	 //  Start_PWM(Rocking_motor_speed, Rocking_motor_pulses); // Generates 200 pulses at 1 kHz

     	Start_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL, Rocking_motor_speed, 50, 500);  // 1kHz, 50% duty, 500 pulses
     	HAL_Delay(100);



}
void Stop_Rocking_Motor()
{
	Stop_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL);
	 pulse_count=0;
	 plate_cnt=0;
	 home_cnt=0;
	 Rck_Motor_Dir_AClk;

}
void Rocking_Slow(int Rocking_motor_speed, int Rocking_motor_pulses)
{
	plate_cnt=0;
    home_cnt=0;
	Rck_Motor_Dir_Clk;
    Rck_Motor_En;
    pulse_count=0;
 //   putchr('@');
 //   Send_Count(pulse_count);
	Start_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL, RockingFrequencyNormal, 50, Rocking_motor_pulses);  // 1kHz, 50% duty, 500 pulses

	 while ((Sensor_Read(Rocking_Home_Sensor) == 0) && (pulse_count <= 1000))
		 {
		    //wait
		 }
		 // Stop PWM and related operations
		 Stop_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL);
	     if(pulse_count >= 1000)
	    	 {
//	    	 putchr('&');
//	    	 Send_Count(pulse_count);
	    	 Error="L";
	    	 }
	     else
	    	 {
	    	 Error="00";
	    	 }

	 Stop_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL);
	 if(strcmp("00",Error)==0)
	 {
	   Start_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL, Rocking_motor_speed, 50, Rocking_motor_pulses);  // 1kHz, 50% duty, 500 pulses
       HAL_Delay(5000);
       if((Sensor_Read(Rocking_Home_Sensor))==1)
    	   {
 //   	   putchr('#');
//    	  Send_Count(pulse_count);
    	   Error= "I" ;
    	   }
        if(strcmp("00",Error)==0) HAL_Delay(30000);
		if(strcmp("00",Error)==0) Home_Rocking_Motor(1000);
	 }
	 Stop_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL);
	      pulse_count=0;

}

void Home_Rocking_Motor(uint32_t Maximum_Pulses)
{
     pulse_count=0;
	 Rck_Motor_Dir_Clk;
	 Rck_Motor_En;
//	 Start_PWM(RockingFrequencyNormal, 0); // Generates 200 pulses at 1 kHz
	 Start_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL, RockingFrequencyNormal, 50, Rocking_motor_pulses);
	 if((Sensor_Read(Rocking_Home_Sensor))==1)
	 {
 	     while(pulse_count<50);
	     if((Sensor_Read(Rocking_Home_Sensor))==1)
	    	 {

	    	   Error= "L" ;// wait till the mechanism goes out of home
	    	 }
		 pulse_count=0;
	 }
	 // Wait until the Rocking_home sensor is triggered OR pulse limit is reached
	 while ((Sensor_Read(Rocking_Home_Sensor) == 0) && (pulse_count <= Maximum_Pulses))
	 {
	    //wait
	 }
	 // Stop PWM and related operations
	 Stop_PWM(ROCKING_TIMER, ROCKING_TIMER_CHANNEL);
     if(pulse_count >= Maximum_Pulses) Error="L";
      pulse_count=0;
      plate_cnt=0;
      home_cnt=0;
}

//pulse_count=0;
//	 Rck_Motor_Dir_Clk;
//	 Rck_Motor_En;
//	 Start_PWM(RockingFrequencyNormal, 0); // Generates 200 pulses at 1 kHz
//	 if((Sensor_Read(Rocking_home))==1)
//	 {
//	     while(pulse_count<100);
//	     if((Sensor_Read(Rocking_home))==1)
//	    	 {
//
//	    	   Error= "L" ;// wait till the mechanism goes out of home
//	    	 }
//		 pulse_count=0;
//	 }
//	 // Wait until the Rocking_home sensor is triggered OR pulse limit is reached
//	 while ((Sensor_Read(Rocking_home) == 0) && (pulse_count <= Maximum_Pulses))
//	 {
//	    //wait
//	 }
//	 // Stop PWM and related operations
//	 HAL_TIM_PWM_Stop(&htim9, TIM_CHANNEL_1);     // Stop PWM output
//	 HAL_TIM_Base_Stop_IT(&htim9);                // Stop timer interrupt (used for pulse counting)
//   if(pulse_count >= Maximum_Pulses) Error="L";
//    pulse_count=0;
//    plate_cnt=0;
//    home_cnt=0;
void Rocking_Count_Function()
{
//	 Send_Count(home_cnt);
//	 putchr('@');
//	 Send_Count(plate_cnt);
	 if ((home_cnt == 0) && (plate_cnt==0))Error="I"; 	// Rocking mechanism not moving and it is at home
	 else if (home_cnt==0) Error="K"; 	// Rocking mechanism not moving and it is not at home
//	 else if (plate_cnt==0)Error="J";	// Plate switch not sensed
	 plate_cnt=0;
	 home_cnt=0;
}
