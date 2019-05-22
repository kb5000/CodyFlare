#include "particle.h"

static ParticleGroup* pg;

Color part_color_render(Particle* part, int time);

void long_paticle(void* unuseful) {
	if (pg) {
		calls(pg->parts, destroy);
		free(pg);
		pg = NULL;
	}
	//pg = create_particle_group(new_pos(0, 0), 1000, 1000, 0.05, -0.002, part_color_render);
}
