#include "plane.h"
#include <stdlib.h>
#include "timer.h"
#include "collision.h"
#include "input.h"
#include "ai.h"
#include "weapon.h"
#include "random.h"
#include "col_updater.h"

static ListHandler planeList;
static int planeID = 0;
static int planeRefreshTime = 0;
static int score = 0;

void init_plane_list() {
	planeList = new_empty_list();
	add_col_group(PLR_PLN_COL_ID);
	add_col_group(ENM_PLN_COL_ID);
}

Plane create_plane(PlaneType type, Pos initPosition, int health, int numOfBombs) {
	Plane res = {
		0,
		type,
		initPosition,
		health,
		0,
		numOfBombs,
		0,
	};
	return res;
}

void add_plane(Plane plane) {
	hnew(Plane, pln);
	*pln = plane;
	pln->id = planeID++;
	calls(planeList, push_back, pln);
	switch (plane.type) {
	case Player_Plane:
		add_col_obj_to_group(PLR_PLN_COL_ID, create_col_obj(Col_Line, add_pos(pln->position, new_pos(-0.2, 0)),
													 add_pos(pln->position, new_pos(0.2, 0)), pln->id));
		break;
	case Basic_Enemy_Plane:
		add_col_obj_to_group(ENM_PLN_COL_ID, create_col_obj(Col_Line, add_pos(pln->position, new_pos(-0.2, 0)),
													 add_pos(pln->position, new_pos(0.2, 0)), pln->id));
		break;
	case Advanced_Enemy_Plane:
		add_col_obj_to_group(ENM_PLN_COL_ID, create_col_obj(Col_Line, add_pos(pln->position, new_pos(-0.2, 0)),
													 add_pos(pln->position, new_pos(0.2, 0)), pln->id));
		break;
	case Swift_Enemy_Plane:
		add_col_obj_to_group(ENM_PLN_COL_ID, create_col_obj(Col_Line, add_pos(pln->position, new_pos(-0.2, 0)),
													 add_pos(pln->position, new_pos(0.2, 0)), pln->id));
		break;
	default:
		break;
	}
}

Plane* find_plane_by_id(int id) {
	for (Node* node = planeList.head; node; node = node->next) {
		Plane* plane = (Plane*)node->data;
		if (plane->id == id) return plane;
	}
	return NULL;
}

Plane* find_dangerous_plane() {
	if (!planeList.head || !planeList.head->next) return NULL;
	Plane* dangp = (Plane*)planeList.head->next->data;
	for (Node* node = planeList.head->next; node; node = node->next) {
		Plane* plane = (Plane*)node->data;
		if (plane->position.y < dangp->position.y) dangp = plane;
	}
	return dangp;
}

int remove_plane_helper(Plane* plane, int* id) {
	if (plane->id == *id) {
		if (plane->type == Player_Plane) {
			remove_col_obj(PLR_PLN_COL_ID, *id);
		} else {
			remove_col_obj(ENM_PLN_COL_ID, *id);
		}
		return 1;
	}
	return 0;
}

void remove_plane_by_id(int id) {
	calls(planeList, remove_if, remove_plane_helper, &id);
}

Pos* player_plane_pos() {
	//assume that the first plane is the player's plane
	return &((Plane*)(planeList.head->data))->position;
}

void update_each_plane(Plane* plane) {
	MovePen(plane->position.x - 0.2, plane->position.y);
	DrawLine(0.4, 0);
	switch (plane->type) {
	case Player_Plane:
		if (plane->position.x < 0 && plane->position.y < 0) return;
		move_by_dir_key(&plane->position, new_pos(0.1, 0.1));
		if (plane->position.x < 0.2) plane->position.x = 0.2;
		if (plane->position.x > 9.8) plane->position.x = 9.8;
		if (plane->position.y < 0.2) plane->position.y = 0.2;
		if (plane->position.y > 6.8) plane->position.y = 6.8;
		plane->missileTime++;
		if (plane->ammoTime++ == 3) {
			shoot_gun(Player_Ammo, add_pos(plane->position, new_pos(0, 0.1)), new_pos(0, 0.1));
			plane->ammoTime = 0;
		}
		update_col_info(PLR_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.2, 0)),
						add_pos(plane->position, new_pos(0.2, 0)));
		break;
	case Basic_Enemy_Plane:
		plane->position = basic_enemy_move(plane->position);
		if (plane->ammoTime++ == 16) {
			shoot_gun(Basic_Enemy_Ammo, add_pos(plane->position, new_pos(0, 0.1)), new_pos(0, -0.1));
			plane->ammoTime = 0;
		}
		update_col_info(ENM_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.2, 0)),
						add_pos(plane->position, new_pos(0.2, 0)));
		break;
	case Advanced_Enemy_Plane:
	{
		Pos pos = *player_plane_pos();
		plane->position = advanced_enemy_move(plane->position, pos);
		if (plane->position.y > pos.y + 2) {
			if (plane->missileTime++ == 60) {
				shoot_missile(Basic_Enemy_Ammo, add_pos(plane->position, new_pos(0, 0.1)), player_plane_pos(),
							  0, missile_target_enemy); 
				plane->missileTime = 0;
			}
		} else {
			if (plane->ammoTime++ == 6) {
				shoot_gun(Basic_Enemy_Ammo, add_pos(plane->position, new_pos(0, 0.1)), sub_pos(pos, plane->position));
				plane->ammoTime = 0;
			}
		}
		update_col_info(ENM_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.2, 0)),
						add_pos(plane->position, new_pos(0.2, 0)));
	}
		break;
	case Swift_Enemy_Plane:
	{
		Pos pos = *player_plane_pos();
		plane->position = swift_enemy_move(plane->position, pos);
		update_col_info(ENM_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.2, 0)),
						add_pos(plane->position, new_pos(0.2, 0)));
		if (pos_length(sub_pos(pos, plane->position)) < 0.7) {
			shoot_bomb(Basic_Enemy_Ammo, plane->position);
			plane->position = new_pos(-1, -1);
		}
	}
		break;
	default:
		break;
	}
}

int remove_invalid_plane(Plane* plane, void* unuseful) {
	if (!pos_in_rect(plane->position, new_pos(0, 0), new_pos(10, 7.4))) {
		if (plane->type == Player_Plane) {
			remove_col_obj(PLR_PLN_COL_ID, plane->id);
		} else {
			remove_col_obj(ENM_PLN_COL_ID, plane->id);
		}
		return 1;
	}
	return 0;
}

void update_plane(void* unuseful) {
	calls(planeList, for_each, update_each_plane);
	calls(planeList, remove_if, remove_invalid_plane, NULL);
}

void generate_plane(void* unuseful) {
	if (planeRefreshTime++ == 80) {
		Plane plane = create_plane(Basic_Enemy_Plane, new_pos(RandomReal(0.2, 9.8), 7.2), 20, 0);
		int seed = RandomInteger(0, 8);
		if (seed < 5) {
			plane.type = Basic_Enemy_Plane;
		} else if (seed < 7) {
			plane.type = Advanced_Enemy_Plane;
			plane.health = 25;
		} else {
			plane.type = Swift_Enemy_Plane;
			plane.health = 15;
		}
		add_plane(plane);
		planeRefreshTime = 0;
	}
}

void start_display_planes() {
	add_func_to_timer(update_plane, NULL, 1, 285744, -1);
}

void stop_display_planes() {
	remove_funcs_from_timer(285744);
}

void plane_explode(Plane* plane, int health) {
	plane->health -= health;
	if (plane->health <= 0) {
		add_score(plane->type);
		draw_anime_explode(17896, plane->position, 0.8, 6);
		remove_plane_by_id(plane->id);
	}
}

ListHandler planes() {
	return planeList;
}

void clear_score() {
	score = 0;
}

void add_score(PlaneType plane) {
	switch (plane) {
	case Basic_Enemy_Plane:
		score += 50;
		break;
	case Advanced_Enemy_Plane:
		score += 100;
		break;
	case Swift_Enemy_Plane:
		score += 80;
		break;
	default:
		break;
	}
}

int current_score() {
	return score;
}