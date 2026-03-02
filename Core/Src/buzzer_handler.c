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
static const Melody error;


void buzzer_handler(void* argument){

}
