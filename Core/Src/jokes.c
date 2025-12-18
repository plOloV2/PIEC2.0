/* Copyright 2025 PWR Racing Team
 *
 * This file contains the most important part of oven:
 *
 *              *** JOKES ***
 */

#include "data_structs.h"
#include <stdint.h>

/** @brief Constant pointer to an empty string for unused joke lines. */
static char* EMPTY = "";

/**
 * Generates a randomized joke by combining 
 * a name and an action from predefined internal lists.
 *
 * @brief Generate a dynamic person/action joke.
 * @param jokes Pointer to an array of four strings to be populated.
 * @param seed  Randomization seed used to select indices.
 * @author Aleksander Dziągwa
 */
void funny1(char** jokes, uint32_t seed) {

static const char* names[] = {
        "Michal Dowgiallo",
        "Zuber",
        "Sobczak",
        "Olek Dziagwa",
        "Przemo Kaluza",
        "Domino",
        "Igor Zielonka",
        "Jakub Koman",
        "Kuba Ruchala",
        "Wadas",
        "Maciej Sikora",
        "Mateusz Grozdanovic",
        "Wiktor Kurwicki",
        "Patryk Koltun",
        "Nina",
        "Nazarii",
        "Mikolaj Stojowski",
        "Twoja babka",
        "Dzial Chassis", 
        "Baba z portierni",
        "Marketing",
        "Suspension"
    };

    static const char* actions[] = {
        "laminuje",
        "zamyka worek",
        "zamyka morde",
        "klei takitejpa",
        "udaje że pracuje",
        "odsysa worek",
        "szlifuje rdzen",
        "stawia browary",
        "tnie worek",
        "daje fula",
        "jest glodny/a",
        "jest zly/a",
        "chce do domu",
        "tnie wykroje",
        "masuje uszczelke",
        "szlifuje formy",
        "wchodzi do pieca",
        "idzie do pirmu",
        "gwintuje inserty",
        "zlamal endplate",
        "wyrwal wklejke",
        "depnal na ub",
        "udaje greka",
        "ma wszy",
        "nic nie rozumie",
        "jest szalony"
    };

    // Select name and action based on the seed modulo the array size
    jokes[0] = (char*)names[seed % 22];
    jokes[1] = (char*)actions[seed % 26];
    
    // Clear remaining lines
    jokes[2] = EMPTY;
    jokes[3] = EMPTY;
}

/**
 * Selects a predefined multi-line joke from a hardcoded list.
 *
 * @brief Generate a static multi-line joke.
 * @param jokes Pointer to an array of four strings to be populated.
 * @param seed  Randomization seed used to select the joke index.
 * @author Aleksander Dziągwa
 */
void funny2(char** jokes, uint32_t seed) {

    /** @brief Internal structure to map jokes to the 4-line LCD layout. */
    typedef struct {
        const char* line0;
        const char* line1;
        const char* line2;
        const char* line3;
    } JokeLines;

    static const JokeLines entries[] = {
        {"Na wszelki wypadek to",           "ksiadz chuja w gaciach nosi",  "",                             "" },
        {"Masz pozdrowienia od Eli",        "Co lozka w burdelu scieli",    "",                             "" },
        {"Masz pozdrowienia od Asi",        "Co swiatlo w burdelu gasi",    "",                             "" },
        {"Niestety oni nie sa juz razem",   "Butla z gazem",                "",                             "" },
        {"Dlaczego maly muzulmanin",        "jest niegrzeczny w szkole?",   "Chce do kozy",                 "" },
        {"Czym sie rozni blondynka",        "od kabla?",                    "Jedno ciagnie napiecie",       "a drugie na kolanie"},
        {"Czym się rozni elektryk",         "od sapera?",                   "elektryk przed smiercia",      "jeszcze zatanczy"},
        {"Jak nazywa sie patronka",         "elektrykow?",                  "Ewa",                          "bo pierwsza ciagla druta"},
        {"Czego nigdy nie robi",            "prawdziwy elektryk?",          "Nie lapie dziewczyny za",      "dwa cycki na raz"}
    };

    // Select a joke structure from the table
    const JokeLines* selected = &entries[seed % 9];

    jokes[0] = (char*)selected->line0;
    jokes[1] = (char*)selected->line1;
    jokes[2] = (char*)selected->line2;
    jokes[3] = (char*)selected->line3;
}

/**
 * Main entry point for the joke system. Determines which type of 
 * joke to display based on a weighted probability determined by the seed.
 *
 * @brief Retrieve a randomized joke for the system.
 * @param jokes Array of 4 character pointers (strings) of size 32 to hold the output.
 * @param seed  The randomization seed.
 * @author Aleksander Dziągwa
 */
void GetJoke(char** jokes, uint32_t seed) {

    // Just some funny numbers
    if (seed % 2137 < 69) {
        funny2(jokes, seed);
    } else {
        funny1(jokes, seed);
    }

}
