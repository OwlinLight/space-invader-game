/* author: Sitao Tong */
/* test wether is was hit */
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"

#include "invaders.h"
#include "framerate.h"
#include "linkedlist.h"
#include "code.h"

/*** run with 0.sa ****/

/* cal new X */
void newX(Alien *alien)
{
	alien->x = alien->x + alien->vx * alien->sim->dt;
}

/* cal new Y (Case: strike the base) */
void newY(Alien *alien)
{
	double y_;

	y_ = alien->y + alien->vy * alien->sim->dt;

	if(y_ <= 0)
	{
	    y_ = 0;
		if(TEXT) printf("\nAlien 0x%8X touches down at X=%9.5lf!\n", alien->code, alien->x);
	}
	alien->y = y_;
}

Alien *allocAlien(unsigned int code, double x, double y, double vx, double vy, Sim *sim){
    Alien *alien = (Alien *)malloc(sizeof(Alien));
    alien->code = code;
    alien->x = x;
    alien->y = y;
    alien->vx = vx;
    alien->vy = vy;
    alien->color = color_from_code(code);
    alien->type = type_from_code(code);
    alien->points = points_from_code(code);
    alien->sim = sim;
    return alien;
}

Sim *allocSim(double elapsed, void* aliens, double xBase, int score, double dt){
    Sim *sim = (Sim *)malloc(sizeof(Sim));
    sim->elapsed = elapsed;
    sim->aliens = aliens;
    sim->xBase = xBase;
    sim->score = score;
    sim->dt = dt;
    return sim;
}

void printIt(void * pointer){
    Alien *p_alien = (Alien *)pointer;
    printf("%-10s T C Pts (%9s, %8s) (%9s, %9s) ET=%9.5lf\n",
	    "Code", "__X_____", "__Y_____", "__VX____", "__VY____", 0.1);
	printf("0x%08X %d %d %3d (%9.5lf, %8.5lf) (%9.5lf, %9.5lf)\n",
		p_alien->code, p_alien->type, p_alien->color, p_alien->points, p_alien->x, p_alien->y, p_alien->vx, p_alien->vy);
}

int compare(void *x, void *y){
    int a = *(int *)x;
    int b = *(int *)y;
    return a < b;
}

int firstLetter(void *x, void *y){
    int a = *(char *)x;
    int b = *(char *)y;
    return a < b;
}

void update(void *pointer){
    Alien *alien = (Alien*)pointer;
    newX(alien);
    newY(alien);
}

int hit(void *pointer, void *helper){
    Alien *alien = (Alien*)pointer;

    return (int)(alien->x) == (int)(alien->sim->xBase);
}

void cal_score(void *pointer){
    Alien* alien = pointer;
    alien->sim->score += alien->points;
    printf("bolt hits alien at (%.5lf, % .5lf), scores %d points\n", alien->x, alien->y, alien->points);
}

void delete_alien(void *pointer){
    /* automatically initialize as 0 */
    static int count = 0;
    Alien *p_alien = pointer;
    free(p_alien);
    /* reset the pointer, avoid leak */
    p_alien = NULL;
    if(TEXT) printf("free_alien: %d freed\n", ++count);
}

/* call back: calculate the alien score and delete the alien */
void beat_alien(void *pointer){
    cal_score(pointer);
    delete_alien(pointer);
}

/******** helper functions *********/
/* judge wheter you cross the bound */
int crosses_second_boundary(double elapsed, double dt)
{
	int cur, prev, rval;

	cur = elapsed; /* implicit conversion truncates */
	prev = elapsed - dt; /* same conversion */

	/* truncation does what I need for positive elapsed time,
	 * but small negatives truncate to zero, not -1 */
	/* SPECIAL CASE: elapsed == 0.0 */
	rval = ( (elapsed == 0.0) || (cur != prev) );
if(DEBUG)printf("crosses_second_boundary: Cur = %d, Prev = %d, ET = %.5lf: returning %d\n",
		cur, prev, elapsed, rval);

	return rval;
}


void run_one(Sim *sim)
{
    int i = 4;
    sim->elapsed = 0.0;
    sim->dt = DELTA_T;
    
    /* BEYOND: needless code parameter */
    while(i--){
            /* the clock is running */
        sim->elapsed += sim->dt;
            /* move */
        iterate(sim->aliens, update);
        iterate(sim->aliens, printIt);
        deleteSome(&(sim->aliens), hit, NULL, beat_alien, 1);
        printf("elapsed: %lf\n", sim->elapsed);
    }
}




void read_loop()
{
    unsigned int code = 0;
    double y = 0.0, x = 0.0, vy = 0.0, vx = 0.0;
    double elapsed = 0.0, xBase = 0.0, dt = DELTA_T;
    Alien* aliens = NULL;
    int score = 0;
    int items;
    int rval;
    Sim* sim;
    void *head = NULL;
    Alien *alien = NULL;

    sim = allocSim(elapsed, NULL, xBase, score, dt);
    while( 5 == (items = scanf("%x %lf %lf %lf %lf",
        &(code), &(x), &(y), &(vx), &(vy))))
    {
        /* Alien alien -- only once */
        alien = allocAlien(code, x, y, vx, vy, sim);
        insert(&head, alien, compare, 1);
    }
    sim->aliens = head;
    
    run_one(sim);

    printf("\n");
}


int main(){
    read_loop();
    return 0;
}