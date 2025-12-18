/* Copyright 2025 PWR Racing Team
 *
 * This file contains the implementation of the time handler task.
 * This code runs as a FreeRTOS task.
 *
 * The time handler serves as the system scheduler, maintaining 
 * the baking timers and triggering periodic tasks such as 
 * SD card logging and oven control logic.
 */

#include "cmsis_os2.h"
#include "data_structs.h"

/** @brief Interval in seconds for writing data to the SD card. */
#define SD_RECORD_INTERVAL 30

/** @brief Interval in seconds for updating the furnace heating state. */
#define FURNACE_HEAT_SWITCH_INTERVAL 5

/**
 * External function to report system errors in a thread-safe manner.
 */
void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem);

/**
 * Primary timing task. It waits for a 1Hz hardware signal (via flags) 
 * to increment system clocks and manage task scheduling.
 *
 * @brief System timing and task scheduler.
 * @param argument Pointer to the furnace_data main structure.
 * @author Aleksander Dziągwa
 */
void time_handler(void* argument) {
    
    furnace_data* Data = (furnace_data*)argument;

    while (1) {

        // Wait for the 1-second synchronization flag (Timer interrupt)
        osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);

        // Synchronize access to the shared time structure
        if (osSemaphoreAcquire(Data->time_sem, 100) != osOK) {
            sett_error(TIME_SEM_NOT_RECEIVED, &Data->error_code, Data->errc_sem);
            continue;
        }

        Data->furnace_time.seconds++;

        // Handle minute roll-over and update process timers
        if (Data->furnace_time.seconds >= 60) {
            Data->furnace_time.minutes_since_stage++;
            Data->furnace_time.minutes_since_start++;
            Data->furnace_time.seconds = 0;
        }

        // Trigger SD logging at defined intervals
        if (Data->furnace_time.seconds % SD_RECORD_INTERVAL == 0) {
            osThreadResume(Data->SD_id);
        }

        // Trigger heat control logic at defined intervals
        if (Data->furnace_time.seconds % FURNACE_HEAT_SWITCH_INTERVAL == 0) {
            osThreadResume(Data->oven_id);
        }

        // Release time struct semaphore
        osSemaphoreRelease(Data->time_sem);

        // Temperature measurement is resumed every single second
        osThreadResume(Data->temp_id);

    }

}
