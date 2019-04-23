#include "missile_test.h"
#include "missile.h"
#include "timer.h"
#include "graphics.h"
#include "input.h"
#include "imgui.h"
#include "animes.h"
#include <stdio.h>

static char buffer[40] = "No hit";

void bb(int id, Pos pos, double size) {
	draw_anime_explode(id, pos, size);
}

void exp_handler(Pos pos) {
	static int n = 0;
	n++;
	sprintf(buffer, "Hit on (%.2lf, %.2lf), %d times", pos.x, pos.y, n);
}

static Pos a, b = {5, 3.5};

void lanunch_missile(void* unuseful) {
	move_by_dir_key(&b, new_pos(0.08, 0.08));
	MouseKeys m = get_mouse_key();
	a = m.pos;
	if (m.left == 2) {
		show_missile(b, &a, 1, color_by_name("Blue"), 0.12, 1.5, 1.5, 120, 1, bb, 0.6, exp_handler);
		reset_mouse_key(1);
	}
	//b = add_pos(m.pos, new_pos(0, 2));
	if (m.right == 2) {
		b = m.pos;
		reset_mouse_key(3);
	}
}

void smash(void* unuseful, int event) {
	MouseKeys m = get_mouse_key();
	a = m.pos;
	show_missile(b, &a, 7, color_by_name("Red"), 0.16, -1.5, 1.2, 50, 1, bb, 0.5, exp_handler);
}

void show_circle(void* unuseful) {
	MovePen(b.x + 0.1, b.y);
	set_color(color_by_name("Green"));
	DrawArc(0.1, 0, 360);
	set_color(color_by_name("Brown"));
	drawLabel(0.1, 0.1, buffer);
}

void test_of_missile() {
	InitGraphics();
	init_global_timer();
	init_input();
	add_func_to_timer(auto_clear_display, 0, 1, 76760, -1);
	add_func_to_timer(lanunch_missile, 0, 1, -1564, -1);
	//show_missile(new_pos(5, 3.5), new_pos(5, 2), 10, color_by_name("Red"), 0.1, -1.5, 1.5, 100, bb);
	add_func_to_timer(remove_invalid_funcs, 0, 30, 12, -1);
	add_func_to_timer(show_circle, 0, 1, 12, -1);
	add_to_key_process(' ', smash, 0);


	start_global_timer();
}