#include "plane_test.h"
#include "plane.h"
#include "anime_test.h"
#include "ammo.h"
#include "timer.h"
#include "input.h"
#include "collision.h"
#include "col_updater.h"
#include "imgui.h"
#include <stdio.h>

static char r[32];

void show_health(void* unuseful) {
	Plane* p = find_plane_by_id(0);
	if (!p) {
		return;
	}
	sprintf(r, "%d, %d", find_plane_by_id(0)->type, find_plane_by_id(0)->health);
	drawLabel(0.1, 0.1, r);
}

void test_of_plane() {
	common_anime_test_init();
	init_col_detector();
	init_ammo_system();
	init_plane_list();
	add_plane(create_plane(Player_Plane, new_pos(5, 1), 100, 5));
	//add_plane(create_plane(Basic_Enemy_Plane, new_pos(2, 6.5), 100, 0));
	//add_plane(create_plane(Advanced_Enemy_Plane, new_pos(8, 6.8), 100, 0));
	//add_plane(create_plane(Swift_Enemy_Plane, new_pos(5, 6.8), 100, 0));
	start_display_planes();
	start_update_ammo();
	add_func_to_timer(generate_plane, NULL, 1, 1213, -1);
	start_col_dets();
	start_detection(1);
	add_func_to_timer(show_health, NULL, 1, 12, -1);
}