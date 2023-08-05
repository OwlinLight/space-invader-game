/* author: Sitao Tong*/

#include "function.h"


/* callback(action): print the alien info */
void printIt(void * pointer){
    Alien *p_alien = pointer;
	printf("0x%08X %d %d %3d (%9.5lf, %8.5lf) (%9.5lf, %9.5lf)\n",
		p_alien->code, p_alien->type, p_alien->color, p_alien->points, p_alien->x, p_alien->y, p_alien->vx, p_alien->vy);
}


/* callback(action): draw the alien */
void draw_one_alien(void *pointer){
    Alien *p_alien = pointer;
    sa_alien(p_alien->type, p_alien->color, p_alien->x, p_alien->y);
}

/* callback(action): update the alien position */
void update(void *pointer){
    Alien *alien = pointer;
    touch_the_wall(alien);
    newX(alien);
    newY(alien);
}

/* callback(criteria): select all in the list */
int all(void *pointer, void *helper){
    return 1;
}

/* callback(compare): compare with the large */
int compare_y(void *x, void *y){
    Alien* a = x;
    Alien* b = y;
    return a->y > b->y;
}

/* callback(criteria): select all in the list */
int hit(void *pointer, void *helper){
    Alien *alien = pointer;
    return (int)(alien->x) == (int)(alien->sim->xBase);
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