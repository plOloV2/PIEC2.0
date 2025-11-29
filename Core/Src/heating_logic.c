#include "main.h"
#include "data_structs.h"
#include <math.h>

#define EPSILON 10.0f
#define HYSTERESIS 3.0f

float current_temp(temp_PT1000* temp_data){

    uint8_t is_valid, change;

    is_valid = temp_data->active_sensors;

    do{

        change = 0;
        uint8_t num_PT1000 = 0;
        float average = 0;

        for(uint8_t i = 0; i < 4; i++){

            if((is_valid & (1 << i)) == 0)
                continue;

            average += temp_data->temp_celsius_PT1000[i];
            num_PT1000++;

        }

        if(num_PT1000 == 0)
            return 500.0f;

        average /= num_PT1000;

        for(uint8_t i = 0; i < 4; i++){

            if((is_valid & (1 << i)) != 0 && fabsf(average - temp_data->temp_celsius_PT1000[i]) > EPSILON){

                change = 1;
                is_valid &= ~(1 << i);

            }

        }


    } while(change != 0);
    
    float result = 500.0f;

   for(uint8_t i = 0; i < 4; i++)
        if((is_valid & (1 << i)) != 0)
            if(result == 500.0f || temp_data->temp_celsius_PT1000[i] < result)
                result = temp_data->temp_celsius_PT1000[i];
            
    return result;

}

void heat_controll(furnace_stage_data* stage_data, temp_PT1000* temp_data, uint8_t* heat_state){

    float measured_temp = current_temp(temp_data);

    if(measured_temp >= 300.0f){

        *heat_state = 0xff;

        return;

    }

    if(measured_temp < (stage_data->stage_required_temp - HYSTERESIS/2.0f)){

        *heat_state  |= 1U;

    }else if(measured_temp > (stage_data->stage_required_temp + HYSTERESIS/2.0f)){

        *heat_state &= ~1U;

    }

}
