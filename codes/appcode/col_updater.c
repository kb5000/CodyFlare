#include "col_updater.h"
#include "collision.h"
#include "plane.h"
#include "ammo.h"

void start_col_dets() {
	add_col_handler(PLR_AMMO_COL_ID, ENM_PLN_COL_ID, player_ammo_enemy_plane_col, NULL);
	add_col_handler(ENM_AMMO_COL_ID, PLR_PLN_COL_ID, enemy_ammo_player_plane_col, NULL);
}

void player_ammo_enemy_plane_col(int group1, int id1, int group2, int id2, void* unuseful) {
	if (group1 == PLR_AMMO_COL_ID && group2 == ENM_PLN_COL_ID) {
		player_ammo_enemy_plane_col(group2, id2, group1, id1, unuseful);
		return;
	}
	set_ammo_invalid(id2);
	Plane* pln = find_plane_by_id(id1);
	if (!pln) return;
	pln->health -= 5;
	if (pln->health <= 0) {
		draw_anime_explode(17896, pln->position, 0.8, 6);
		remove_plane_by_id(id1);
	}
}


void enemy_ammo_player_plane_col(int group1, int id1, int group2, int id2, void* unuseful) {
	if (group1 == ENM_AMMO_COL_ID && group2 == PLR_PLN_COL_ID) {
		enemy_ammo_player_plane_col(group2, id2, group1, id1, unuseful);
		return;
	}
	set_ammo_invalid(id2);
	Plane* pln = find_plane_by_id(id1);
	if (!pln) return;
	pln->health -= 2;
	if (pln->health <= 0) {
		draw_anime_explode(17896, pln->position, 0.8, 6);
		remove_plane_by_id(id1);
	}
}

void missile_target_enemy(Pos pos, int id) {
	Plane* pln = find_plane_by_id(id);
	if (!pln) return;
	pln->health -= 5;
	if (pln->health <= 0) {
		draw_anime_explode(17896, pln->position, 0.8, 6);
		remove_plane_by_id(id);
	}
}


