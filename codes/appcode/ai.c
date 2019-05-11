#include "ai.h"

Pos basic_enemy_move(Pos postion) {
	return add_pos(postion, new_pos(0, -0.02));
}

Pos advanced_enemy_move(Pos position, Pos playerPos) {
	Pos dir;
	if (position.y > playerPos.y + 1) {
		double detx = position.x - playerPos.x;
		if (0 <= detx && detx <= 2) {
			dir = new_pos(0.5, -0.865);
		} else if (-2 <= detx && detx < 0) {
			dir = new_pos(-0.5, -0.865);
		} else {
			dir = new_pos(0, -0.9);
		}
	} else {
		double detx = position.x - playerPos.x;
		if (detx >= 0) {
			dir = new_pos(-0.5, -0.865);
		} else {
			dir = new_pos(0.5, -0.865);
		}
	}
	if (position.x < 0.3 || position.x > 9.7) dir.x = 0;
	return add_pos(position, dir);
}

Pos swift_enemy_move(Pos position, Pos playerPos) {
	Pos dir;
	double detx = position.x - playerPos.x;
	if (0 <= detx && detx <= 2) {
		dir = new_pos(0.5, -0.865);
	} else if (-2 <= detx && detx < 0) {
		dir = new_pos(-0.5, -0.865);
	} else {
		dir = new_pos(0, -0.9);
	}
	if (position.x < 0.3 || position.x > 9.7) dir.x = 0;
	return add_pos(position, dir);
}
