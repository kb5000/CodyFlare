#include "col_updater.h"
#include "collision.h"
#include "plane.h"
#include "ammo.h"
#include "fix_obj.h"
#include "animes.h"

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
	plane_explode(pln, 5);
}


void enemy_ammo_player_plane_col(int group1, int id1, int group2, int id2, void* unuseful) {
	if (group1 == ENM_AMMO_COL_ID && group2 == PLR_PLN_COL_ID) {
		enemy_ammo_player_plane_col(group2, id2, group1, id1, unuseful);
		return;
	}
	set_ammo_invalid(id2);
	Plane* pln = find_plane_by_id(id1);
	if (!pln) return;
	plane_explode(pln, 2);
}

void missile_target_enemy(Pos pos, int id) {
	Plane* pln = find_plane_by_id(id);
	if (!pln) return;
	plane_explode(pln, 5);
}

void missile_target_by_boss(Pos pos, int id) {
	Plane* pln = find_plane_by_id(id);
	if (!pln) return;
	plane_explode(pln, 3);
}

void missile_target_by_player(Pos pos, int id) {
	Plane* pln = find_plane_by_id(id);
	if (!pln) return;
	plane_explode(pln, 12);
}

void fix_plane_col(int group1, int id1, int group2, int id2, void* unuseful) {
	if (group1 == FIX_OBJ_COL_ID && group2 == PLR_PLN_COL_ID) {
		fix_plane_col(group2, id2, group1, id1, unuseful);
		return;
	}
	Fix_Objs fo = find_fix_obj(id2)->fixObj;
	set_fix_obj_invalid(id2);
	Plane* pln = find_plane_by_id(id1);
	if (!pln) return;
	switch (fo) {
	case Fix_Obj_Health:
		//if (pln->health >= 100) break;
		//if (pln->health >= 90) {
		//	pln->health = 100;
		//	break;
		//}
		pln->health += 10;
		break;
	case Fix_Obj_Bomb:
		pln->numOfBombs += 1;
		break;
	default:
		break;
	}
}
