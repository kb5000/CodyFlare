#include "plane.h"
#include <stdlib.h>
#include "timer.h"
#include "collision.h"

static ListHandler planeList;

void init_plane_list() {
	planeList = new_empty_list();
}

Plane create_plane(int id, PlaneType type, Pos initPosition, int health, int missileTime, int numOfBombs, int ammoTime) {
	Plane res = {
		id, 
		type,
		initPosition,
		health,
		missileTime,
		numOfBombs,
		ammoTime,
	};
	return res;
}

void add_plane(Plane plane) {
	hnew(Plane, pln);
	*pln = plane;
	calls(planeList, push_back, pln);
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

void update_plane(void* unuseful) {

}

void start_display_planes() {
	add_func_to_timer(update_plane, NULL, 1, 285744, -1);
}

void stop_display_planes() {
	remove_funcs_from_timer(285744);
}
