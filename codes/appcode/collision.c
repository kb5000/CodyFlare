#include "collision.h"
#include <stdlib.h>
#include <math.h>

ListHandler globalCollisionList;

static void (*collision_handler)(int groupID1, int groupID2, int id1, int id2);

void init_collision_detector(void func(int groupID1, int groupID2, int id1, int id2)) {
	collision_handler = func;
	globalCollisionList = new_empty_list();
}

void add_group_to_list(CollisionGroup* group) {
	globalCollisionList.push_back(&globalCollisionList, (void*)group);
}

void remove_group(int groupID) {
	while (((CollisionGroup*)globalCollisionList.head->data)->groupID == groupID) {
		globalCollisionList.pop_front(&globalCollisionList);
	}
	globalCollisionList.nowpos = globalCollisionList.head;
	while (globalCollisionList.nowpos->next) {
		if (((CollisionGroup*)globalCollisionList.nowpos->next->data)->groupID == groupID) {
			globalCollisionList.remove_after(&globalCollisionList);
		} else {
			globalCollisionList.nowpos = globalCollisionList.nowpos->next;
		}
	}
}

void destroy_handler(void* data) {
	CollisionGroup* group = (CollisionGroup*)data;
	group->boxes.destroy(&group->boxes);
}

void destroy_collision_list() {
	globalCollisionList.for_each(&globalCollisionList, destroy_handler);
	globalCollisionList.destroy(&globalCollisionList);
}

CollisionBox* create_collision_box(Pos position, Pos size, int id) {
	CollisionBox* res = (CollisionBox*)malloc(sizeof(CollisionBox));
	res->position = position;
	res->size = size;
	res->id = id;
	return res;
}

CollisionGroup* create_collision_group(ListHandler boxes, int groupID) {
	CollisionGroup* res = (CollisionGroup*)malloc(sizeof(CollisionGroup));
	res->boxes = boxes;
	res->groupID = groupID;
	return res;
}

int have_collision(CollisionBox lhs, CollisionBox rhs) {
	return (abs(lhs.position.x - rhs.position.x) < (lhs.size.x + rhs.size.x) ||
			abs(lhs.position.y - rhs.position.y) < (lhs.size.y + rhs.size.y));
	//TODO: fix bug
}

void detect_collision() {
}
