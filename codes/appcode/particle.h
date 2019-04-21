#pragma once
#include "utility.h"
#include "color.h"
#include "vector.h"

typedef struct {
	Pos bias;
	Pos momantum;
	int existTime;
	Color color;
} Particle;

typedef struct {
	Vector parts;
	Pos center;
	int life;
	double maxSpeed;
	double gravity;
	Color (*color_generator)(Particle*, int time);
	int startTime;
} ParticleGroup;

ParticleGroup create_particle_group(Pos center, int life, int number, double maxSpeed, double gravity, Color color_generator(Particle*, int time));

void show_particles(ParticleGroup* part);

