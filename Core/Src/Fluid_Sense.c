/*
 * Fluid_Sense.c
 *
 *  Created on: May 29, 2025
 *      Author: RAGHUL
 */


// frequency_reader.c
#include "Fluid_Sense.h"
#include "command_processor.h"
#include <stdio.h>

volatile uint32_t capture1 = 0;
volatile uint32_t capture2 = 0;
//volatile uint8_t capture_ready = 0;


uint32_t freq_buffer[AVG_SAMPLES] = {0}; // Buffer to store recent frequency samples
uint8_t freq_index = 0;                  // Index to track current position in buffer
uint8_t freq_count = 0;                  // Counter to track number of valid samples
uint16_t total_sample_count = 0;  // Tracks total number of samples received
uint32_t freq=0;


volatile uint8_t frequency_measured = 0;  // New flag
#define SKIP_SAMPLES 20  // Number of initial samples to skip

/*uint32_t Read_Average_Frequency(void)
    {
	   uint32_t average=0;
	   uint32_t start_time = HAL_GetTick();
	   const uint32_t timeout_ms = 3000; // 1 second timeout
	   frequency_measured=0;
	   capture_ready=0;
    	   while(1)
 		  {
 		  if (capture_ready == 2)
 		  	  {

 		  	      // Calculate time delta between two rising edges
 		  	      uint32_t delta;
 		  	      if (capture_val_2 > capture_val_1)
 		  	          delta = capture_val_2 - capture_val_1;
 		  	      else
 		  	          delta = (0xFFFF - capture_val_1 + capture_val_2 + 1); // Handle overflow

 		  	    if (delta == 0)
 		  	    	{
 		  	    	  DEBUG_PRINT ("No frequency Input") ;
 		  	    	}
 		  	    else
 		  	    	{
 		  	    	  freq = TIMER_CLOCK_HZ / delta;    // Calculate frequency
 		  	    	}


 		  	   // --- Averaging logic ---

					// Store measured frequency in circular buffer
					freq_buffer[freq_index++] = freq;
					if (freq_index >= AVG_SAMPLES)
						freq_index = 0;

					// Ensure we only average over available data (during initial filling)
					if (freq_count < AVG_SAMPLES)
						freq_count++;

					// Calculate average frequency
					uint32_t sum = 0;
					for (uint8_t i = 0; i < freq_count; i++)
						sum += freq_buffer[i];
					average = sum / freq_count;

					// --- UART Output ---

					// Display measured and average frequencies via UART

					char msg[128];
					if(PRINT_FREQ)
					{
		    		 snprintf(msg, sizeof(msg),"Freq: %lu Hz\r\n", freq);
				     HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
					}
					if(PRINT_FREQ_AVG)
					{
					snprintf(msg, sizeof(msg),"Avg: %lu Hz\r\n",average);
					HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
					}

					// Reset flags for next measurement
					capture_ready = 0;
					frequency_measured = 1;
 		  	  }
 		        if(frequency_measured==1)
 		    	  {
 		    	     frequency_measured=0;
 		    	     break;
 		    	  }
 		       // Timeout check:
				  if((HAL_GetTick() - start_time) > timeout_ms)
				  {
					  DEBUG_PRINT ("Frequency input timeout");
					  break;
				  }


 		  }
    	   return average; // Return the computed average frequency

    }
*/
uint32_t Read_Average_Frequency(void)
{
    // For now just a single read, add averaging/filter as needed
    return read_frequency_tim3();
}
// --- Frequency reading function using TIM3 external clock ---
uint32_t read_frequency_tim3(void)
{
    uint32_t start_cnt, end_cnt, start_ovf, end_ovf;
    uint32_t count_diff, ovf_diff, pulses_measured;
    uint32_t freq;
    uint32_t start_time = HAL_GetTick();

    __HAL_TIM_SET_COUNTER(&htim3, 0);
    tim3_overflow = 0;

    HAL_TIM_Base_Start_IT(&htim3);
    start_cnt = __HAL_TIM_GET_COUNTER(&htim3);
    start_ovf = tim3_overflow;

    // Non-blocking wait loop for gate time
    while ((HAL_GetTick() - start_time) < GATE_TIME_MS)
    {
        // MCU can do other tasks here
    }

    end_cnt = __HAL_TIM_GET_COUNTER(&htim3);
    end_ovf = tim3_overflow;

    HAL_TIM_Base_Stop_IT(&htim3);

    ovf_diff = end_ovf - start_ovf;

    if (end_cnt >= start_cnt)
        count_diff = end_cnt - start_cnt;
    else
    {
        count_diff = (65536 - start_cnt) + end_cnt;
        if (ovf_diff > 0) ovf_diff--;
    }

    pulses_measured = (ovf_diff * 65536U) + count_diff;

    freq = (pulses_measured * 1000U) / GATE_TIME_MS;
    return freq;
}

//uint32_t read_frequency_tim3(void)
//{
//    uint32_t start_cnt, end_cnt, start_ovf, end_ovf, pulse_count, freq;
//
//    // Reset timer and software overflow before starting
//    __HAL_TIM_SET_COUNTER(&htim3, 0);
//    tim3_overflow = 0;
//
//    // Start base timer (with interrupt enabled for overflow)
//    HAL_TIM_Base_Start_IT(&htim3);
//
//    // Capture starting state
//    start_cnt = __HAL_TIM_GET_COUNTER(&htim3);
//    start_ovf = tim3_overflow;
//
//    // Wait desired measurement interval
//    HAL_Delay(GATE_TIME_MS);
//
//    // Capture ending state
//    end_cnt = __HAL_TIM_GET_COUNTER(&htim3);
//    end_ovf = tim3_overflow;
//
//    HAL_TIM_Base_Stop_IT(&htim3);
//
//    // Handle overflow arithmetic
//    uint32_t ovf_diff = end_ovf - start_ovf;
//    uint32_t count_diff;
//    if (end_cnt >= start_cnt)
//        count_diff = end_cnt - start_cnt;
//    else {
//        count_diff = (65536 - start_cnt) + end_cnt;
//        if (ovf_diff > 0) ovf_diff--; // Subtract one overflow for the wrap
//    }
//    pulse_count = (ovf_diff * 65536U) + count_diff;
//
//    // Convert measured pulses to Hz for the measurement window
//    freq = (pulse_count * 1000U) / GATE_TIME_MS;
//    return freq;
//}

//void Move_And_Monitor_Frequency(uint32_t Maximum_Distance)
//{
//    uint32_t last_sample_time = HAL_GetTick();
//    uint32_t avg_freq = 0;
//    uint32_t prev_freq = 0;
//
//    // Setup probe motor direction and enable outputs as per your logic
//    if (PROBE_DOWN_DIR)
//        Probe_Motor_Dir_Clk;
//    else
//        Probe_Motor_Dir_AClk;
//    Probe_Motor_En; // Enable the probe motor
//
//    Start_Z_Probe_Motor(); // Start the motor pulses (1kHz, 50% duty, 500 pulses)
//
//    // Reset your pulse counter before starting move
//    pulse_count = 0;
//
//    // Initialize prev_freq with the first frequency measurement before loop
//    prev_freq = Read_Average_Frequency();
//
//    while (pulse_count < Maximum_Distance)
//    {
//        uint32_t now = HAL_GetTick();
//        if ((now - last_sample_time) >= 8)
//        {
//            last_sample_time = now;
//            avg_freq = Read_Average_Frequency();
//
//            // Check the change in frequency compared to the previous measurement
//            if (abs((int32_t)avg_freq - (int32_t)prev_freq) > LIQUID_DETECTION_THRESHOLD)
//            {
//                char msg[128];
//                snprintf(msg, sizeof(msg), "Frequency changed from %lu Hz to %lu Hz\r\n", prev_freq, avg_freq);
//                HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
//
//                // Stop motor on significant frequency change
//                Stop_Z_Probe_Motor();
//                break;
//            }
//
//            // Update prev_freq for next comparison
//            prev_freq = avg_freq;
//        }
//        HAL_Delay(1);
//    }
//
//    // Ensure probe is stopped at the end
//    Stop_Z_Probe_Motor();
//}

// Function to move the probe and monitor frequency changes,
// stopping immediately if frequency change exceeds threshold or if an error is detected.
/*void Move_And_Monitor_Frequency(uint32_t Maximum_Distance)
{
	char msg[128];
	 int32_t freq_diff=0;
    // Reset pulse counter to start tracking distance moved
    pulse_count = 0;

    // Set motor direction (clockwise = down)
    Probe_Motor_Dir_Clk;

    // Enable motor driver
    Probe_Motor_En;

    // Start PWM pulses to move motor
 //   Start_Z_Probe_Motor();
	 Start_PWM(PROBE_TIMER, PROBE_TIMER_CHANNEL, Z_Probe_motor_speed_Frq_Check, 50, 0);  // 500kHz, 50% duty, 0 target pulses


    // Store the time of last frequency sample (for timing sampling intervals)
    uint32_t last_sample_time = HAL_GetTick();

    // Variable to hold current and previous frequency measurements
    uint32_t avg_freq = 0;
    uint32_t prev_freq = Read_Average_Frequency();  // Initial baseline frequency reading before moving

    // Main loop to continue moving until target pulses reached or error/condition occurs
    while (pulse_count < Maximum_Distance)
    {
        // Check if any error has been reported externally (e.g., sensor error)
        if (strcmp(Error, "00") != 0)
        {
            // Stop the motor immediately to prevent damage or unexpected behavior
            Stop_Z_Probe_Motor();

            // Print error info to debug output for diagnostics
//            char msg[64];
//            snprintf(msg, sizeof(msg), "Error detected (%s), stopping probe.\r\n", Error);
//            DEBUG_PRINT(msg);

            // Exit function to stop further movement
            return;
        }

        // Get current system time in milliseconds
        uint32_t now = HAL_GetTick();

        // If sampling interval elapsed, read and check frequency
        if ((now - last_sample_time) >= SAMPLE_INTERVAL_MS)
        {
            // Update last sample time for next interval check
            last_sample_time = now;

            // Read current frequency from frequency measurement function
            avg_freq = Read_Average_Frequency();

            // Calculate signed difference from last frequency reading
            freq_diff = (int32_t)avg_freq - (int32_t)prev_freq;

            // If the absolute frequency difference exceeds the liquid detection threshold
            if (abs(freq_diff) > LIQUID_DETECTION_THRESHOLD)
            {
            	   // Stop motor movement immediately upon detection
            	                Stop_Z_Probe_Motor();
                // Exit function, ending probing as event detected
                return;
            }

            // Update previous frequency for next iteration comparison
            prev_freq = avg_freq;
        }


    }

    // Target distance reached without error or threshold exceedance: stop motor normally
    Stop_Z_Probe_Motor();
    // Compose string showing detected frequency jump and current pulse count

		snprintf(msg, sizeof(msg),"Frequency change exceeded threshold: %ld Hz at pulse %lu\r\n",(long)freq_diff, pulse_count);

		// Output message for debugging or logging
		DEBUG_PRINT(msg);


    // Optionally take one last frequency reading and print for final status
    avg_freq = Read_Average_Frequency();
    char final_msg[128];
    snprintf(final_msg, sizeof(final_msg), "Final frequency after move: %lu Hz\r\n", avg_freq);
    DEBUG_PRINT(final_msg);
}
*/





void Move_And_Monitor_Frequency(uint32_t Maximum_Distance)
{
    char msg[128];
    int32_t freq_diff = 0;

    // Reset and start probe motor
    pulse_count = 0;
    Probe_Motor_Dir_Clk;
    Probe_Motor_En;
    Start_PWM(PROBE_TIMER, PROBE_TIMER_CHANNEL,
              Z_Probe_motor_speed_Frq_Check, 50, 0);

    // Timing tracker
    uint32_t last_sample_time = HAL_GetTick();

    // Frequency variables
    uint32_t avg_freq            = 0;
    uint32_t prev_freq           = Read_Average_Frequency();
    uint8_t  consecutive_breaches = 0;

    // Buffers for storing frequencies and deltas at each sample
    uint32_t *freq_log = malloc(MAX_STORE_ENTRIES * sizeof(uint32_t));
    int32_t  *diff_log = malloc(MAX_STORE_ENTRIES * sizeof(int32_t));
    uint32_t store_index = 0;

    while (pulse_count < Maximum_Distance)
    {
        // External error check
        if (strcmp(Error, "00") != 0)
        {
            Stop_Z_Probe_Motor();
   //        Probe_Motor_Dis;
  //          DEBUG_PRINT("Error reported, stopping.\r\n");
            break;
        }

        uint32_t now = HAL_GetTick();

        // Perform sampling and logging every SAMPLE_INTERVAL_MS
        if ((now - last_sample_time) >= SAMPLE_INTERVAL_MS)
        {
            last_sample_time = now;

            // Read current frequency
            avg_freq = Read_Average_Frequency();
            freq_diff = (int32_t)avg_freq - (int32_t)prev_freq;

            // Log frequency and diff
            if (store_index < MAX_STORE_ENTRIES)
            {
                freq_log[store_index] = avg_freq;
                diff_log[store_index] = freq_diff;
                store_index++;
            }

            // Bubble detection: 3 consecutive breaches
            if (abs(freq_diff) > LIQUID_DETECTION_THRESHOLD)
            {
                consecutive_breaches++;
            }
            else
            {
                consecutive_breaches = 0;
            }

            if (consecutive_breaches >= 3)
            {
                Stop_Z_Probe_Motor();
   //             Probe_Motor_Dis;
  //              snprintf(msg, sizeof(msg),
   //                      "fluid detected at pulse %lu\r\n", pulse_count);
  //              DEBUG_PRINT(msg);
                break;
            }

            // Update prev_freq every 5 pulses
            if ((store_index % 5) == 0 && (consecutive_breaches == 0))
            {
                prev_freq = avg_freq;
      /*          snprintf(msg, sizeof(msg),
                         "pF: %lu @ %lu\r\n",
                         prev_freq, store_index);
                DEBUG_PRINT(msg);*/
            }
        }
    }

    // Ensure motor is stopped
    Stop_Z_Probe_Motor();
//    Probe_Motor_Dis;

  //   Print stored frequencies and deltas over UART for debugging
   /* for (uint32_t i = 0; i < store_index; i++)
    {
        snprintf(msg, sizeof(msg),
                 "Log[%lu]: Freq=%lu Hz, Δf=%ld Hz\r\n",
                 i, freq_log[i], diff_log[i]);
        DEBUG_PRINT(msg);
    }*/
    if(pulse_count>=Maximum_Distance)
	{
//		snprintf(msg, sizeof(msg),
//				"Max distance reached: %lu pulses, no fluid detected\r\n", pulse_count);
//		DEBUG_PRINT(msg);
    	Error="Q";
	}

    free(freq_log);
    free(diff_log);
}





