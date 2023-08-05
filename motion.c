/* Copyright 2022 Neil Kirby.  Not for disclosure */
/* modified: Sitao Tong*/

#include "motion.h"

#define XBASE 0.0

#define SAUCER 3
#define BOMB 4

#define DROP 3

/**** position related ****/

/* position change */
void update_position(Sim *sim){
    /* move */
    iterate(sim->aliens, update);
}

/* alien not in the air */
int not_in_the_air(void *pointer, void*helper){
    Alien *alien = pointer;
    return alien->y <= XBASE;
}

/* event after alien touch the wall */
void touch_the_wall(Alien *alien){
	if(alien->type != SAUCER && is_strike_the_wall(alien->x, alien->vx)){
		alien->vx = -alien->vx;
		/* for normal alien, drop it 3 */
		alien->y -= DROP;
		if(TEXT) printf("\nAlien 0x%08X drops to (%9.5lf, %8.5lf) changes VX to %+9.5lf at ET %.5lf\n ", alien->code, alien->x, alien->y, alien->vx, alien->sim->elapsed);
	}
}

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

	if(y_ <= XBASE)
	{
	    y_ = XBASE;
		if(TEXT) printf("\nAlien 0x%8X touches down at X=%9.5lf!\n", alien->code, alien->x);
	}
	alien->y = y_;
}

/* below here is the only user of these constants */
#define RIGHT_WALL 39.0
#define LEFT_WALL (-39.0)

int is_strike_the_wall(double X, double VX){
	int rval = (X >= RIGHT_WALL && VX > 0.0)  || (X <= LEFT_WALL && VX < 0.0);
	return rval;
}

/**** escape related ****/

/* delete the escaped alien */
int escape_alien(Sim *sim){
	return deleteSome(&sim->aliens, escape, NULL, delete_alien, TEXT);
}

/* call back (action) */
int escape(void *pointer, void *helper){
    Alien *alien = pointer;
	int rval;
	if(rval = (alien->type == SAUCER && is_strike_the_wall(alien->x, alien->vx))){
		if(TEXT) printf("Flying saucer worth %d points escapes at ET = %.5lf!\n", alien->points, alien->sim->elapsed);
		if(GRAPHICS) sa_status("Flying saucer escape!\n");
	}
    return rval;
}

/**** attack related ****/

/* fight back to the aliens and eliminate them */
void fight_back(Sim *sim){
    if(shot(sim)){
        /* fight back */
        if(hit_alien(sim)){
            /* attack_aliens */
            attack_alien(sim);
        }
    }
}

/*  wether base fire */
int shot(Sim *sim){
    return crosses_second_boundary(sim->elapsed, sim->dt);
}

/* wether hits aliens */ 
int hit_alien(Sim *sim){
    return any(sim->aliens, hit, NULL);
}

/* attack aliens hits in the list */
void attack_alien(Sim *sim){
    deleteSome(&(sim->aliens), hit, NULL, beat_alien, TEXT);
}

/* call back: calculate the alien score and delete the alien */
void beat_alien(void *pointer){
    cal_score(pointer);
    delete_alien(pointer);
}

/* call back: calculate the score of the alienhits */
void cal_score(void *pointer){
    Alien* alien = pointer;
    alien->sim->score += alien->points;
    if(TEXT) printf("bolt hits alien at (%.5lf, % .5lf), scores %d points\n", alien->x, alien->y, alien->points);
    if(GRAPHICS)sa_status("bolt hits alien");
}

/**** game ending related ****/

/* the requirement of end a game */
int game_over(Sim *sim){
	return game_victory(sim) || game_defeated(sim);
}

/* no aliens, you win */
int game_victory(Sim *sim){
	/* when there is no alien, you win */
	return sim->aliens == NULL;
}

/* touch the bound, you lose */
int game_defeated(Sim *sim){
	/* when there is any alien toucht the bottom line, you lose */
	return any(sim->aliens, not_in_the_air, NULL);
}


