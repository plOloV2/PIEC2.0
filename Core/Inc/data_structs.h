/* Copyright 2025 PWR Racing Team
 *
 * This file contains the data structures for the furnace 
 * control system, including temperature monitoring, 
 * baking stages, and FreeRTOS synchronization primitives.
 */

#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

#include "cmsis_os.h"
#include "cmsis_os2.h"
#include <stdint.h>

/**
 * @brief Structure that holds information about individual baking stages.
 */
typedef struct {
    /** @brief Stage duration in minutes. */
    uint16_t stage_time_min;

    /** @brief Target temperature in Celsius. 0xFF indicates an error or unset state. */
    uint8_t stage_required_temp;

    /** * @brief Temperature growth rate in degrees per minute.
     * Values are typically between 0.0 and 10.0. 
     * Divide this integer value by 10 to obtain the actual decimal value.
     */
    uint8_t temp_grow;

    /** @brief Boolean flag; non-zero if the fan is active during this stage. */
    uint8_t FAN_ON;

    /** @brief Name of the stage for LCD display purposes (max 32 chars). */
    char stage_name[32];
} furnace_stage_data;

/**
 * @brief Structure for PT1000 sensor data and processing.
 */
typedef struct {
    /** @brief Bitmask of active sensors for error rejection algorithms. */
    uint8_t active_sensors;

    /** @brief Raw ADC values measured from four PT1000 sensors. */
    uint32_t raw_val_PT1000[4];

    /** @brief Converted temperature values in Celsius. */
    float temp_celsius_PT1000[4];
} temp_PT1000;

/**
 * @brief List of furnace system error codes.
 */
enum FURNACE_ERRORS {
    SEMAPHORES_INIT_FAIL,   /**< Failed to initialize FreeRTOS semaphores. */
    NO_VALID_TEMP_READ,     /**< Failed to obtain any valid temperature reading. */
    SD_CARD_MISSING,        /**< Failed to detect the SD card. */
    SD_CARD_ERR,            /**< Failed to read from or write to the SD card. */
    STAGE_SEM_NOT_RECEIVED, /**< Failed to obtain semaphore for furnace_stage_data. */
    TEMP_SEM_NOT_RECEIVED,  /**< Failed to obtain semaphore for temp_PT1000. */
    TIME_SEM_NOT_RECEIVED,  /**< Failed to obtain semaphore for baking_time. */
};

/**
 * @brief Structure for tracking baking duration and stage progress.
 */
typedef struct {
    /** @brief Current second count. */
    uint8_t seconds;

    /** @brief Total minutes elapsed since the baking process started. */
    uint16_t minutes_since_start;

    /** @brief Minutes elapsed since the current stage began. */
    uint16_t minutes_since_stage;
} baking_time;

/**
 * @brief Main system data structure.
 * Contains all sub-structures, thread IDs, and synchronization primitives.
 */
typedef struct {
    /* --- Sub-structures --- */
    furnace_stage_data furnace_stages[10];
    temp_PT1000 furnace_temp;
    baking_time furnace_time;

    /** @brief Index of the current active stage. */
    uint8_t curr_stages;

    /** 
     * @brief Current operational state of the furnace.
     * 0xff -> error ocured while calculating state,
     * heating elements and fan are off.
     */
    uint8_t furnace_state;

    /** @brief Current system error code (0 indicates no error). */
    uint16_t error_code;

    /** @brief Buffer for jokes. */
    char jokes_on_you[4][32];

    /* --- FreeRTOS Semaphores --- */
    osSemaphoreId_t stage_sem; /**< Semaphore for furnace_stage_data access. */
    osSemaphoreId_t temp_sem;  /**< Semaphore for temp_PT1000 access. */
    osSemaphoreId_t time_sem;  /**< Semaphore for baking_time access. */
    osSemaphoreId_t joke_sem;  /**< Semaphore for joke buffer access. */
    osSemaphoreId_t errc_sem;  /**< Semaphore for error_code access. */

    /* --- FreeRTOS Thread IDs --- */
    osThreadId_t time_id;
    osThreadId_t temp_id;
    osThreadId_t oven_id;
    osThreadId_t SD_id;
    osThreadId_t LCD_id;
    osThreadId_t BUZZER_id;

} furnace_data;

#endif // DATA_STRUCTS_H_