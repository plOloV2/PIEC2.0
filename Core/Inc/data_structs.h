#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include "main.h"


struct furnace_stage_data{

    uint16_t    stage_time_min;
    uint8_t     stage_required_temp;
    uint8_t     temp_grow;
    uint8_t     FAN_ON;

    char*       stage_name[32];

    struct furnace_stage_data* next_stage;

};

struct furnace_stage_data* furnace_stage_init();


struct temp_PT1000{

    uint8_t     active_sensors;
    uint32_t    raw_val_PT1000[4];
    float       temp_celsius_PT1000[4]; 

};

struct temp_PT1000* init_temp_struct(uint8_t active_sensors);

#endif
