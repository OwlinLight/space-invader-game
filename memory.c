/* author: Sitao Tong*/

#include "memory.h"

/***** alien related *****/

/* create an alien from the existing source */
Alien *newAlien(Alien src){
    Alien *alien = allocAlien();
    *alien = src;
    return alien;
}

/* allocate a new alien */
Alien *allocAlien(){
    /* count is intialize to 1 */
    static int count;
    Alien *alien = malloc(sizeof(Alien));
    if(alien != NULL){
        if(TEXT) printf("allocate_alien %d allocated\n", ++count);
    } else{
        if(TEXT) printf("ERROR:allocate_alien: failed to allocate\n");
    }
    return alien;
}

/* delete alien and its space */
void delete_alien(void *pointer){
    /* automatically initialize as 0 */
    static int count = 0;
    Alien *p_alien = pointer;
    free(p_alien);
    /* reset the pointer, avoid leak */
    p_alien = NULL;
    if(TEXT) printf("free_alien: %d freed\n", ++count);
}

/***** sim related *****/

/* create a sim from the existing source */
Sim *newSim(Sim src){
    Sim *sim = allocSim();
    *sim = src;
    return sim;
}

/* free a sim */
void deleteSim(Sim* sim){
    free(sim);
}

/* allocate a new simulation*/
Sim *allocSim(){
    Sim *sim = malloc(sizeof(Sim));
    return sim;
}