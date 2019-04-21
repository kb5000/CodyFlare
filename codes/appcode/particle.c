#include "particle.h"
#include "graphics.h"
#include "random.h"
#include "timer.h"
#include "extgraph.h"

ParticleGroup create_particle_group(Pos center, int life, int number, double maxSpeed, double gravity, Color color_generator(Particle*, int time)) {
	Particle p = {
		new_pos(0, 0),
		new_pos(0, 0),
		0,
		color_by_name("Black"),
	};
	ParticleGroup res = {
		new_vector(sizeof(Particle), number, &p),
		center,
		life,
		maxSpeed,
		gravity,
		color_generator,
		0,
	};
	for (unsigned i = 0; i < res.parts.len(&res.parts); i++) {
		Particle* pt = res.parts.at(&res.parts, i);
		pt->momantum = polar_to_rect(new_pos(RandomReal(-maxSpeed, maxSpeed), RandomReal(-PI, PI)));
	}
	return res;
}

void show_particles_tick(void* para) {
	ParticleGroup* part = (ParticleGroup*)para;
	for (unsigned i = 0; i < part->parts.len(&part->parts); i++) {
		Particle* p = part->parts.at(&part->parts, i);
		if (p->existTime > part->life) continue;
		p->color = part->color_generator(p, get_tick() - part->startTime);
		set_color(p->color);
		SetPenSize(2);
		MovePen(part->center.x + p->bias.x, part->center.y + p->bias.y);
		DrawLine(0.01, 0.01);
		p->bias = add_pos(p->bias, p->momantum);
		p->momantum.y += part->gravity;
	}
}


void show_particles(ParticleGroup* part) {
	part->startTime = get_tick();
	add_func_to_timer(show_particles_tick, part, 1, Unique_ID("Part"), part->life);
}


