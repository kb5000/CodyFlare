#include "particle.h"
#include "graphics.h"
#include "random.h"
#include "timer.h"
#include "extgraph.h"
#include <math.h>

ParticleGroup* create_particle_group(Pos center, int life, int number, double maxSpeed, double gravity, Color color_generator(Particle*, int time), int isCycle) {
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
		isCycle,
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
		pt->existTime = 0;
		pt->bias = new_pos(RandomReal(start.x, start.x + size.x), RandomReal(start.y, start.y + size.y));
		pt->momentum = new_pos(RandomReal(minSpeed.x, maxSpeed.x), RandomReal(minSpeed.y, maxSpeed.y));
	}

}

void show_particles_tick(void* para) {
	ParticleGroup* part = (ParticleGroup*)para;
	if (!part) return;
	SetPenSize(3);
	for (unsigned i = 0; i < part->parts.len(&part->parts); i++) {
		Particle* p = part->parts.at(&part->parts, i);
		if (!p || (++p->existTime >= part->life && part->life >= 0) || (part->life == -5)) continue;
		p->color = part->color_generator(p, get_tick() - part->startTime);
		set_color(p->color);
		MovePen(part->center.x + p->bias.x, part->center.y + p->bias.y);
		DrawLine(0, 0);
		p->bias = add_pos(p->bias, p->momentum);
		if (fabs(p->momentum.y) < part->maxSpeed)
			p->momentum.y += part->gravity;
		if (part->isCycle) {
			if (part->center.x + p->bias.x < -0.01) p->bias.x = 10 - part->center.x;
			else if (part->center.x + p->bias.x > 10.01) p->bias.x = -part->center.x;
			if (part->center.y + p->bias.y < -0.01) p->bias.y = 7 - part->center.y;
			else if (part->center.y + p->bias.y > 7.01) p->bias.y = -part->center.y;
		}
	}
	SetPenSize(1);
}


void show_particles(ParticleGroup* part) {
	part->startTime = get_tick();
	add_func_to_timer(show_particles_tick, part, 1, Unique_ID("Part"), part->life);
}

void disable_particles(ParticleGroup* part) {
	if (part) part->life = -5;
}

void destroy_particles(ParticleGroup* pg) {
	if (pg) {
		calls(pg->parts, destroy);
		free(pg);
	}
}

