#include "missile.h"
#include "timer.h"
#include <stdlib.h>
#include "vector.h"
#include "graphics.h"
#include "extgraph.h"
#include <math.h>
#include "random.h"

typedef struct {
	Pos position;
	Pos momentum;
	int valid;
} Missile;

typedef struct {
	Vector missile;
	Pos a, *b;
	int num;
	Color color;
	double speed;
	int life;
	double flexibility;
	int isDirectAttack;
	void (*explode_anime)(int id, Pos position, double size);
	double explodeSize;
	void (*hit_handler)(Pos position, int hitObjID);
	double explodeRadius;
	int hitID;
} Missiles;

void move_missile(Missile* missile, Pos b, double drawSpeed, double flexibility, int isDirectAttack) {
	Pos p;
	double theta = pos_arc(missile->momentum) - pos_arc(sub_pos(b, missile->position));
	if (theta < -PI / 2) theta = -PI - theta;
	if (theta > PI / 2) theta = PI - theta;
	p = sub_pos(rect_to_polar(missile->momentum), new_pos(0, flexibility * drawSpeed * theta));// fmin(theta, theta - PI)));
	missile->momentum = polar_to_rect(p);
	MovePen(missile->position.x, missile->position.y);
}

void update_missile(void* missiles) {
	Missiles* miss = (Missiles*)missiles;
	set_color(miss->color);

	//MovePen(miss->b->x, miss->b->y);
	//DrawLine(0.1, 0.1);
	int allInvalid = 1;
	for (unsigned i = 0; i < miss->missile.len(&miss->missile); i++) {
		Missile* m = (Missile*)miss->missile.at(&miss->missile, i);
		if (!m->valid) continue;
		allInvalid = 0;
		if (m->valid++ >= miss->life) {
			m->valid = 0;
			miss->explode_anime(Unique_ID("Missile"), m->position, miss->explodeSize);
			continue;
		}
		MovePen(m->position.x, m->position.y);
		double angle = pos_arc(m->momentum);
		DrawLine(0.1 * cos(angle), 0.1 * sin(angle));
		if (pos_length(sub_pos(*miss->b, m->position)) <= miss->explodeRadius) {
			m->valid = 0;
			miss->explode_anime(Unique_ID("Missile"), m->position, miss->explodeSize);
			if (miss->hit_handler) miss->hit_handler(m->position, miss->hitID);
		}
		m->position = add_pos(m->position, m->momentum);
		move_missile(m, *miss->b, miss->speed, miss->flexibility, miss->isDirectAttack);// sub_pos(miss->b, miss->a), 1);
	}
	if (allInvalid) miss->missile.destroy(&miss->missile);
}

void show_missile(Pos a, Pos* b, int num,
 Color color,
				  double speed, double maxAngle,
 double flexibility, int life,

				  int isDirectAttack, 
				  void explode_anime(int id, Pos position, double size),
 double explodeSize, 
				  void hit_handler(Pos position, int hitID), double explodeRadius, int hitID) {
	Missile m = {
		a,
		new_pos(0, 0),
		1,
	};
	Missiles miss = {
		new_vector(sizeof(Missile), num, &m),
		a, b,
		num,
		color,
		speed,
		life,
		flexibility,
		isDirectAttack,
		explode_anime,
		explodeSize,
		hit_handler,
		explodeRadius,
		hitID
	};
	for (int i = 0; i < num; i++) {
		Missile* ms = (Missile*)miss.missile.at(&miss.missile, i);
		double theta = pos_arc(sub_pos(*b, a));
		if (maxAngle > 0) {
			ms->momentum = polar_to_rect(new_pos(speed, RandomReal(theta - maxAngle, theta + maxAngle)));
		} else {
			ms->momentum = polar_to_rect(new_pos(speed, PI + RandomReal(theta - maxAngle, theta + maxAngle)));
		}
	}
	Missiles* mis = (Missiles*)malloc(sizeof(Missiles));
	*mis = miss;
	add_func_to_timer(update_missile, mis, 1, Unique_ID("Missiles"), life + 2);
}
