#pragma once
#include "linked_list.h"
#include "utility.h"
#include "vector.h"

typedef enum {
	Col_Box, Col_Line
} ColType;

typedef struct {
	int id;
	ColType colType;
	Pos start, end;
} CollisionObj;

typedef struct {
	int id;
	ListHandler objs;
} CollisionGroup;

typedef void ColHandler(int id1, int id2, void* para);

void init_col_dector();
void add_col_group(int id);
void add_col_obj_to_group(int objID, int groupID, CollisionObj colObj);
CollisionObj create_col_obj(ColType colType, Pos start, Pos end, int id);
void add_col_handler(int groupID1, int groupID2, ColHandler func, void* para);
CollisionObj* find_col_obj(int groupID, int objID);
void remove_col_obj(int groupID, int objID);
void destroy_col_detector();
void start_detection();
void end_detection();
