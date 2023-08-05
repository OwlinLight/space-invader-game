/* Copyright 2022 Neil Kirby */
/* modify: Sitao Tong*/

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "function.h"

#include "invaders.h"
#include "debug.h"
#include "framerate.h"
#include "linkedlist.h"

#include "output.h"
#include "code.h"
#include "memory.h"

#define XBASE 0.0

/* main run */
int main();
void run_sim();
Sim* init_sim();
void run_one(Sim *sim);

/* initial / tear */
int init();
void teardown();

/* read / free */
void read_aliens(Sim *sim);
void free_aliens(Sim* sim);
Alien* new_complete_alien(Sim *sim, Alien alien_sample);
