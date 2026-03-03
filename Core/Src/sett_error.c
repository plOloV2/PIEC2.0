/* Copyright 2025 PWR Racing Team
 *
 * This file contains the implementation of the error 
 * setting utility function. This code ensures that 
 * error flags are updated in a thread-safe manner.
 *
 * The sett_error function is responsible for updating 
 * the global error bitmask using a semaphore for 
 * synchronization.
 */

#include "cmsis_os2.h"
#include "data_structs.h"
#include <stdint.h>

/**
 * Updates the system error bitmask by setting a specific bit.
 * It uses a semaphore to prevent race conditions when multiple
 * threads attempt to report an error simultaneously.
 *
 * @brief Set system error bit.
 * @param error_value The bit position to set (the error index).
 * @param error_codes Pointer to the shared 16-bit error mask.
 * @param error_sem   The semaphore used for thread synchronization.
 * @author Aleksander Dziągwa
 */
void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem, osThreadId_t buzz_id){

    // Attempt to acquire the semaphore with a 100ms timeout
    osStatus_t errc_status = osSemaphoreAcquire(error_sem, 100);

    if(errc_status == osOK){

        // Set the bit corresponding to the error value using bitwise OR
        *error_codes |= (1U << error_value);

        // Release the semaphore back to the system
        osSemaphoreRelease(error_sem);

        osThreadFlagsSet(buzz_id, ERROR_FLAG);

    }

}
