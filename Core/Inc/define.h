/*
 * define.h
 *
 *  Created on: May 8, 2025
 *      Author: RAGHUL
 */

#ifndef INC_DEFINE_H_
#define INC_DEFINE_H_

 #define RX_BUFFER_SIZE 50  // Max command length
 #define TIMEOUT_MS 1000     // Timeout for character reception
#define SAMPLE_COUNT 1  // Or whatever number you use for averaging
#define SKIP_SAMPLES 20


#include"main.h"

typedef enum {
    CLOCKWISE,
    ANTICLOCKWISE
} PumpDirection;

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
}  Sensor ,LED, ALARM, valve_t,GATE_t;

// Define a structure to hold GPIO configuration for the pump
typedef struct {
    GPIO_TypeDef* pin1_port;
    uint16_t      pin1;
    GPIO_TypeDef* pin2_port;
    uint16_t      pin2;
} Pump;

extern GATE_t P1_P4_GATE ;
extern GATE_t P5_P7_GATE ;
extern GATE_t VL_EXLED_GATE ;


extern Pump WashandUniversalBuffer_Pump;
extern Pump Waste_RemovalPump;

extern valve_t DI_Probe_Inlet;
extern valve_t Waste_Outlet;


// Sensors
extern Sensor Z_Home_Sensor;    				//PC10
extern Sensor Z_EOT_Sensor;  				   //pc11
extern Sensor X_EOT_Sensor;						 // PC3
extern Sensor Reagent_Probe_Position_Sensor;	 //PC2
extern Sensor Nozzle_Probe_Position_Sensor;		//PC12
extern Sensor Syringe_Home_Sensor;
extern Sensor Probe_Crash_Sensor;
extern Sensor Rocking_Home_Sensor;
extern Sensor Rocking_Plate_Sensor;
extern Sensor Tube_Sensor;
extern Sensor WashOrUniversal_Buffer_Sensor ;
extern Sensor DI_Water_Sensor;



// LEDs & Alarm
extern LED GreenLED ;
extern LED RedLED ;
extern LED YellowLED ;
extern ALARM Alarm ;


// Motors
#define Nozzle_Motor_Dir_Clk          HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)    //PB15
#define Nozzle_Motor_Dir_AClk         HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)  //PB15
#define Nozzle_Motor_En               HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_RESET)   //PC13
#define Nozzle_Motor_Dis              HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_SET) //pc13
// Motors
#define Rck_Motor_Dir_Clk             HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET)    //PB14  -> pc0
#define Rck_Motor_Dir_AClk            HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_RESET)  //PB14  ---pc0
#define Rck_Motor_En                  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_RESET)    //PE0
#define Rck_Motor_Dis                 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_SET)  //PE0


#define X_Motor_Dir_Clk               HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)    //PC0
#define X_Motor_Dir_AClk              HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)  //PC0
#define X_Motor_En                    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET)    //PC14
#define X_Motor_Dis                   HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET)  //PC14



// Motors
#define Syringe_Motor_Dir_Clk          HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET)    //PB12
#define Syringe_Motor_Dir_AClk         HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET)  //PB12
#define Syringe_Motor_En               HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_RESET)    //PE3
#define Syringe_Motor_Dis              HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,GPIO_PIN_SET)  //PE3




#define Probe_Motor_Dir_Clk          HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)    //PB13
#define Probe_Motor_Dir_AClk         HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)  //PB13
#define Probe_Motor_En               HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_RESET)    //PE1
#define Probe_Motor_Dis              HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_SET)  //PE1


// Motors


#define RockingFrequencyNormal        225
#define RockingFrequencySlow          20

#define Z_Probe_motor_speed_Frq_Check    500

#define ROCKING_TIMER                  &htim12                                  //9 ch1
#define ROCKING_TIMER_CHANNEL          TIM_CHANNEL_1

#define NOZZLE_TIMER                   &htim11                                 //10 ch1
#define NOZZLE_TIMER_CHANNEL           TIM_CHANNEL_1

#define PROBE_TIMER                    &htim11                                  //11 ch1
#define PROBE_TIMER_CHANNEL            TIM_CHANNEL_1

#define SYRINGE_TIMER                  &htim9                                 //12 ch
#define SYRINGE_TIMER_CHANNEL          TIM_CHANNEL_1

#define X_MOTOR_TIMER                  &htim10                                //10 ch1
#define X_MOTOR_TIMER_CHANNEL          TIM_CHANNEL_1


#define PROBE_DOWN_DIR                   1
#define PROBE_UP_DIR                     0
#define NOZZLE_DOWN_DIR                  0

#define NOZZLE_HOME_MAX_COUNT            500
#define PROBE_HOME_MAX_COUNT             500
#define SYRINGE_EOT_MAX_COUNT            9000
#define SYRINGE_HOME_MAX_COUNT           9500

#define STRIP_DIRECTION                  1
#define REAGENT_BOTTLE_DIRECTION         0
#define PROBE                            1
#define NOZZLE                           2


#define PUMP_REVERSE_COUNT             100
#define WASTE_ASPIRATE_COUNT           100
#define AVERAGE_SAMPLES                  8                 ///< Number of samples to average for stable frequency
#define SIGNAL_TIMEOUT_MS   		   100               ///< Timeout duration (ms) to detect signal loss
#define MAX_STORE_ENTRIES             1000    // adjust as needed



//   ===========for testeing purpose=========//
	// Replace with the actual address from your I2C scan!

//#define MCP4661_ADDR           (0x2F << 1)  // 8-bit format for HAL
#define MCP4661_REG_WIPER0_VOL 0x00         // Volatile Wiper0
#define MCP4661_REG_WIPER1_VOL 0x01         // Volatile Wiper1
////////////////////////////////////////////////////////////////////////
#define ADS7828_ADDR           			    (0x48 << 1)  // 7-bit I2C address shifted left for STM32 HAL
#define POWER_DOWN_BETWEEN_CONVERSIONS 		 0x0C      // PD mode: power-down between conversions
#define PD_POWER_DOWN_AFTER_CONV             0x00  // ADC and reference off
#define PD_REF_ON_ADC_OFF               	 0x01  // Reference stays on
#define PD_REF_OFF_ADC_ON               	 0x02  // ADC stays on
#define PD_ALL_ON                       	 0x03  // Both stay on

#define REFERENCE_VOLTAGE                    5.0f         // External reference voltage (VREF) in volts (updated to 5V)
#define ADC_RESOLUTION                       4096.0f      // 12-bit ADC resolution (2^12)0f      // 12-bit ADC resolution (2^12)

// 7-bit I2C base address for MCP4661 (binary: 0101100)
#define MCP4661_BASE_ADDR 0x2C

// I2C device base addresses for 4 MCP4661 ePOTs (based on hardware A0/A1 wiring)
#define MCP4661_ADDR_EPOT1 (0x29 << 1)  // A1=0, A0=0              0x5
#define MCP4661_ADDR_EPOT2 (0x2B << 1)  // A1=0, A0=1
#define MCP4661_ADDR_EPOT3 (0x2D << 1)  // A1=1, A0=0
#define MCP4661_ADDR_EPOT4 (0x2F << 1)  // A1=1, A0=1


#define MCP4661_ADDR   (0x2B << 1)  // 7-bit 0x28 (0101000b), shifted for HAL
#define WIPER0_EEPROM  0x02
#define WIPER1_EEPROM  0x03
#define STATUS_REG     0x05

#define I2C_Delay_Ms    100

// Write protect control pins (mapped to GPIOs for each device)
#define EPOT1_WP_PORT GPIOB
#define EPOT1_WP_PIN  GPIO_PIN_5
#define EPOT2_WP_PORT GPIOB
#define EPOT2_WP_PIN  GPIO_PIN_4
#define EPOT3_WP_PORT GPIOD
#define EPOT3_WP_PIN  GPIO_PIN_6
#define EPOT4_WP_PORT GPIOD
#define EPOT4_WP_PIN  GPIO_PIN_5

#define I2C2_SCL_PORT GPIOB
#define I2C2_SCL_PIN  GPIO_PIN_10
#define I2C2_SDA_PORT GPIOC
#define I2C2_SDA_PIN  GPIO_PIN_12
#define X_Encoder_Pin GPIO_PIN_6


// Note: Dont change this order,because when we run ADC in single ended mode, the channels are interleaved

#define SampleOrBlocking_Buffer_ADC          0
#define WashOrUniversal_Buffer_ADC           4
#define Conjugate_IgG_ADC                    1
#define Conjugate_IgMOrIgE_ADC               5
#define Subsrtrate_ADC                       2
#define DI_Water_ADC                         6
#define Waste_Full_ADC                       3
#define Vaccum_Sensor_ADC                    7



//#define WashOrUniversal_Buffer_ADC           1
//#define DI_Water_ADC                         5


#define V_LOW  0.72f
#define V_MAX  5.00f
#define MAX_STEP 38


// Calibration constants computed from calibration measurements
#define V_LOW_CAL    -0.07f
#define V_HIGH_CAL    3.60f
#define ADC_LOW_CAL   919
#define ADC_HIGH_CAL  3664




//Fluid Sense
#define TIMER_CLOCK_HZ  (84000000UL / (89 + 1))
#define AVG_SAMPLES 5  // Number of samples to average
#define PRINT_FREQ         0
#define PRINT_FREQ_AVG      1



#define DEBUG 1

#define SAMPLE_INTERVAL_MS       8
#define GATE_TIME_MS 10  // 10ms for 1.7 MHz signal (ADJUST BASED ON THE FREQUENCY)
#define LIQUID_DETECTION_THRESHOLD 70000
#define BUBBLE_CONFIRMATION_COUNT 3
#define BUBBLE_CONFIRMATION_INTERVAL_MS 20

#if DEBUG
#define DEBUG_PRINT(msg) HAL_UART_Transmit(&huart3, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY)
#else
#define DEBUG_PRINT(msg)  // no-op
#endif


#endif /* INC_DEFINE_H_ */
