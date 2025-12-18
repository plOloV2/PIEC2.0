/* Copyright 2025 PWR Racing Team
 *
 * This file contains the implementation of the heating logic.
 * It includes algorithms for processing multi-sensor PT1000 data
 * and controlling the furnace heating state based on hysteresis.
 */

#include "main.h"
#include "data_structs.h"
#include <math.h>

/** @brief Threshold for outlier detection in temperature readings (Celsius). */
#define EPSILON 10.0f

/** @brief Total temperature range for the control hysteresis (Celsius). */
#define HYSTERESIS 3.0f

/**
 * Calculates a reliable temperature from multiple PT1000 sensors.
 * It uses an iterative error-rejection algorithm to remove sensor 
 * readings that deviate from the average by more than EPSILON. 
 * Finally, it returns the minimum value from the remaining valid sensors.
 *
 * @brief Calculate filtered temperature.
 * @param temp_data Pointer to the PT1000 sensor data structure.
 * @return The calculated temperature in Celsius, or 500.0f if no sensors are valid.
 * @author Aleksander Dziągwa
 */
float current_temp(temp_PT1000* temp_data) {

    uint8_t is_valid, change;

    // Start with the mask of sensors currently marked as active
    is_valid = temp_data->active_sensors;

    do {
        change = 0;
        uint8_t num_PT1000 = 0;
        float average = 0;

        // Calculate average of currently valid sensors
        for (uint8_t i = 0; i < 4; i++) {
            if ((is_valid & (1 << i)) == 0)
                continue;

            average += temp_data->temp_celsius_PT1000[i];
            num_PT1000++;
        }

        // Handle case where no valid sensors remain
        if (num_PT1000 == 0)
            return 500.0f;

        average /= num_PT1000;

        // Outlier rejection: identify sensors too far from the average
        for (uint8_t i = 0; i < 4; i++) {
            if ((is_valid & (1 << i)) != 0 && fabsf(average - temp_data->temp_celsius_PT1000[i]) > EPSILON) {
                change = 1;
                is_valid &= ~(1 << i); // Remove sensor from valid mask
            }
        }

    } while (change != 0); // Repeat if any outliers were removed
    
    float result = 500.0f;

    // Determine the minimum value among the remaining valid sensors
    for (uint8_t i = 0; i < 4; i++) {
        if ((is_valid & (1 << i)) != 0) {
            if (result == 500.0f || temp_data->temp_celsius_PT1000[i] < result) {
                result = temp_data->temp_celsius_PT1000[i];
            }
        }
    }
            
    return result;
}

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
void heat_controll(furnace_stage_data* stage_data, temp_PT1000* temp_data, uint8_t* heat_state) {

    float measured_temp = current_temp(temp_data);

    // Error safety check: readings above 250C (error) trigger shutdown
    if (measured_temp >= 250.0f) {
        *heat_state = 0xff;
        return;
    }

    // Hysteresis control logic
    if (measured_temp < (stage_data->stage_required_temp - HYSTERESIS / 2.0f)) {
        // Temperature too low: turn heater ON
        *heat_state |= 1U;
    } else if (measured_temp > (stage_data->stage_required_temp + HYSTERESIS / 2.0f)) {
        // Temperature too high: turn heater OFF
        *heat_state &= ~1U;
    }
}
