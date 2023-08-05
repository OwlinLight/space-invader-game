/* author: Sitao Tong*/

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "code.h"

#include "debug.h"

Alien *allocAlien();
void delete_alien(void *pointer);

Alien *newAlien(Alien src);
Sim *allocSim();
Sim *newSim(Sim src);
void deleteSim(Sim* sim);