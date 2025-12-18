/* Copyright 2025 PWR Racing Team
 *
 * This file contains the declaration of temp 
 * measures and conversion functions.
 */

#ifndef TEMP_MEASURE_H
#define TEMP_MEASURE_H

#include "main.h"
#include "data_structs.h"

/**
 * Polls the ADC hardware for four consecutive conversions to update 
 * the raw sensor value buffer.
 *
 * @brief Poll raw ADC values for all PT1000 sensors.
 * @param temp_struct Pointer to the structure where raw values are stored.
 * @param hadc        Pointer to the STM32 ADC handle.
 * @author Aleksander Dziągwa
 */
void measure_temp(temp_PT1000* temp_struct);

/**
 * Iterates through raw sensor values and converts them to physical 
 * Celsius units for all active sensors.
 *
 * @brief Convert raw ADC buffer to Celsius.
 * @param temp_struct Pointer to the shared temperature data structure.
 * @author Aleksander Dziągwa
 */
void calculate_temp_celsius(temp_PT1000* temp_struct);

#endif
