/* Copyright 2025 PWR Racing Team
 *
 * This file contains the declaration of data structs
 * iniciations.
 */

#ifndef INIT_CODE_H
#define INIT_CODE_H

#include "data_structs.h"

/**
 * Initializes the main system structure by creating necessary 
 * FreeRTOS semaphores for thread-safe data access.
 * and sets the system error flag.
 *
 * @brief Initialize furnace system data and semaphores.
 * @param furnace Pointer to the main furnace_data structure to initialize.
 * @author Aleksander Dziągwa
 */
void init_furnace_stage(furnace_stage_data* stages);

void init_temp_struct(temp_PT1000* temps, uint8_t active_sensors);      //not writen yet

void init_furnace_data(furnace_data* furnace);      //not writen yet

#endif
