/* Copyright 2025 PWR Racing Team
 *
 * This file contains the buzzer handler task 
 * implementation. This code is run as a FreeRTOS task.
 *
 * The handler is responsible for playing "music" via buzzer.
 * It should play on startup, when stage ends or when error ocures. 
 */

#include "cmsis_os2.h"
#include "data_structs.h"
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

typedef struct{
    uint16_t frequency;
    uint16_t duration;
} Note;

typedef struct{
    uint8_t num_notes;
    const Note* notes;
} Melody;

static const Melody R2D = {
    .num_notes = 6,
    .notes = (Note[]) {
        {1047, 500},
        {1319, 500},
        {1047, 500},
        {1319, 500},
        {1047, 500},
        {1319, 500}
    }
};
static const Melody stage_end;
static const Melody baking_end;
static const Melody error = {
    .num_notes = 2,
    .notes = (Note[]) {
        {1047, 500},
        {0, 500}
    }
};


void play_err_code(furnace_data* Data){

}

void play_melody(Melody melody){

}


void buzzer_handler(void* argument){

    furnace_data* Data = (furnace_data*)argument;

    while(1){

        uint32_t flag = osThreadFlagsWait(STARTUP_FLAG | STAGE_END_FLAG | BAKING_END_FLAG | ERROR_FLAG, osFlagsWaitAny, osWaitForever);

        if(!(flag & 0x80000000)){

            if(flag & ERROR_FLAG){

                play_err_code(Data);

            }else if(flag & STARTUP_FLAG){

                play_melody(R2D);

            }else if(flag & STAGE_END_FLAG){

                play_melody(stage_end);

            }else if(flag & BAKING_END_FLAG){

                play_melody(baking_end);
                
            }

        }

    }

}
