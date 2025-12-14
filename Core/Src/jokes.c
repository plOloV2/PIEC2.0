#include "data_structs.h"
#include <stdint.h>

static char* EMPTY = "";

void funny1(char** jokes, uint32_t seed){

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

    jokes[0] = (char*)names[seed % 22];
    jokes[1] = (char*)actions[seed % 26];
    
    jokes[2] = EMPTY;
    jokes[3] = EMPTY;
}

void funny2(char** jokes, uint32_t seed){

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

    const JokeLines* selected = &entries[seed % 9];

    jokes[0] = (char*)selected->line0;
    jokes[1] = (char*)selected->line1;
    jokes[2] = (char*)selected->line2;
    jokes[3] = (char*)selected->line3;
}

void GetJoke(char** jokes, uint32_t seed){

    if(seed % 2137 < 69){

        funny2(jokes, seed);

    } else{

        funny1(jokes, seed);

    }
    
}
