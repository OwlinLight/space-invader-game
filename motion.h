/* Copyright 2022 Neil Kirby */
/* modified: Sitao Tong*/
/* SP22 Lab 2 code.  Not for disclosure without permission */


#include <stdio.h>

#include "function.h"
#include "memory.h"

#include "debug.h"
#include "framerate.h"
#include "linkedlist.h"

void update_position(Sim *sim);

/* update the position of the aliens */
void update(void *pointer);
void newX(Alien *alien);
void newY(Alien *alien);
int all_in_air(void* head);
int not_in_the_air(void *pointer, void*helper);
void touch_the_wall(Alien *alien);
int is_strike_the_wall(double X, double VX);

void fight_back(Sim *sim);
void attack_alien(Sim *sim);
void beat_alien(void *pointer);
void cal_score(void *pointer);
int hit_alien(Sim *sim);
int shot(Sim *sim);

int game_over(Sim *sim);
int game_victory(Sim *sim);
int game_defeated(Sim *sim);

int escape(void *pointer, void *helper);
int escape_alien(Sim *sim);
