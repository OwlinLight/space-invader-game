/* Copyright 2022 Neil Kirby */
/* modified: Sitao Tong */

#include <stdio.h>

#include "structs.h"
#include "function.h"

#include "debug.h"
#include "framerate.h"
#include "linkedlist.h"

#include "motion.h"
#include "code.h"

/* SP22 Lab 2 code.  Not for disclosure without permission */

void draw_alien(void *header);
void draw_base_and_bolt(Sim *sim);
void draw_fun_stuff(Sim* sim);
void final_draw( Sim* sim);
void final_output(Sim* sim);
void graphic_output( Sim* sim);
void normal_output(Sim* sim);
void text_header(double dt);
void text_output (Sim* sim);
void end_output(Sim *sim);
