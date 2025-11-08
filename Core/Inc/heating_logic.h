#ifndef HEATING_LOGIC_H
#define HEATING_LOGIC_H

#include "main.h"
#include "data_structs.h"

uint8_t heat_controll(struct furnace_stage_data* stage_data, struct temp_PT1000* temp_data);

#endif
