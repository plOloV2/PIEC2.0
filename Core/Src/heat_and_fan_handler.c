#include "cmsis_os2.h"
#include "data_structs.h"
#include "heating_logic.h"
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem);

void heat_and_fan_handler(void* argument){
    
    furnace_data* Data = argument;

    while(1){

            // suspends itself
        osThreadSuspend(Data->oven_id);     //neds to be tested if it's safe to first suspend

        if(osSemaphoreAcquire(Data->temp_sem, 100) != osOK){

            sett_error(TEMP_SEM_NOT_RECIVED, &Data->error_code, Data->errc_sem);

            continue;

        }

        if(osSemaphoreAcquire(Data->stage_sem, 100) != osOK){
            
            osSemaphoreRelease(Data->temp_sem);

            sett_error(STAGE_SEM_NOT_RECIVED, &Data->error_code, Data->errc_sem);

            continue;

        }

        heat_controll(Data->furnace_stages, &Data->furnace_temp, &Data->furnace_state);

        if(Data->furnace_state == 0xff){

            HAL_GPIO_WritePin(HEAT_GPIO_Port, HEAT_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_RESET);

            sett_error(NO_VALID_TEMP_READ, &Data->error_code, Data->errc_sem);
        
            osSemaphoreRelease(Data->stage_sem);
            osSemaphoreRelease(Data->temp_sem);

            continue;

        }

        HAL_GPIO_WritePin(HEAT_GPIO_Port, HEAT_Pin, (Data->furnace_state & 1U));

        if(Data->furnace_stages->FAN_ON){

            HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_SET);

            Data->furnace_state |= (1U << 1);

        } else{

            HAL_GPIO_WritePin(FAN_GPIO_Port, FAN_Pin, GPIO_PIN_RESET);

            Data->furnace_state &= ~(1U << 1);

        }
        
        osSemaphoreRelease(Data->stage_sem);
        osSemaphoreRelease(Data->temp_sem);

    }

}
