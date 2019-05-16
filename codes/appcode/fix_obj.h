#pragma once
#include "utility.h"

#define FIX_OBJ_COL_ID 833

typedef enum {
	Fix_Obj_Health = 0,
	Fix_Obj_Bomb = 1,
	Fix_Obj_Shield = 2
} Fix_Objs;

typedef struct {
	Fix_Objs fixObj;
	Pos pos;
	int existTime;
	int id;
} FixObj;

void init_fix_obj_system();

void generate_fix_obj(Pos pos);

void add_fix_obj(Pos pos, Fix_Objs type);

void remove_fix_obj(int id);

void start_show_fix_obj();

void set_fix_obj_invalid(int id);

FixObj* find_fix_obj(int id);

