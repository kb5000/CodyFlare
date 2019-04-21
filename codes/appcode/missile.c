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
	Pos a, b;
	int num;
	Color color;
	double speed;
	int life;
	double flexibility;
	void(*explodeAnime)(int id, Pos position);
} Missiles;

void move_missile(Missile* missile, Pos b, double drawSpeed, double flexibility) {
	//double det = 12 * drawSpeed * 2 * pos_length(missile->momentum) *
	//	sin(pos_arc(missile->momentum) - pos_arc(size)) / pos_length(size);
	//missile->momentum = add_pos(missile->momentum, new_pos(det * missile->momentum.y, -det * missile->momentum.x));
	//double theta = -pos_arc(sub_pos(b, missile->position)) - pos_arc(b);
	double theta = pos_arc(missile->momentum) - pos_arc(sub_pos(b, missile->position));
	if (theta < -PI / 2) theta = -PI - theta;
	if (theta > PI / 2) theta = PI - theta;
	Pos p = sub_pos(rect_to_polar(missile->momentum), new_pos(0, flexibility * drawSpeed * theta));// fmin(theta, theta - PI)));
	missile->momentum = polar_to_rect(p);
	MovePen(missile->position.x, missile->position.y);
	//Pos pp = 
	//DrawLine()
}

void update_missile(void* missiles) {
	Missiles* miss = (Missiles*)missiles;
	set_color(miss->color);

	MovePen(miss->b.x, miss->b.y);
	DrawLine(0.01, 0.01);

	for (unsigned i = 0; i < miss->missile.len(&miss->missile); i++) {
		Missile* m = (Missile*)miss->missile.at(&miss->missile, i);
		if (!m->valid) continue;
		if (m->valid++ > miss->life) {
			m->valid = 0;
			miss->explodeAnime(Unique_ID("Missile"), m->position);
			return;
		}
		MovePen(m->position.x, m->position.y);
		double angle = pos_arc(m->momentum);
		DrawLine(0.1 * cos(angle), 0.1 * sin(angle));
		if (pos_length(sub_pos(miss->b, m->position)) <= 0.1) {
			m->valid = 0;
			miss->explodeAnime(Unique_ID("Missile"), m->position);
		}
		m->position = add_pos(m->position, m->momentum);
		move_missile(m, miss->b, miss->speed, miss->flexibility);// sub_pos(miss->b, miss->a), 1);
	}
}

void show_missile(Pos a, Pos b, int num, Color color, double speed, double maxAngle, 
				  double flexibility, int life, void explodeAnime(int id, Pos position)) {
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
		explodeAnime,
	};
	for (int i = 0; i < num; i++) {
		Missile* ms = (Missile*)miss.missile.at(&miss.missile, i);
		double theta = pos_arc(sub_pos(b, a));
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
