/* Copyright 2025 PWR Racing Team
 *
 * This file contains the declartion of jokes function.
 */

#ifndef JOKES_H
#define JOKES_H

#include <stdint.h>

/**
 * Main entry point for the joke system. Determines which type of 
 * joke to display based on a weighted probability determined by the seed.
 *
 * @brief Retrieve a randomized joke for the system.
 * @param jokes Array of 4 character pointers (strings) of size 32 to hold the output.
 * @param seed  The randomization seed.
 * @author Aleksander Dziągwa
 */
void GetJoke(char** jokes, uint32_t seed);

#endif
