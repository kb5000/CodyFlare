#include "collision_test.h"
#include "collision.h"
#include "timer.h"
#include "color.h"
#include <stdio.h>
#include "graphics.h"
#include "imgui.h"
#include "input.h"


char lebalText[50];

typedef struct {
	Pos start, size;
	Color color;
} Rect;

Rect r1, r2;

void collision_handler(int group1, int id1, int group2, int id2, void* unuseful) {
	sprintf(lebalText, "the %d coled with %d", id1, id2);
}

void draw_rec(Rect* r) {
	set_color(r->color);
	drawRectangle(r->start.x, r->start.y, r->size.x, r->size.y, 0);
}

void draw_line(Rect* r) {
	set_color(r->color);
	MovePen(r->start.x, r->start.y);
	DrawLine(r->size.x, r->size.y);
}

void col_test(void* unuseful) {
	draw_rec(&r1);
	draw_line(&r2);
	move_by_dir_key(&r2.start, new_pos(0.1, 0.1));
	update_col_info(2, 1, r2.start, add_pos(r2.start, r2.size));
	drawLabel(0.1, 0.1, lebalText);
	sprintf(lebalText, "No collision now");
}

void test_of_collision() {
	InitGraphics();
	init_global_timer();
	init_col_detector();
	init_input();
	r1.start = new_pos(1, 1);
	r1.size = new_pos(2, 3);
	r1.color = color_by_name("Black");
	r2.start = new_pos(5, 2);
	r2.size = new_pos(1, 1);
	r2.color = color_by_name("Blue");
	//Below is the key code
	//first create groups by ID
	//only different group will detect collision
	add_col_group(1);
	add_col_group(2);
	//if uncomment this it will crash
	//add_col_group(2);
	//then create collision object, type, start point, end point, obj id
	CollisionObj r1c = create_col_obj(Col_Box, r1.start, add_pos(r1.start, r1.size), 1);
	CollisionObj r2c = create_col_obj(Col_Line, r2.start, add_pos(r2.start, r2.size), 1);
	//add obj to group
	add_col_obj_to_group(1, r1c);
	add_col_obj_to_group(2, r2c);
	//add collision handler, you can pass a para
	add_col_handler(1, 2, collision_handler, NULL);
	add_func_to_timer(auto_clear_display, NULL, 1, 1, -1);
	add_func_to_timer(col_test, NULL, 1, 1, -1);
	//finally start detection
	start_detection(1);
	start_global_timer();
}