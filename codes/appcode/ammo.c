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
	CollisionObj co = create_col_obj(Col_Line, position, add_pos(position, dirPos), res.colObjID);
	add_col_obj_to_group(isEnemy ? ENM_AMMO_COL_ID : PLR_AMMO_COL_ID, co);
	hnew(Ammo, ress);
	*ress = res;
	calls(ammoList, push_back, ress);
}

void update_each_ammo(Ammo* ammo) {
	draw_anime_ammo_once(ammo->isEnemy, ammo->pos, ammo->dirt);
	if (ammo->isEnemy) {
		ammo->pos = add_pos(ammo->pos, pos_mut(ammo->dirt, enemyAmmoSpeed / pos_length(ammo->dirt)));
	} else {
		ammo->pos = add_pos(ammo->pos, pos_mut(ammo->dirt, playerAmmoSpeed / pos_length(ammo->dirt)));
	}
	update_col_info(ammo->isEnemy ? ENM_AMMO_COL_ID : PLR_AMMO_COL_ID, ammo->colObjID, ammo->pos, add_pos(ammo->pos, ammo->dirt));
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
