#ifndef TEMP_MEASURE_H
#define TEMP_MEASURE_H

#include "main.h"
#include "data_structs.h"

void measure_temp(struct temp_PT1000* temp_struct);

void calculate_temp_celsius(struct temp_PT1000* temp_struct);

#endif
