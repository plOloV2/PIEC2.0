/* Copyright 2025 PWR Racing Team
 *
 * This file contains the implementation of the temperature 
 * handler task. This code runs as a FreeRTOS task.
 *
 * The temperature handler is responsible for orchestrating 
 * sensor measurements and unit conversions, ensuring data 
 * is refreshed before the task suspends itself.
 */

#include "cmsis_os2.h"
#include "data_structs.h"
#include "temp_measure.h"

/**
 * External function to report system errors in a thread-safe manner.
 */
void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem);

/**
 * Task responsible for managing the temperature measurement cycle. 
 * It acquires necessary semaphores, triggers ADC polling, 
 * processes raw values, and then enters a suspended state.
 *
 * @brief Temperature measurement orchestration task.
 * @param argument Pointer to the furnace_data main structure.
 * @author Aleksander Dziągwa
 */
void temp_handler(void* argument) {
    
    furnace_data* Data = (furnace_data*)argument;

    while(1){

        // Attempt to acquire temperature data semaphore before writing
        if (osSemaphoreAcquire(Data->temp_sem, 100) != osOK) {
            sett_error(TEMP_SEM_NOT_RECEIVED, &Data->error_code, Data->errc_sem);
            continue;
        }

        // Execute low-level ADC measurement
        measure_temp(&Data->furnace_temp);

        // Convert raw ADC values to Celsius using Steinhart-Hart Coefficients
        calculate_temp_celsius(&Data->furnace_temp);

        // Release the semaphore so other tasks (like logic or UI) can read the data
        osSemaphoreRelease(Data->temp_sem);

        // Task suspends itself; it is resumed periodically by the time_handler
        osThreadSuspend(Data->temp_id);

    }

}
