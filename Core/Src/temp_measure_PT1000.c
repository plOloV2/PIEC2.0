#include "main.h"
#include "data_structs.h"
#include "stm32f4xx_hal_adc.h"
#include <math.h>

// Values used in Steinhart-Hart equation
// Got them from: https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
#define SH_A    0.06318718787f
#define SH_B    -0.01123112836f
#define SH_C    0.00005477763415f

void measure_temp(struct temp_PT1000* temp_struct, ADC_HandleTypeDef *hadc){

    HAL_ADC_Start(hadc);

    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    temp_struct->raw_val_PT1000[0] = HAL_ADC_GetValue(hadc);
    
    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    temp_struct->raw_val_PT1000[1] = HAL_ADC_GetValue(hadc);
    
    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    temp_struct->raw_val_PT1000[2] = HAL_ADC_GetValue(hadc);
    
    HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
    temp_struct->raw_val_PT1000[3] = HAL_ADC_GetValue(hadc);

}

float Steinhart_Hart_model_calc(float R){

    float ln_R = logf(R);

    return (1.0/(SH_A + SH_B*ln_R + SH_C*ln_R*ln_R*ln_R)) - 273.15f;

}

void calculate_temp_celsius(struct temp_PT1000* temp_struct){

    for(uint8_t i = 0; i < 4; i++){

        if((temp_struct->active_sensors & (1 << i)) == 0)
            continue;

        float R, V;

        V = temp_struct->raw_val_PT1000[i] / 4096.0f;

        R = 680.0f * ((1.65f - V) / (1.65f + V));

        temp_struct->temp_celsius_PT1000[i] = Steinhart_Hart_model_calc(R);

    }

}
