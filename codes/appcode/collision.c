#include "collision.h"
#include <stdlib.h>
#include "hashmap.h"
#include "timer.h"

typedef struct {
	IntPair ids;
	ColHandler* colHandler;
	void* para;
} ColNode;

static ListHandler globalCollisionList;
static ListHandler globalCollisionHandler;

void init_col_dector() {
	globalCollisionList = new_empty_list();
}

static void col_group_equal(CollisionGroup* cg, int* groupID) {
	return cg->id == *groupID;
}

static void col_obj_equal(CollisionGroup* co, int* objID) {
	return co->id == *objID;
}

void add_col_group(int id) {
	if (!calls(globalCollisionList, find_if, col_group_equal, &id)) {
		hnew(CollisionGroup, cg);
		cg->id = id;
		cg->objs = new_empty_list();
		calls(globalCollisionList, push_back, cg);
	} else {
		crash_now("Add an exist group id");
	}
}

void add_col_obj_to_group(int objID, int groupID, CollisionObj colObj) {
	CollisionGroup* cg;
	CollisionObj* cob;
	if (cg = calls(globalCollisionList, find_if, col_group_equal, &groupID)) {
		if (cob = calls(cg->objs, find_if, col_obj_equal, &objID)) {
			crash_now("obj id already exists when adding obj");
		}
		hnew(CollisionObj, co);
		*co = colObj;
		calls(cg->objs, push_back, co);
	} else {
		crash_now("group id doesnt exist when adding obj");
	}
}

CollisionObj create_col_obj(ColType colType, Pos start, Pos end, int id) {
	CollisionObj res = {
		id,
		colType,
		start, end,
	};
	return res;
}

static void col_handler_equal(ColNode* cg, IntPair* groupID) {
	return (cg->ids.a == groupID->a && cg->ids.b == groupID->b) || 
		   (cg->ids.a == groupID->b && cg->ids.b == groupID->a);
}

void add_col_handler(int groupID1, int groupID2, ColHandler func, void* para) {
	IntPair ids = {groupID1, groupID2};
	ColNode* chn;
	if (chn = calls(globalCollisionHandler, find_if, col_handler_equal, &ids)) {
		if (chn->para && chn->para != para) {
			free(chn->para);
		}
		chn->colHandler = func;
		chn->para = para;
		return;
	}
	ColNode colHandler = {
		ids,
		func,
		para,
	};
	hnew(ColNode, ch);
	*ch = colHandler;
	calls(globalCollisionHandler, push_back, ch);
}

static ColHandler* find_col_handler(int groupID1, int groupID2) {
	IntPair ids = {groupID1, groupID2};
	return calls(globalCollisionHandler, find_if, col_handler_equal, &ids);
}

CollisionObj* find_col_obj(int groupID, int objID) {
	CollisionGroup* cg;
	CollisionObj* res;
	if (cg = calls(globalCollisionList, find_if, col_group_equal, &groupID)) {
		if (res = calls(cg->objs, find_if, col_obj_equal, &objID)) {
			return res;
		}
	}
	return NULL;
}

void remove_col_obj(int groupID, int objID) {
	CollisionGroup* cg;
	if (cg = calls(globalCollisionList, find_if, col_group_equal, &groupID)) {
		calls(cg->objs, remove_if, col_obj_equal, &objID);
	}
}

static double det_2_dim(Pos a, Pos b) {
	return a.x * b.y - a.y * b.x;
}

static int box_box_col_dec(CollisionObj* a, CollisionObj* b) {
	return a->start.x <= b->end.x && b->start.x <= b->end.x &&
		   a->start.y <= b->end.y && b->start.y <= a->end.y;
}

static int line_line_base_dec(Pos A, Pos B, Pos C, Pos D) {
	const double zero = 1e-9;
	Pos AC = sub_pos(C, A);
	Pos AD = sub_pos(C, A);
	Pos BC = sub_pos(C, A);
	Pos BD = sub_pos(C, A);
	return det_2_dim(AC, AD) * det_2_dim(BC, BD) <= zero &&
		   det_2_dim(AC, BC) * det_2_dim(AD, BD) <= zero;
}

static int point_in_box(Pos p, Pos a, Pos b) {
	return p.x >= a.x && p.x <= b.x && p.y >= a.y && p.y <= b.y;
}

static int box_line_col_dec(CollisionObj* b, CollisionObj* l) {
	if (point_in_box(l->start, b->start, b->end) || point_in_box(l->end, b->start, b->end))
		return 1;
	Pos ld = b->start;
	Pos rd = new_pos(b->end.x, b->start.y);
	Pos lu = new_pos(b->start.x, b->end.y);
	Pos ru = b->end;
	return line_line_base_dec(l->start, l->end, ld, rd) ||
		   line_line_base_dec(l->start, l->end, lu, ru) ||
		   line_line_base_dec(l->start, l->end, lu, ld) ||
		   line_line_base_dec(l->start, l->end, ru, rd);
}

static int line_line_col_dec(CollisionObj* a, CollisionObj* b) {
	return line_line_base_dec(a->start, a->end, b->start, b->end);
}

static void col_obj_detection(CollisionGroup* lhs, CollisionGroup* rhs, ColHandler* func) {
	for (Node* l = lhs->objs.head; l; l = l->next) {
		for (Node* r = rhs->objs.head; r; r = r->next) {
			CollisionObj* lc = (CollisionObj*)l->data;
			CollisionObj* rc = (CollisionObj*)r->data;
			if (lc->colType == Col_Line && rc->colType == Col_Line) {
				if (line_line_col_dec(lc, rc)) func(lc->id, rc->id, lhs->id, rhs->id);
			} else if (lc->colType == Col_Box && rc->colType == Col_Box) {
				if (box_box_col_dec(lc, rc)) func(lc->id, rc->id, lhs->id, rhs->id);
			} else if (lc->colType == Col_Box && rc->colType == Col_Line) {
				if (box_line_col_dec(lc, rc)) func(lc->id, rc->id, lhs->id, rhs->id);
			} else if (lc->colType == Col_Line && rc->colType == Col_Box) {
				if (box_line_col_dec(rc, lc)) func(lc->id, rc->id, lhs->id, rhs->id);
			}
		}
	}
}

static void col_detection(void* unuseful) {
	Node* stabler = globalCollisionList.head;
	if (!stabler) return;
	Node* floater = stabler->next;
	while (stabler && stabler->next) {
		while (floater) {
			ColHandler* func;
			if (func = find_col_handler(((CollisionGroup*)stabler->data)->id, 
				((CollisionGroup*)floater->data)->id)) {
				col_obj_detection((CollisionGroup*)stabler->data, (CollisionGroup*)floater->data, func);
			}
			floater = floater->next;
		}
		stabler = stabler->next;
		floater = stabler->next;
	}
}

static void destroy_col_objs(CollisionGroup* cg) {
	call0(cg->objs, destroy);
}

void destroy_col_detector() {
	end_detection();
	call0(globalCollisionHandler, destroy);
	calls(globalCollisionList, for_each, destroy_col_objs);
	call0(globalCollisionList, destroy);
}

void start_detection() {
	add_func_to_timer(col_detection, NULL, 1, 16777216, -1);
}

void end_detection() {
	remove_funcs_from_timer(16777216);
}
