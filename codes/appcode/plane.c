#include "plane.h"
#include <stdlib.h>
#include "timer.h"
#include "collision.h"
#include "input.h"
#include "ai.h"
#include "weapon.h"

static ListHandler planeList;
static int planeID = 0;

void init_plane_list() {
	planeList = new_empty_list();
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
	calls(planeList, push_back, pln);
	pln->id = planeID++;
	switch (plane.type) {
	case Player_Plane:
		break;
	case Basic_Enemy_Plane:
		break;
	case Advanced_Enemy_Plane:
		break;
	case Swift_Enemy_Plane:
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
	if (planeList.head) return NULL;
	Plane* dangp = (Plane*)planeList.head->data;
	for (Node* node = planeList.head; node; node = node->next) {
		Plane* plane = (Plane*)node->data;
		if (plane->position.y < dangp->position.y) dangp = plane;
	}
	return dangp;
}

int remove_plane_helper(Plane* plane, int* id) {
	return plane->id == *id;
}

void remove_plane_by_id(int id) {
	calls(planeList, remove_if, remove_plane_helper, &id);
}

void update_each_plane(Plane* plane) {
	MovePen(plane->position.x - 0.2, plane->position.y);
	DrawLine(0.4, 0);
	switch (plane->type) {
	case Player_Plane:
		move_by_dir_key(&plane->position, new_pos(0.1, 0.1));
		if (plane->ammoTime++ == 6) {
			shoot_gun(Player_Ammo, add_pos(plane->position, new_pos(0, 0.1)), new_pos(0, 0.1));
			plane->ammoTime = 0;
		}
		break;
	case Basic_Enemy_Plane:
		plane->position = basic_enemy_move(plane->position);
		if (plane->ammoTime++ == 16) {
			shoot_gun(Basic_Enemy_Ammo, add_pos(plane->position, new_pos(0, 0.1)), new_pos(0, -0.1));
			plane->ammoTime = 0;
		}
		break;
	case Advanced_Enemy_Plane:
		break;
	case Swift_Enemy_Plane:
		break;
	default:
		break;
	}
}

void update_plane(void* unuseful) {
	calls(planeList, for_each, update_each_plane);
}

void start_display_planes() {
	add_func_to_timer(update_plane, NULL, 1, 285744, -1);
}

void stop_display_planes() {
	remove_funcs_from_timer(285744);
}
