#include "collision.h"
#include <stdlib.h>
#include <math.h>

ListHandler globalCollisionList;

static void (*collision_handler)(int groupID1, int groupID2, int id1, int id2);

void init_collision_detector(void func(int groupID1, int groupID2, int id1, int id2)) {
	collision_handler = func;
	globalCollisionList = new_empty_list();
}

void add_col_group_to_list(CollisionGroup* group) {
	globalCollisionList.push_back(&globalCollisionList, (void*)group);
}

void add_col_to_group(CollisionGroup* target, CollisionObj* source) {
	target->boxes.push_back(&target->boxes, source);
}

void remove_col_group(int groupID) {
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

CollisionObj* create_collision_box(Pos position, Pos size, int id) {
	CollisionObj* res = (CollisionObj*)malloc(sizeof(CollisionObj));
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

int have_collision(CollisionObj* lhs, CollisionObj* rhs) {
	return (lhs->position.x < rhs->position.x + rhs->size.x) && (rhs->position.x < lhs->position.x + lhs->size.x) &&
		   (lhs->position.y < rhs->position.y + rhs->size.y) && (rhs->position.y < lhs->position.y + lhs->size.y);
}

void detect_collision(void* unuseful) {
	for (Node* i = globalCollisionList.head; i; i = i->next) {
		for (Node* j = globalCollisionList.head; j; j = j->next) {
			CollisionGroup* a = (CollisionGroup*)(i->data);
			CollisionGroup* b = (CollisionGroup*)(j->data);
			if (a->groupID < b->groupID) {
				for (Node* p = a->boxes.head; p; p = p->next) {
					for (Node* q = b->boxes.head; q; q = q->next) {
						CollisionObj* m = (CollisionObj*)(p->data);
						CollisionObj* n = (CollisionObj*)(q->data);
						if (have_collision(m, n)) collision_handler(a->groupID, b->groupID, m->id, n->id);
					}
				}
			}
		}
	}
}
