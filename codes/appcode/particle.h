#pragma once
#include "utility.h"
#include "color.h"
#include "vector.h"

typedef struct {
	Pos bias;
	Pos momentum;
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
	int isCycle;
} ParticleGroup;

///name: create_particle_group
///func: create a struct contains random particles
///para: center expects the center of the particles, life expects how long the particle will exist, 
///      number expects the num of particles, maxSpeed expects the max Speed the particle will have,
///      gravity exptects the y accceleration, color_generator expects the function to give every particle color
///visb: public
ParticleGroup* create_particle_group(Pos center, int life, int number, double maxSpeed, double gravity, Color color_generator(Particle*, int time), int isCycle);

///name: ball_particle
///func: make particles like a ball
///para: parts expects a ParticleGroup, maxSpeed expects the max initial speed
///visb: public
void ball_particle(ParticleGroup* parts, double maxSpeed);

///name: uniform_particle
///func: make particles move randomly in a box and the lower left corner is the value of center 
///para: parts expects a ParticleGroup, size expects the w and h of the box, minSpeed and maxSpeed expects the speed limit
///visb: public
void uniform_particle(ParticleGroup* parts, Pos size, Pos minSpeed, Pos maxSpeed);

///name: show_particles
///func: add particle anime to timer
///para: part expects a ParticleGroup malloced
///visb: public
void show_particles(ParticleGroup* part);

///name: disable_particles
///func: disable a particle group
///para: part expects a particle group to disable
///visb: public
void disable_particles(ParticleGroup* part);

///name: destroy_particles
///func: destroy a particle group and release memory
///para: part expects a particle group to destroy
///visb: public
void destroy_particles(ParticleGroup* pg);

