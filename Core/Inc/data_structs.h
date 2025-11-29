#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include "cmsis_os.h"
#include "cmsis_os2.h"
#include <stdint.h>
#include <sys/_intsup.h>

    // struct that holds info about baking stages
typedef struct furnace_stage_s{

    uint16_t    stage_time_min;
    uint8_t     stage_required_temp;
    uint8_t     temp_grow;
    uint8_t     FAN_ON;

    char        stage_name[32];

    struct furnace_stage_s* next_stage;

}furnace_stage_data;


    // structs for PT1000 data
typedef struct{

    uint8_t     active_sensors;
    uint32_t    raw_val_PT1000[4];
    float       temp_celsius_PT1000[4]; 

}temp_PT1000;


    // list of furnace errors
enum FURNACE_ERRORS{
    NO_ERROR,
    FURNACE_STAGES_NULL,
    FURNACE_TEMP_NULL,
    FURNACE_TIME_NULL,
    NO_VALID_TEMP_READ,
    SD_CARD_MISSING,
    SD_CARD_ERR,
    STAGE_SEM_NOT_RECIVED,
    TEMP_SEM_NOT_RECIVED,
    TIME_SEM_NOT_RECIVED,
};

    // time struct
typedef struct{

    uint8_t     seconds;
    uint16_t    minutes_sice_start;
    uint16_t    minutes_sice_stage;

}baking_time;

    // main data struct
typedef struct{

    furnace_stage_data*     furnace_stages;
    temp_PT1000*            furnace_temp;
    baking_time*            furnace_time;

    uint8_t                 num_stages;
    uint8_t                 furnace_state;
    uint16_t                error_code;

    char                    jokes_on_you[4][32];

    osSemaphoreId_t         stage_sem;
    osSemaphoreId_t         temp_sem;
    osSemaphoreId_t         time_sem;
    osSemaphoreId_t         joke_sem;
    osSemaphoreId_t         errc_sem;

    osThreadId_t            time_id;
    osThreadId_t            temp_id;
    osThreadId_t            oven_id;
    osThreadId_t            SD_id;
    osThreadId_t            LCD_id;
    osThreadId_t            BUZZER_id;

}furnace_data;

#endif
