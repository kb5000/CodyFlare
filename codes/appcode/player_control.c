#include "player_control.h"
#include "plane.h"
#include "weapon.h"
#include "input.h"
#include "col_updater.h"

static Pos noTargetPos = {5, 0};

void start_control() {
	add_to_key_process(' ', launch_missile, NULL);
	add_to_key_process('B', place_bomb, NULL);
}

void launch_missile(int key, void* unuseful, int event) {
	Plane* player = find_plane_by_id(0);
	if (!player) return;
	if (player->missileTime >= 100) {
		player->missileTime = 0;
		Plane* target = find_dangerous_plane();
		if (!target) {
			shoot_missile(0, player->position, &noTargetPos, 0, NULL);
			return;
		}
		shoot_missile(0, player->position, &target->position, target->id, missile_target_by_player);
	}
}

void place_bomb(int key, void* unuseful, int event) {
	if (event != 0) return;
	Plane* player = find_plane_by_id(0);
	if (!player) return;
	if (player->numOfBombs > 0) {
		player->numOfBombs--;
		shoot_bomb(0, player->position);
	}
}