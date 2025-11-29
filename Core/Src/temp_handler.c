#include "cmsis_os2.h"
#include "data_structs.h"
#include "temp_measure.h"

void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem);

void temp_handler(void* argument){
    
    furnace_data* Data = argument;

    while(1){

        if(Data->furnace_temp == NULL){

            sett_error(FURNACE_TEMP_NULL, &Data->error_code, Data->errc_sem);

            continue;

        }

        if(osSemaphoreAcquire(Data->temp_sem, 100) != osOK){

            sett_error(TEMP_SEM_NOT_RECIVED, &Data->error_code, Data->errc_sem);

            continue;

        }

        measure_temp(Data->furnace_temp);

        calculate_temp_celsius(Data->furnace_temp);

            // suspends itself
        osThreadSuspend(Data->temp_id);

    }

}
