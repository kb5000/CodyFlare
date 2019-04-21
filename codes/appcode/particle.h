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

///name: create_particle_group
///func: create a struct contains random particles
///para: center expects the center of the particles, life expects how long the particle will exist, 
///      number expects the num of particles, maxSpeed expects the max Speed the particle will have,
///      gravity exptects the y accceleration, color_generator expects the function to give every particle color
///visb: public
ParticleGroup* create_particle_group(Pos center, int life, int number, double maxSpeed, double gravity, Color color_generator(Particle*, int time));

void ball_particle(ParticleGroup* parts, double maxSpeed);

void uniform_particle(ParticleGroup* parts, Pos size, Pos minSpeed, Pos maxSpeed);

///name: show_particles
///func: add particle anime to timer
///para: part expects a ParticleGroup malloced
///visb: public
void show_particles(ParticleGroup* part);

