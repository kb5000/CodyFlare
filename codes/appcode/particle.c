#include "particle.h"
#include "graphics.h"
#include "random.h"
#include "timer.h"
#include "extgraph.h"
#include <math.h>

ParticleGroup* create_particle_group(Pos center, int life, int number, double maxSpeed, double gravity, Color color_generator(Particle*, int time)) {
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
	ParticleGroup* pars = (ParticleGroup*)malloc(sizeof(ParticleGroup));
	*pars = res;
	return pars;
}

void ball_particle(ParticleGroup* parts, double maxSpeed) {
	for (unsigned i = 0; i < parts->parts.len(&parts->parts); i++) {
		Particle* pt = parts->parts.at(&parts->parts, i);
		pt->momentum = polar_to_rect(new_pos(RandomReal(0, maxSpeed), RandomReal(-PI, PI)));
	}
}

void uniform_particle(ParticleGroup* parts, Pos size, Pos minSpeed, Pos maxSpeed) {
	for (unsigned i = 0; i < parts->parts.len(&parts->parts); i++) {
		Particle* pt = parts->parts.at(&parts->parts, i);
		Pos start = parts->center;
		pt->bias = new_pos(RandomReal(start.x, start.x + size.x), RandomReal(start.y, start.y + size.y));
		pt->momentum = new_pos(RandomReal(minSpeed.x, maxSpeed.x), RandomReal(minSpeed.y, maxSpeed.y));
	}

}

void show_particles_tick(void* para) {
	ParticleGroup* part = (ParticleGroup*)para;
	SetPenSize(3);
	for (unsigned i = 0; i < part->parts.len(&part->parts); i++) {
		Particle* p = part->parts.at(&part->parts, i);
		if (++p->existTime == part->life) continue;
		p->color = part->color_generator(p, get_tick() - part->startTime);
		set_color(p->color);
		MovePen(part->center.x + p->bias.x, part->center.y + p->bias.y);
		DrawLine(0, 0);
		p->bias = add_pos(p->bias, p->momentum);
		if (fabs(p->momentum.y) < part->maxSpeed)
			p->momentum.y += part->gravity;
	}
	SetPenSize(1);
}


void show_particles(ParticleGroup* part) {
	part->startTime = get_tick();
	add_func_to_timer(show_particles_tick, part, 1, Unique_ID("Part"), part->life);
}


