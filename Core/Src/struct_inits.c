/* Copyright 2025 PWR Racing Team
 *
 * This file contains the initialization routines for the 
 * furnace system data structures and FreeRTOS resources.
 *
 * It is responsible for safely allocating semaphores and 
 * verifying that all system primitives are correctly 
 * initialized before the scheduler starts.
 */

#include "cmsis_os2.h"
#include "data_structs.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>

/**
 * Initializes the main system structure by creating necessary 
 * FreeRTOS semaphores for thread-safe data access.
 * * If any semaphore allocation fails, the function enters an 
 * error handler to clean up partially allocated resources 
 * and sets the system error flag.
 *
 * @brief Initialize furnace system data and semaphores.
 * @param furnace Pointer to the main furnace_data structure to initialize.
 * @author Aleksander Dziągwa
 */
void init_furnace_data(furnace_data* furnace) {

    // Create binary semaphores with an initial count of 1
    furnace->stage_sem   = osSemaphoreNew(1, 1, NULL);
    furnace->temp_sem    = osSemaphoreNew(1, 1, NULL);
    furnace->time_sem    = osSemaphoreNew(1, 1, NULL);
    furnace->joke_sem    = osSemaphoreNew(1, 1, NULL);
    furnace->errc_sem    = osSemaphoreNew(1, 1, NULL);

    // Validate that all semaphores were successfully created
    if (!furnace->stage_sem || !furnace->temp_sem || !furnace->time_sem || 
        !furnace->errc_sem  || !furnace->joke_sem) {

        goto Error_Handler;
    }

    return;

    /* --- CLEANUP SECTION --- */
    /**
     * Error Handler: Triggered if resource allocation fails.
     * Ensures no "hanging" semaphores remain and marks the 
     * SEMAPHORES_INIT_FAIL error bit.
     */
Error_Handler:
        
    if (furnace->stage_sem) osSemaphoreDelete(furnace->stage_sem);
    if (furnace->temp_sem)  osSemaphoreDelete(furnace->temp_sem);
    if (furnace->joke_sem)  osSemaphoreDelete(furnace->joke_sem);
    if (furnace->errc_sem)  osSemaphoreDelete(furnace->errc_sem);
    if (furnace->time_sem)  osSemaphoreDelete(furnace->time_sem);

    // Record initialization failure in the error bitmask
    furnace->error_code |= (1U << SEMAPHORES_INIT_FAIL);
}
