/* author: Sitao Tong*/

#ifndef FUNCTION_H
#define FUNCTION_H

#include "structs.h"
#include "invaders.h"

#include "motion.h"
#include "code.h"


/* iteration */
/*print the alien info*/
void printIt(void * pointer);
/* draw every one aliens */
void draw_one_alien(void *pointer);

/* compare */
/* compare the y value */
int compare_y(void *x, void *y);

/* criterial */
/* delete the hitted aliens */
int hit(void *pointer, void *helper);
int all(void *pointer, void *helper);

/* helper */
int crosses_second_boundary(double elapsed, double dt);

#endif