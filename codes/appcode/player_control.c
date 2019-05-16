#include "player_control.h"
#include "plane.h"
#include "weapon.h"
#include "input.h"
#include "col_updater.h"
#include <stdlib.h>

static Pos noTargetPos = {5, 0};
static Pos* delayPos;
static int firstPressFlag = 0, firstInFlag = 1;

void start_control() {
	add_to_key_process(' ', launch_missile, NULL);
	add_to_key_process('F', place_bomb, NULL);
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
	if (event == 0) {
		Plane* player = find_plane_by_id(0);
		if (!player || player->numOfBombs <= 0) return;
		if (firstPressFlag == 0) {
			firstPressFlag = 1;
			delayPos = (Pos*)malloc(sizeof(Pos));
			*delayPos = player->position;
			add_func_to_timer(draw_front_sight, delayPos, 1, 99887766, -1);
		}
	} else if (event == 1 && firstPressFlag) {
		firstPressFlag = 0;
		//firstInFlag = 1;
		Plane* player = find_plane_by_id(0);
		if (!player) return;
		if (player->numOfBombs > 0) {
			player->numOfBombs--;
			shoot_bomb(0, *delayPos);
			//*delayPos = new_pos(-1, -1);
			remove_funcs_from_timer(99887766);
		}
	}
}