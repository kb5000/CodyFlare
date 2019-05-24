#include "ai.h"
#include <math.h>

Pos basic_enemy_move(Pos postion, Pos playerPos) {
	Pos dir;
	if (pos_length(sub_pos(postion, playerPos)) < 3 && fabs(postion.x - playerPos.x) < 0.7 && postion.y > playerPos.y) {
		dir = new_pos(0, -0.08);
	} else {
		dir = new_pos(0, -0.02);
	}
	return add_pos(postion, dir);
}

Pos advanced_enemy_move(Pos position, Pos playerPos) {
	Pos dir;
	if (position.y > playerPos.y + 2) {
		double detx = position.x - playerPos.x;
		if (0 <= detx && detx <= 1.4) {
			dir = new_pos(1.7, -0.865);
		} else if (-1.4 <= detx && detx < 0) {
			dir = new_pos(-1.7, -0.865);
		} else {
			dir = new_pos(0, -0.9);
		}
	} else {
		double detx = position.x - playerPos.x;
		if (detx >= -0.05 && detx <= 0.05) {
			dir = new_pos(0, -0.865);
		} else if (detx > 0) {
			dir = new_pos(-1.5, -0.865);
		} else {
			dir = new_pos(1.5, -0.865);
		}
	}
	if (position.x < 0.2 && dir.x < 0 || position.x > 9.8 && dir.x > 0) dir.x = 0;
	dir = pos_mut(dir, 0.02);
	return add_pos(position, dir);
}

Pos swift_enemy_move(Pos position, Pos playerPos) {
	Pos dir;
	double detx = position.x - playerPos.x;
	if (playerPos.x > 9) {
		dir = new_pos(-3.2, -0.865);
	} else if (0 <= detx && detx <= 3 || playerPos.x < 1) {
		dir = new_pos(3.2, -0.865);
	} else if (-3 <= detx && detx < 0) {
		dir = new_pos(-3.2, -0.865);
	} else {
		dir = new_pos(0, -0.9);
	}
	if (position.x < 0.3 && dir.x < 0 || position.x > 9.7 && dir.x > 0) dir.x = 0;
	dir = pos_mut(dir, 0.02);
	return add_pos(position, dir);
}
