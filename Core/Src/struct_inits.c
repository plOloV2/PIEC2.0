#include "cmsis_os2.h"
#include "data_structs.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>

// furnace_stage_data* init_furnace_stage();       //not writen yet

// temp_PT1000* init_temp_struct(uint8_t active_sensors);      //not writen yet

furnace_data* init_furnace_data(){

    furnace_data* result = NULL;

    result = (furnace_data*) pvPortMalloc(sizeof(furnace_data));

    if(!result)
        return NULL;

    memset(result, 0, sizeof(furnace_data));

    result->furnace_time = (baking_time*) pvPortMalloc(sizeof(baking_time));

    if(!result->furnace_time){

        vPortFree(result);
        
        return NULL;

    }

    memset(result->furnace_time, 0, sizeof(baking_time));

    result->stage_sem   = osSemaphoreNew(1, 1, NULL);
    result->temp_sem    = osSemaphoreNew(1, 1, NULL);
    result->time_sem    = osSemaphoreNew(1, 1, NULL);
    result->joke_sem    = osSemaphoreNew(1, 1, NULL);
    result->errc_sem    = osSemaphoreNew(1, 1, NULL);

    if( !result->stage_sem  || !result->temp_sem || !result->time_sem || 
        !result->errc_sem   || !result->joke_sem){

        goto Error_Handler;

    }

    return result;

    // --- CLEANUP SECTION ---
Error_Handler:
    if(result) {

        if(result->furnace_time) vPortFree(result->furnace_time);
        
        if(result->stage_sem) osSemaphoreDelete(result->stage_sem);
        if(result->temp_sem)  osSemaphoreDelete(result->temp_sem);
        if(result->joke_sem)  osSemaphoreDelete(result->joke_sem);
        if(result->errc_sem)  osSemaphoreDelete(result->errc_sem);
        if(result->time_sem)  osSemaphoreDelete(result->time_sem);

        vPortFree(result);

    }

    return NULL;

}
