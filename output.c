
/* Copyright 2022 Neil Kirby.  Not for disclosure */
/* modified: Sitao Tong */

#include "output.h"

#define LATENCY 4

/**** common to both modes ***/
void normal_output(Sim *sim)
{
	if(TEXT)
	{
		
		/* we are in text mode, is it time? Are we debugging? */
		/* TEACH: dt is convey as a parameter */
		/* NSTD: indention */
	    if( crosses_second_boundary(sim->elapsed, sim->dt) || DEBUG )
		/* output alien infomation */
		text_output(sim);
	}

	if(GRAPHICS) graphic_output(sim);
}

/* final output: text and ending */
void final_output(Sim* sim)
{

	if(TEXT){
		text_output(sim);
		end_output(sim);
	}
	if(GRAPHICS) final_draw(sim);
}

/************************************** text functions ********/

/* output the text_header */
void text_header(double dt)
{
	if(TEXT)printf("\nSTART SIMULATION (dt = %.5lf)\n", dt);	
}

/* output end by different sim status */
void end_output(Sim *sim){
	if(game_victory(sim)){
		printf("Victory! No attackers remain at ET = %.5lf\n", sim->elapsed);
		printf("Total score is %d points\n", sim->score);
	}else if(game_defeated(sim)){
		printf("Defeat! Aliens land at ET = %.5lf\n", sim->elapsed);
		printf("Total score is %d points\n", sim->score);
	}
}

/* output the required infomation about aliens as list */
void text_output (Sim* sim)
{
	printf("\n");
	if(sim->aliens){
		printf("%-10s T C Pts (%9s, %8s) (%9s, %9s) ET=%9.5lf\n",
			"Code", "__X_____", "__Y_____", "__VX____", "__VY____", sim->elapsed);
		iterate(sim->aliens, printIt);
	}
	printf("\n");
}


/************************* graphics functions ******/

/* output graphic elements */
void  graphic_output(Sim* sim)
{

	/* high level draw sequence */
	sa_clear();

	draw_fun_stuff(sim);

	/* noted the unit */
	sa_time( (int) (1e3 * sim->elapsed) ); /* sec -> milliseconds */
	sa_score(sim->score);
	sa_refresh();
	microsleep( (unsigned int) 1e6 * sim->dt); /* sec -> microsec */
}

/* draw the base/bolt/aliens */
void draw_fun_stuff(Sim *sim)
{
	draw_base_and_bolt(sim);
	draw_alien(sim->aliens);
}

/* draw base according to sim */
void draw_base_and_bolt(Sim *sim)
{
	sa_base(sim->xBase);
	if(crosses_second_boundary(sim->elapsed, sim->dt)) sa_bolt(sim->xBase);
}

/* draw alien according to the list */
void draw_alien(void *head)
{
	iterate(head, draw_one_alien);
}

/* final: delay 4 seconds, freeze game time, real time continue */
void  final_draw(Sim *sim)
{
	double real = sim->elapsed + LATENCY; /* onscreen for 4 seconds */

	/* TEACH: start new loop to counter the time*/
	while (real > sim->elapsed)
	{
	    graphic_output(sim);
	    real -= sim->dt;
	}
}


