#include "cmsis_os2.h"

void sett_error(uint8_t error_value, uint16_t* error_codes, osSemaphoreId_t error_sem){

    osStatus_t errc_status = osSemaphoreAcquire(error_sem, 100);

    if(errc_status == osOK){

        *error_codes |= (1U << error_value);

        osSemaphoreRelease(error_sem);

    }

}
