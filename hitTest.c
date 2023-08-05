/* author: Sitao Tong */
#include <stdio.h>
#include <stdlib.h>

#include "code.h"
#include "invaders.h"
#include "framerate.h"
#include "linkedlist.h"


typedef struct alien{
    unsigned int code;
    double x;
    double y;
    double vx;
    double vy;
    int color;
    int type;
    int points;
} Alien;

Alien *allocAlien(unsigned int code, double x, double y, double vx, double vy){
    Alien *alien = (Alien *)malloc(sizeof(Alien));
    alien->code = code;
    alien->x = x;
    alien->y = y;
    alien->vx = vx;
    alien->vy = vy;
    alien->color = color_from_code(code);
    alien->type = type_from_code(code);
    alien->points = points_from_code(code);
    return alien;
}

void printIt(void * pointer){
    Alien *p_alien = (Alien *)pointer;
    printf("%-10s T C Pts (%9s, %8s) (%9s, %9s) ET=%9.5lf\n",
	    "Code", "__X_____", "__Y_____", "__VX____", "__VY____", 0.1);
	printf("0x%08X %d %d %3d (%9.5lf, %8.5lf) (%9.5lf, %9.5lf)\n",
		p_alien->code, p_alien->type, p_alien->color, p_alien->points, p_alien->x, p_alien->y, p_alien->vx, p_alien->vy);
}

int compare_y(void *x, void *y){
    int a = *(int *)x;
    int b = *(int *)y;
    return a < b;
}

int firstLetter(void *x, void *y){
    int a = *(char *)x;
    int b = *(char *)y;
    return a < b;
}
void init_sim()
{
    unsigned int code = 0;
    double y = 0.0, x = 0.0, vy = 0.0, vx = 0.0;

    int items;
    int rval;
    Alien *head = NULL;
    Alien *alien = NULL;
    while( 5 == (items = scanf("%x %lf %lf %lf %lf",
        &(code), &(x), &(y), &(vx), &(vy))))
    {
        /* Alien alien -- only once */
        alien = allocAlien(code, x, y, vx, vy);
        insert(&head, alien, compare_y, 1);
    }
    
    iterate(head, printIt);

    printf("\n");
}


int main(){
    init_sim();
    return 0;
}