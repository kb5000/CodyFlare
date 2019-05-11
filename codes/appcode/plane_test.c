#include "plane_test.h"
#include "plane.h"
#include "anime_test.h"
#include "ammo.h"
#include "timer.h"
#include "input.h"
#include "collision.h"

void test_of_plane() {
	common_anime_test_init();
	init_col_detector();
	init_ammo_system();
	init_plane_list();
	add_plane(create_plane(Player_Plane, new_pos(5, 1), 100, 5));
	add_plane(create_plane(Basic_Enemy_Plane, new_pos(2, 6.5), 100, 0));
	start_display_planes();
	start_update_ammo();
	
}