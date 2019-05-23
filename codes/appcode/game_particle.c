#include "particle.h"
#include "timer.h"
#include "game_particle.h"
#include <stdlib.h>

static ParticleGroup* pg, * backPg;
//static int particleOn = 1;

Color part_color_render(Particle* part, int time) {
	return color_by_rgb(180, 76, 200);
}

//void long_paticle(void* unuseful) {
//	if (backPg) {
//		//calls(backPg->parts, destroy);
//		//free(backPg);
//	}
//	backPg = pg;
//	pg = create_particle_group(new_pos(0, 7), 200, 130, 0.05, -0.002, part_color_render, 0);
//	uniform_particle(pg, new_pos(10, 7), new_pos(-0.009, -0.04), new_pos(0, 0));
//	if (backPg) show_particles(backPg);
//	if (pg) show_particles(pg);
//}

void show_long_particle() {
	//add_func_to_timer(long_paticle, NULL, 200, 9565, -1);
	pg = create_particle_group(new_pos(0, 0), -1, 200, 0.1, -0.002, part_color_render, 1);
	uniform_particle(pg, new_pos(10, 7), new_pos(-0.009, -0.04), new_pos(0, 0));
	show_particles(pg);
}

void toggle_long_particle() {
	if (pg) {
		disable_particles(pg);
		calls(pg->parts, destroy);
		pg = NULL;
	}
	else show_long_particle();
}

void show_bonus_particle() {
	
}
