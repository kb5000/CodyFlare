#include "fix_obj.h"
#include "linked_list.h"
#include "collision.h"
#include "animes.h"
#include "tortoise.h"
#include "extgraph.h"
#include "col_updater.h"
#include "plane.h"
#include "random.h"

static ListHandler fixObjList;
static int fixObjID = 0;

void init_fix_obj_system() {
	fixObjList = new_empty_list();
	add_col_group(FIX_OBJ_COL_ID);
	add_col_handler(FIX_OBJ_COL_ID, PLR_PLN_COL_ID, fix_plane_col, NULL);
}

void generate_fix_obj(Pos pos) {
	int p = RandomInteger(0, 5);
	if (p > 3) add_fix_obj(pos, Fix_Obj_Health);
	else add_fix_obj(pos, Fix_Obj_Bomb);
}

void add_fix_obj(Pos pos, Fix_Objs type) {
	FixObj fixObj = {
		type,
		pos,
		0,
		fixObjID++
	};
	hnew(FixObj, fix);
	*fix = fixObj;
	calls(fixObjList, push_back, fix);
	add_col_obj_to_group(FIX_OBJ_COL_ID, create_col_obj(Col_Box, sub_pos(pos, new_pos(0.1, 0.1)),
														add_pos(pos, new_pos(0.1, 0.1)), fixObj.id, new_pos(0, 0)));
}

int remove_fix_obj_handler(FixObj* fixObj, int* id) {
	return fixObj->id == *id;
}

int remove_invalid_fix_objs(FixObj* fixObj, void* unuseful) {
	if (fixObj && fixObj->existTime > 190) {
		remove_col_obj(FIX_OBJ_COL_ID, fixObj->id);
		return 1;
	}
	return 0;
}

void remove_fix_obj(int id) {
	calls(fixObjList, remove_if, remove_fix_obj_handler, &id);
}

static void draw_fix_obj_health(Pos pos) {
	Pos ld = add_pos(pos, new_pos(-0.1, 0.1));
	set_color(color_by_rgb(68, 175, 92));
	move_tortoise(ld);
	tts_set_home();
	tts_turn(0);
	tts_pd();
	for (int i = 0; i < 4; i++) {
		tts_fd(0.2);
		tts_lt(90);
	}
	set_color(color_by_rgb(216, 45, 55));
	tts_pu();		tts_fd(0.105);	tts_lt(90);		tts_fd(0.02);
	tts_pd();		SetPenSize(2);	tts_fd(0.16);	tts_pu();
	tts_home();		tts_fd(0.1);	tts_rt(90);		tts_fd(0.02);
	tts_pd();		tts_fd(0.16);	tts_pu();		SetPenSize(1);
}

static void draw_fix_obj_bomb(Pos pos) {
	Pos ld = add_pos(pos, new_pos(-0.1, 0.1));
	set_color(color_by_rgb(68, 175, 92));
	move_tortoise(ld);
	tts_set_home();
	tts_turn(0);
	tts_pd();
	for (int i = 0; i < 4; i++) {
		tts_fd(0.2);
		tts_lt(90);
	}
	set_color(color_by_rgb(218, 194, 46));
	tts_pu();	 tts_fd(0.04);	tts_lt(90);		tts_fd(0.055);
	tts_pd();	 tts_lt(2.8);
	SetPenSize(2);
	for (int i = 0; i < 12; i++) {
		tts_fd(2 * PI * 0.05 / 12);
		tts_rt(360.0 / 12);
	}
	tts_pu();	tts_home();		tts_turn(0);	tts_fd(0.11);
	tts_lt(90);	tts_fd(0.092);	tts_pd();		tts_lt(30);
	set_color(color_by_rgb(180, 150, 150));
	for (int i = 0; i < 5; i++) {
		tts_fd(0.02);
		tts_rt(30);
	}
}

void show_each_fix_obj(FixObj* fo) {
	if (fo->existTime <= 132 || fo->existTime > 140 && fo->existTime < 152 ||
		fo->existTime > 160 && fo->existTime < 172 || fo->existTime > 180) {
		switch (fo->fixObj) {
		case Fix_Obj_Health:
			draw_fix_obj_health(fo->pos);
			break;
		case Fix_Obj_Bomb:
			draw_fix_obj_bomb(fo->pos);
			break;
		case Fix_Obj_Shield:
			break;
		default:
			break;
		}
	}
	update_col_info(FIX_OBJ_COL_ID, fo->id, sub_pos(fo->pos, new_pos(0.1, 0.1)),
					add_pos(fo->pos, new_pos(0.1, 0.1)));
	fo->existTime++;
	if (fo->pos.y > 0.5) fo->pos.y -= 0.02;
}

void show_fix_obj(void* unuseful) {
	calls(fixObjList, for_each, show_each_fix_obj);
	calls(fixObjList, remove_if, remove_invalid_fix_objs, NULL);
}

void start_show_fix_obj() {
	add_func_to_timer(show_fix_obj, NULL, 1, 772777, -1);
}

void set_fix_obj_invalid(int id) {
	for (Node* node = fixObjList.head; node; node = node->next) {
		FixObj* fo = (FixObj*)node->data;
		if (!fo) continue;
		if (fo->id == id) {
			fo->existTime = 99999;
			return;
		}
	}
}

FixObj* find_fix_obj(int id) {
	for (Node* node = fixObjList.head; node; node = node->next) {
		FixObj* fo = (FixObj*)node->data;
		if (!fo) continue;
		if (fo->id == id) {
			return fo;
		}
	}
	return NULL;
}