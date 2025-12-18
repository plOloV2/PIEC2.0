/* Copyright 2025 PWR Racing Team
 *
 * This file contains the low-level implementation for PT1000 
 * temperature sensor measurement and conversion.
 *
 * It utilizes the Steinhart-Hart model for high-accuracy 
 * thermistor/RTD linearization and handles raw ADC polling.
 */

#include "main.h"
#include "data_structs.h"
#include "stm32f4xx_hal_adc.h"
#include <math.h>

/** * Steinhart-Hart Coefficients 
 * Calibrated via: https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
 */
#define SH_A    0.06318718787f
#define SH_B    -0.01123112836f
#define SH_C    0.00005477763415f

/**
 * Polls the ADC hardware for four consecutive conversions to update 
 * the raw sensor value buffer.
 *
 * @brief Poll raw ADC values for all PT1000 sensors.
 * @param temp_struct Pointer to the structure where raw values are stored.
 * @param hadc        Pointer to the STM32 ADC handle.
 * @author Aleksander Dziągwa
 */
void measure_temp(temp_PT1000* temp_struct, ADC_HandleTypeDef *hadc) {

    HAL_ADC_Start(hadc);

    // Sequentially poll and store raw values for 4 sensor channels
    for(uint8_t i = 0; i < 4; i++){
        HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
        temp_struct->raw_val_PT1000[i] = HAL_ADC_GetValue(hadc);
    }

}

/** @brief Applies the Steinhart-Hart equation to convert resistance to Celsius. */
float Steinhart_Hart_model_calc(float R) {

    float ln_R = logf(R);

    // Standard Steinhart-Hart formula: 1/T = A + B*ln(R) + C*(ln(R))^3
    return (1.0f / (SH_A + SH_B * ln_R + SH_C * ln_R * ln_R * ln_R)) - 273.15f;
}

/**
 * Iterates through raw sensor values and converts them to physical 
 * Celsius units for all active sensors.
 *
 * @brief Convert raw ADC buffer to Celsius.
 * @param temp_struct Pointer to the shared temperature data structure.
 * @author Aleksander Dziągwa
 */
void calculate_temp_celsius(temp_PT1000* temp_struct) {

    for(uint8_t i = 0; i < 4; i++){
        // Skip sensors that are marked as inactive
        if((temp_struct->active_sensors & (1 << i)) == 0)
            continue;

        float R, V;

        // Convert 12-bit ADC value to normalized voltage ratio
        V = temp_struct->raw_val_PT1000[i] / 4096.0f;

        // Calculate resistance based on the specific voltage divider bridge circuit
        R = 680.0f * ((1.65f - V) / (1.65f + V));

        temp_struct->temp_celsius_PT1000[i] = Steinhart_Hart_model_calc(R);
    }

}
