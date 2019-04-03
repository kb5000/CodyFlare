#pragma once
#include "linked_list.h"
#include "point.h"

extern ListHandler globalCollisionList;

typedef struct {
	Pos position, size;
	int id;
} CollisionBox;

typedef struct {
	ListHandler boxes;
	int groupID;
} CollisionGroup;

void init_collision_detector(void collision_handler(int groupID1, int groupID2, int id1, int id2));
void add_group_to_list(CollisionGroup* group);
void remove_group(int groupID);
void destroy_collision_list();
CollisionBox* create_collision_box(Pos position, Pos size, int id);
CollisionGroup* create_collision_group(ListHandler boxes, int groupID);

int have_collision(CollisionBox lhs, CollisionBox rhs);

void detect_collision();

