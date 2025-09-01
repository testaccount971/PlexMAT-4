/*
 * Fluid_Sense.h
 *
 *  Created on: May 29, 2025
 *      Author: RAGHUL
 */
//
//#ifndef INC_FLUID_SENSE_H_
//#define INC_FLUID_SENSE_H_
//
//#include "command_processor.h"
//#include "stm32f4xx_hal.h"
//#include "tim.h"
//#include <stdint.h>
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//// Variables used in input capture callback and main loop
//extern volatile uint32_t capture_val_1 ;     ///< First captured timer value (rising edge)
//extern volatile uint32_t capture_val_2 ;     ///< Second captured timer value (next rising edge)
//extern volatile uint8_t capture_ready;      ///< Flag indicating capture state: 0=waiting, 1=first edge done, 2=second edge done
//extern volatile uint32_t last_capture_tick ; ///< Tick count when last capture occurred (for timeout detection)
//
//extern uint32_t freq_buffer[AVERAGE_SAMPLES]; ///< Circular buffer to store frequency samples for averaging
//extern uint8_t freq_index ;                       ///< Current index in frequency buffer
//extern uint8_t buffer_filled;                    ///< Flag indicating buffer has filled at least once
//extern uint32_t average_frequency ;               ///< Calculated average frequency
//
//void process_input_capture(void);
//void print_frequency(uint32_t freq);
//uint32_t GetTimerTickFrequency(TIM_HandleTypeDef *htim);
//
//#ifdef __cplusplus
//}
//#endif
//
//
//#endif /* INC_FLUID_SENSE_H_ */


#ifndef INC_FLUID_SENSE_H_
#define INC_FLUID_SENSE_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "command_processor.h"

extern volatile uint32_t capture1;
extern volatile uint32_t capture2;
extern volatile uint8_t capture_ready;

//
//uint32_t freq_buffer[AVG_SAMPLES] = {0}; // Buffer to store recent frequency samples
//uint8_t freq_index = 0;                  // Index to track current position in buffer
//uint8_t freq_count = 0;                  // Counter to track number of valid samples
//uint16_t total_sample_count = 0;  // Tracks total number of samples received

extern volatile uint32_t capture1 ;
extern volatile uint32_t capture2 ;
extern volatile uint8_t capture_ready ;
extern uint32_t Read_Average_Frequency(void);
extern uint32_t read_frequency_tim3(void);
void Move_And_Monitor_Frequency(uint32_t Maximum_Distance);


extern volatile uint8_t frequency_measured ;  // New flag
extern volatile uint8_t start_measurement;

#endif /* INC_FLUID_SENSE_H_ */

