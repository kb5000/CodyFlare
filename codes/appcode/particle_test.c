#include "particle_test.h"
#include "particle.h"
#include "graphics.h"
#include "timer.h"
#include <stdlib.h>
#include "random.h"

Color cgener(Particle* p, int time) {
	return color_by_hsl(80, 180, 70);
}

Color cgenerb(Particle* p, int time) {
	return color_by_hsl(280, 180, 20);
}

void test_of_particle() {
	InitGraphics();
	init_global_timer();
	ParticleGroup* pts = create_particle_group(new_pos(5, 3.5), 1400, 3000, 0.1, -0.00015, cgener);
	ball_particle(pts, 0.05);
	ParticleGroup* ptb = create_particle_group(new_pos(0, 0), -1, 3000, 0.05, -0.0002, cgenerb);
	uniform_particle(ptb, new_pos(20, 50), new_pos(-0.009, -0.04), new_pos(0, 0));
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	show_particles(pts);
	show_particles(ptb);
	start_global_timer();
}