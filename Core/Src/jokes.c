#include "data_structs.h"
#include <stdint.h>


void funny1(char** jokes, uint32_t seed){

    switch(seed % 22){
        case(0):
        jokes[0] = "Michal Dowgiallo\0";
        break;

        case(1):
        jokes[0] = "Zuber\0";
        break;

        case(2):
        jokes[0] = "Sobczak\0";
        break;
        
        case(3):
        jokes[0]= "Olek Dziagwa\0";
        break;

        case(4):
        jokes[0] = "Przemo Kałuza";
        break;

        case(5):
        jokes[0] = "Domino\0";
        break;

        case(6):
        jokes[0] = "Igor Zielonka\0";
        break;

        case(7):
        jokes[0] = "Jakub Koman\0";
        break;

        case(8):
        jokes[0] = "Kuba Ruchala\0";
        break;

        case(9):
        jokes[0] = "Wadas\0";
        break;

        case(10):
        jokes[0] = "Maciej Sikora\0";
        break;

        case(11):
        jokes[0] = "Mateusz Grozdanovic\0";
        break;

        case(12):
        jokes[0] = "Wiktor Kurwicki\0";
        break;

        case(13):
        jokes[0] = "Patryk Koltun\0";
        break;

        case(14):
        jokes[0] = "Nina\0";
        break;

        case(15):
        jokes[0] = "Nazarii\0";
        break;

        case(16):
        jokes[0] = "Mikolaj Stojowski\0";
        break;

        case(17):
        jokes[0] = "Twoja babka\0";
        break;

        case(18):
        jokes[0] = "Dział Chassis\0";
        break;

        case(19):
        jokes[0] = "Baba z portierni\0";
        break;

        case(20):
        jokes[0] = "Marketing\0";
        break;

        case(21):
        jokes[0] = "Suspension\0";
        break;
    }

    
    switch(seed % 26){
        case(0):
        jokes[1] = "laminuje\0";
        break;

        case(1):
        jokes[1] = "zamyka worek\0";
        break;

        case(2):
        jokes[1] = "zamyka morde\0";
        break;
        
        case(3):
        jokes[1] = "klei takitejpa\0";
        break;

        case(4):
        jokes[1] = "udaje że pracuje\0";
        break;

        case(5):
        jokes[1] = "odsysa worek\0";
        break;

        case(6):
        jokes[1] = "szlifuje rdzen\0";
        break;

        case(7):
        jokes[1] = "stawia browary\0";
        break;

        case(8):
        jokes[1] = "tnie worek\0";
        break;

        case(9):
        jokes[1] = "daje fula\0";
        break;

        case(10):
        jokes[1] = "jest głodny/a\0";
        break;

        case(11):
        jokes[1] = "jest zly/a\0";
        break;

        case(12):
        jokes[1] = "chce do domu\0";
        break;

        case(13):
        jokes[1] = "tnie wykroje\0";
        break;

        case(14):
        jokes[1] = "masuje uszczelke\0";
        break;

        case(15):
        jokes[1] = "szlifuje formy\0";
        break;

        case(16):
        jokes[1] = "wchodzi do pieca\0";
        break;

        case(17):
        jokes[1] = "idzie do pirmu\0";
        break;

        case(18):
        jokes[1] = "gwintuje inserty\0";
        break;

        case(19):
        jokes[1] = "zlamal endplate\0";
        break;

        case(20):
        jokes[1] = "wyrwal wklejke\0";
        break;

        case(21):
        jokes[1] = "depnal na ub\0";
        break;

        case(22):
        jokes[1] = "udaje greka\0";
        break;

        case(23):
        jokes[1] = "ma wszy\0";
        break;

        case(24):
        jokes[1] = "nic nie rozumie\0";
        break;

        case(25):
        jokes[1] = "jest szalony\0";
        break;

    }

    jokes[2] = "\0";
    jokes[3] = "\0";


}

void funny2(char** jokes, uint32_t seed){

    switch(seed % 5){
        case 0:
            jokes[0] = "Na wszelki wypadek to\0";
            jokes[1] = "ksiadz chuja w gaciach nosi\0";
            jokes[2] = "\0";
            jokes[3] = "\0";
            break;
    
        case 1:
            jokes[0] = "Dlaczego maly muzulmanin\0";
            jokes[1] = "jest niegrzeczny w szkole?\0";
            jokes[2] = "\0";
            jokes[3] = "Chce do kozy\0";
            break;
    
        case 2:
            jokes[0] = "Masz pozdrowienia od Eli\0";
            jokes[1] = "\0";
            jokes[2] = "\0";
            jokes[3] = "Co lozka w burdelu scieli\0";
            break;
    
        case 3:
            jokes[0] = "Szkoda mi tej Asi\0";
            jokes[1] = "\0";
            jokes[2] = "\0";
            jokes[3] = "Co swiatlo w burdelu gasi\0";
            break;
    
        case 4:
            jokes[0] = "Niestety oni nie sa juz razem\0";
            jokes[1] = "\0";
            jokes[2] = "\0";
            jokes[3] = "Butla z gazem\0";
            break;
    }

}
