#include "collision_test.h"
#include "collision.h"
#include "timer.h"
#include "color.h"
#include <stdio.h>
#include "graphics.h"
#include "imgui.h"


char lebalText[50];

typedef struct {
	Pos start, size;
	Color color;
} Rect;

Rect r1, r2;

void collision_handler(int groupID1, int groupID2, int id1, int id2) {
	sprintf(lebalText, "the %d of %d coled with %d of %d", id1, groupID1, id2, groupID2);
}

void draw_rec(void* rect) {
	Rect* r = (Rect*)rect;
	set_color(r->color);
	drawRectangle(r->start.x, r->start.y, r->size.x, r->size.y, 0);
}

void test_of_collision() {
	init_global_timer();
	init_collision_detector(collision_handler);
	CollisionGroup* cg1, *cg2;
	cg1 = create_collision_group(new_empty_list(), 1);
	cg2 = create_collision_group(new_empty_list(), 2);
	add_col_to_group(cg1, create_collision_box(r1.start, r1.size, 1));
	
}