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
#include "heating_logic.h"
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

/**
 * External function to report system errors in a thread-safe manner.
 */
void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem);

/**
 * Task responsible for managing the furnace hardware state. 
 * It synchronizes with temperature and stage data to 
 * determine the appropriate GPIO outputs.
 *
 * @brief Heat and fan management task.
 * @param argument Pointer to the furnace_data main structure.
 * @author Aleksander Dziągwa
 */
void heat_and_fan_handler(void* argument){
    
    furnace_data* Data = (furnace_data*)argument;

    /* Infinite loop */
    while(1){

        // The task suspends itself until resumed by the scheduler or another task
        osThreadSuspend(Data->oven_id);

        // Attempt to acquire temperature data semaphore
        if (osSemaphoreAcquire(Data->temp_sem, 100) != osOK) {
            sett_error(TEMP_SEM_NOT_RECEIVED, &Data->error_code, Data->errc_sem);
            continue;
        }

        // Attempt to acquire baking stage data semaphore
        if (osSemaphoreAcquire(Data->stage_sem, 100) != osOK) {
            osSemaphoreRelease(Data->temp_sem);
            sett_error(STAGE_SEM_NOT_RECEIVED, &Data->error_code, Data->errc_sem);
            continue;
        }

        // Calculate required heating state based on logic rules
        heat_controll(Data->furnace_stages, &Data->furnace_temp, &Data->furnace_state);

        // Check for critical temperature errors (0xff indicates invalid readings)
        if (Data->furnace_state == 0xff) {
            // Safety shutdown of all hardware elements
            HAL_GPIO_WritePin(HEAT_GPIO_Port, HEAT_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_RESET);

            // Sett error for no valid temp read
            sett_error(NO_VALID_TEMP_READ, &Data->error_code, Data->errc_sem);
        
            osSemaphoreRelease(Data->stage_sem);
            osSemaphoreRelease(Data->temp_sem);
            continue;
        }

        // Update Heater GPIO based on the first bit of furnace_state
        HAL_GPIO_WritePin(HEAT_GPIO_Port, HEAT_Pin, (Data->furnace_state & 1U));

        // Update Fan GPIO and status bit based on stage configuration
        if (Data->furnace_stages->FAN_ON) {
            HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_SET);
            Data->furnace_state |= (1U << 1); // Mark fan as ON in state mask
        } else {
            HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_RESET);
            Data->furnace_state &= ~(1U << 1); // Mark fan as OFF in state mask
        }
        
        // Release resources for other tasks
        osSemaphoreRelease(Data->stage_sem);
        osSemaphoreRelease(Data->temp_sem);
    }

}
