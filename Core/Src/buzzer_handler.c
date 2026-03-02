/* Copyright 2025 PWR Racing Team
 *
 * This file contains the heat and fan handler task 
 * implementation. This code is run as a FreeRTOS task.
 *
 * The handler is responsible for processing the heating 
 * logic and driving the physical GPIO pins for the 
 * heating element and the fan based on current sensor data.
 */

#include "cmsis_os2.h"
#include "data_structs.h"
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

/**
 * External function to report system errors in a thread-safe manner.
 */
void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem);

typedef struct{
    uint16_t frequency;
    uint16_t duration;
} Note;

typedef struct{
    uint8_t num_notes;
    Note* notes;
} Melody;

void buzzer_handler(void* argument){

}
