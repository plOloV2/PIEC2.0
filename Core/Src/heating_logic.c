#include "main.h"
#include "data_structs.h"
#include <math.h>

#define EPSILON 10.0
#define HYSTERESIS 3.0  

float current_temp(struct temp_PT1000* temp_data){

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
            return 500.0;

        average /= num_PT1000;

        for(uint8_t i = 0; i < 4; i++){

            if(fabsf(average - temp_data->temp_celsius_PT1000[i]) > EPSILON){

                change = 1;
                is_valid = is_valid & ~(1 << i);

            }

        }


    } while(change != 0);
    
    float result = 500.0;

    for(uint8_t i = 0; i < 4; i++)
        if((is_valid & (1 << i)) != 0 && temp_data->temp_celsius_PT1000[i] < result)
            result = temp_data->temp_celsius_PT1000[i];

    return result;

}

void heat_controll(struct furnace_stage_data* stage_data, struct temp_PT1000* temp_data, uint8_t* heat_state){

    float measured_temp = current_temp(temp_data);

    if(measured_temp >= 300.0)
        return;

    if(measured_temp < (stage_data->stage_required_temp - HYSTERESIS/2)){

        *heat_state = 1;

    }else if(measured_temp > (stage_data->stage_required_temp + HYSTERESIS/2)){

        *heat_state = 0;

    }

}
