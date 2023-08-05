/* author: Sitao Tong*/

#include "global.h"
#include "structs.h"
#include "memory.h"
#include "function.h"
#include "code.h"

int main(){

    Alien temp={
        0x32F3F1F,
        0.0,
        0.0,
        1.1,
        1.1,
    };

    Alien *alien = newAlien(temp);
    alien->code = 0x223331;
    printIt(alien);
    printIt(&temp);
    return 0;
}