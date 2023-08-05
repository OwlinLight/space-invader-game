/* Copyright 2022 Neil Kirby */
/* modify: Sitao Tong*/

#include "main.h"

/* number of parameter */
#define P_NUM 5

#define XBASE 0.0

/* main function start from here */
int main()
{
	double start, runtime;
	start = now();
	if(init())
	{
        /* divide read_loop */
	    run_sim();
	    teardown();
	}
	runtime = now()- start;
	printf("Total run time is %.9lf seconds.\n", runtime);
	return(0);
}

/* run the simulation */
void run_sim()
{
    Sim *sim = init_sim();
    read_aliens(sim);
    run_one(sim); 
    /* free all the aliens*/
    free_aliens(sim);
    /* free sim struct */
    deleteSim(sim);
    sim = NULL;
}

/* init sim */
Sim *init_sim(){
    Sim sim;
    /* for elapsed time usually start with 0.0, no need to define */
    sim.elapsed = 0.0;
    sim.dt = DELTA_T;
    sim.xBase = XBASE;
    /* for score usually start with 0, no need to define */
    sim.score = 0;
    return newSim(sim);
}

/* read all the required aliens */
void read_aliens(Sim *sim){
    int items;
    /* sample alien */
    Alien alien;
    /* header of the linked list */
    void *aliens = NULL;
    /* pointer to alien */
    Alien *p_alien = NULL;
    while(P_NUM == (items = scanf("%x %lf %lf %lf %lf",
        &alien.code, &alien.x, &alien.y, &alien.vx, &alien.vy)))
    {
        p_alien = new_complete_alien(sim, alien);
        /* check if correctly allocated, or release the space */
        if(!insert(&aliens, p_alien, compare_y, TEXT)) delete_alien(p_alien);
        else if(TEXT) printf("add_new_alien: inserted code %X\n", p_alien->code);
    }
    if(TEXT) printf("Input terminated: scanf returned %d\n", items);
    sim->aliens = aliens;
}

/* parse the info from code and assign sim */
Alien* new_complete_alien(Sim *sim, Alien alien_sample){
    Alien *alien = newAlien(alien_sample);
    alien->color = color_from_code(alien->code);
    alien->type = type_from_code(alien->code);
    alien->points = points_from_code(alien->code);
    alien->sim = sim;
    return alien;
}

/* run one round of game */
void run_one(Sim *sim)
{   
    /* BEYOND: needless code parameter */
    while(!game_over(sim)){
        /* output the graphic */
        normal_output(sim);
        /* the clock is running */
        sim->elapsed += sim->dt;
        /* update the aliens' position */
        update_position(sim);
        /* hit the wall / escape */
        escape_alien(sim);
        /* bolt fight back and deal with hit event */
        fight_back(sim);
    }
    final_output(sim);
}

int init()
{
    /* deal with the mode */
	return (TEXT || ( GRAPHICS && sa_initialize()));
}

/* warp another layer to deal with graphic */
void teardown()
{
	if(GRAPHICS)sa_teardown();
}

/* free all the aliens at last */
void free_aliens(Sim* sim){
    int count;
    if(TEXT) printf("Clearing the attacking list... \n");
    count = deleteSome(&(sim->aliens), all, NULL, delete_alien, TEXT);
    if(TEXT) printf("    ... %d cleared \n", count);
}