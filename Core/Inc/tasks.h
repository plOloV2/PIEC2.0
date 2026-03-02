/* Copyright 2025 PWR Racing Team
 *
 * This file contains the declaration of tasks functions.
 */

#ifndef TASKS_H
#define TASKS_H

/**
 * Primary timing task. It waits for a 1Hz hardware signal (via flags) 
 * to increment system clocks and manage task scheduling.
 *
 * @brief System timing and task scheduler.
 * @param argument Pointer to the furnace_data main structure.
 * @author Aleksander Dziągwa
 */
void time_handler(void* argument);

/**
 * Task responsible for managing the temperature measurement cycle. 
 * It acquires necessary semaphores, triggers ADC polling, 
 * processes raw values.
 *
 * @brief Temperature measurement orchestration task.
 * @param argument Pointer to the furnace_data main structure.
 * @author Aleksander Dziągwa
 */
void temp_handler(void* argument);

/**
 * Task responsible for managing the furnace hardware state. 
 * It synchronizes with temperature and stage data to 
 * determine the appropriate GPIO outputs.
 *
 * @brief Heat and fan management task.
 * @param argument Pointer to the furnace_data main structure.
 * @author Aleksander Dziągwa
 */
void heat_and_fan_handler(void* argument);

/**
 * Task responsible for playing sounds with simple
 * buzzer located on PCB.
 * 
 * @brief Buzzer management task.
 * @param argument Pointer to the melody structure.
 * @author Aleksander Dziągwa
 */
void buzzer_handler(void* argument);

#endif
