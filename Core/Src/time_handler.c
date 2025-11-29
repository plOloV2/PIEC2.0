#include "cmsis_os2.h"
#include "data_structs.h"

#define SD_RECORD_INTERVAL 30
#define FURNACE_HEAT_SWITCH_INTERVAL 5

void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem);

void time_handler(void* argument){
    
    furnace_data* Data = argument;

    while(1){

        osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);

        if(Data->furnace_time == NULL){

            sett_error(FURNACE_TIME_NULL, &Data->error_code, Data->errc_sem);

            continue;

        }

            // waits for time semaphore to be free
        if(osSemaphoreAcquire(Data->time_sem, 100) != osOK){

            sett_error(TIME_SEM_NOT_RECIVED, &Data->error_code, Data->errc_sem);

            continue;

        }

        Data->furnace_time->seconds++;

            // if 60 seconds passed reset second counter and increment minutes
        if(Data->furnace_time->seconds >= 60){

            Data->furnace_time->minutes_sice_stage++;
            Data->furnace_time->minutes_sice_start++;

            Data->furnace_time->seconds = 0;

        }

            // resume recording to SD card every SD_RECORD_INTERVAL
        if(Data->furnace_time->seconds % SD_RECORD_INTERVAL == 0)
            osThreadResume(Data->SD_id);

            // resume control of oven every FURNACE_HEAT_SWITCH_INTERVAL
        if(Data->furnace_time->seconds % FURNACE_HEAT_SWITCH_INTERVAL == 0)
            osThreadResume(Data->oven_id);

        osSemaphoreRelease(Data->time_sem);

            // temp measurement is resumed every second
        osThreadResume(Data->temp_id);

    }

}
