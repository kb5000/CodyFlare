#include "particle_test.h"
#include "particle.h"
#include "graphics.h"
#include "timer.h"
#include <stdlib.h>
#include "random.h"

Color cgener(Particle p, int time) {
	return color_by_hsl(20, 40, 20);
}

void test_of_particle() {
	InitGraphics();
	init_global_timer();
	ParticleGroup* pts = (ParticleGroup*)malloc(sizeof(ParticleGroup));
	*pts = create_particle_group(new_pos(5, 3.5), 1400, 6000, 0.01, -0.0001, cgener);
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	show_particles(pts);
	start_global_timer();
}