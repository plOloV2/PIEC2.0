#include "cmsis_os2.h"
#include "data_structs.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>

// void init_furnace_stage(furnace_stage_data* stages);       //not writen yet

// void init_temp_struct(uint8_t active_sensors, temp_PT1000* temps);      //not writen yet

void init_furnace_data(furnace_data* furnace){

    furnace->stage_sem   = osSemaphoreNew(1, 1, NULL);
    furnace->temp_sem    = osSemaphoreNew(1, 1, NULL);
    furnace->time_sem    = osSemaphoreNew(1, 1, NULL);
    furnace->joke_sem    = osSemaphoreNew(1, 1, NULL);
    furnace->errc_sem    = osSemaphoreNew(1, 1, NULL);

    if( !furnace->stage_sem  || !furnace->temp_sem || !furnace->time_sem || 
        !furnace->errc_sem   || !furnace->joke_sem){

        goto Error_Handler;

    }

    return;

    // --- CLEANUP SECTION ---
Error_Handler:
        
    if(furnace->stage_sem) osSemaphoreDelete(furnace->stage_sem);
    if(furnace->temp_sem)  osSemaphoreDelete(furnace->temp_sem);
    if(furnace->joke_sem)  osSemaphoreDelete(furnace->joke_sem);
    if(furnace->errc_sem)  osSemaphoreDelete(furnace->errc_sem);
    if(furnace->time_sem)  osSemaphoreDelete(furnace->time_sem);

    furnace->error_code |= (1U << SEMAPHORES_INIT_FAIL);

}
