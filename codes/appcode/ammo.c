#include "ammo.h"
#include "collision.h"
#include "linked_list.h"
#include "timer.h"
#include <stdlib.h>
#include "animes.h"

static ListHandler ammoList;

static const double enemyAmmoSpeed = 0.08;
static const double playerAmmoSpeed = 0.12;
static const double ammoLength = 0.12;

static int globalAmmoID = 0;

typedef struct {
	Pos pos, dirt;
	int isEnemy;
	int colObjID;
	int isValid;
} Ammo;

void init_ammo_system() {
	if (ammoList.destroy) {
		calls(ammoList, destroy);
	}
	globalAmmoID = 0;
	ammoList = new_empty_list();
	add_col_group(ENM_AMMO_COL_ID);
	add_col_group(PLR_AMMO_COL_ID);
}

void add_ammo(int isEnemy, Pos position, Pos direction) {
	Pos dirPos = pos_mut(direction, ammoLength / pos_length(direction));
	Ammo res = {
		position, dirPos,
		isEnemy,
		globalAmmoID++,
		1
	};
	CollisionObj co = create_col_obj(Col_Line, position, add_pos(position, dirPos), res.colObjID, new_pos(0, 0));
	add_col_obj_to_group(isEnemy ? ENM_AMMO_COL_ID : PLR_AMMO_COL_ID, co);
	hnew(Ammo, ress);
	*ress = res;
	calls(ammoList, push_back, ress);
}

void update_each_ammo(Ammo* ammo) {
	if (ammo->isEnemy == 1) {
		ammo->pos = add_pos(ammo->pos, pos_mut(ammo->dirt, enemyAmmoSpeed / pos_length(ammo->dirt)));
	} else if (ammo->isEnemy == 2) {
		ammo->pos = add_pos(ammo->pos, pos_mut(ammo->dirt, 0.6 * enemyAmmoSpeed / pos_length(ammo->dirt)));
	} else {
		ammo->pos = add_pos(ammo->pos, pos_mut(ammo->dirt, playerAmmoSpeed / pos_length(ammo->dirt)));
	}
	draw_anime_ammo_once(ammo->isEnemy, ammo->pos, ammo->dirt);
	Pos normal = add_pos(ammo->pos, polar_to_rect(new_pos(0.01, PI / 2 + pos_arc(ammo->dirt))));
	Pos lp = pos_mut(ammo->dirt, 1.018);
	update_col_info(ammo->isEnemy ? ENM_AMMO_COL_ID : PLR_AMMO_COL_ID, ammo->colObjID, normal, add_pos(normal, lp));
}

int is_invalid_ammo(Ammo* ammo, void* unuseful) {
	if (!ammo->isValid || !pos_in_rect(ammo->pos, new_pos(0, 0), new_pos(10, 7))) {
		remove_col_obj(ammo->isEnemy ? ENM_AMMO_COL_ID : PLR_AMMO_COL_ID, ammo->colObjID);
		return 1;
	}
	return 0;
}

void update_ammo(void* unuseful) {
	calls(ammoList, for_each, update_each_ammo);
	calls(ammoList, remove_if, is_invalid_ammo, NULL);
}

void set_ammo_invalid(int id) {
	Node* node = ammoList.head;
	for (; node; node = node->next) {
		Ammo* ammo = &cast(Ammo, node->data);
		if (ammo->colObjID == id) {
			ammo->isValid = 0;
			draw_anime_ammo_hit(ammo->pos);
			return;
		}
	}
}

void start_update_ammo() {
	add_func_to_timer(update_ammo, NULL, 1, 8979323, -1);
}

void stop_update_ammo() {
	remove_funcs_from_timer(8979323);
}
