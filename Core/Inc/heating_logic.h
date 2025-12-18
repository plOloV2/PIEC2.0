/* Copyright 2025 PWR Racing Team
 *
 * This file contains the declaration of heat controll function.
 */
#ifndef HEATING_LOGIC_H
#define HEATING_LOGIC_H

#include "main.h"
#include "data_structs.h"

/**
 * Determines the next heater state based on measured temperature and targets.
 * Implements a hysteresis controller to prevent rapid switching. 
 * If the temperature reading is invalid, it sets an error state.
 *
 * @brief Heating state controller.
 * @param stage_data Pointer to current stage requirements.
 * @param temp_data  Pointer to current sensor measurements.
 * @param heat_state Pointer to the current system state bitmask to be updated.
 * @author Aleksander Dziągwa
 */
void heat_controll(furnace_stage_data* stage_data, temp_PT1000* temp_data, uint8_t* heat_state);

#endif
