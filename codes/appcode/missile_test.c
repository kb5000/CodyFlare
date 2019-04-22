#include "missile_test.h"
#include "missile.h"
#include "timer.h"
#include "graphics.h"
#include "input.h"
#include "imgui.h"
#include "animes.h"

void bb(int id, Pos pos, double size) {
	draw_anime_explode(id, pos, size);
}

static Pos b = {5, 2};

void lanunch_missile(void* unuseful) {
	MouseKeys m = get_mouse_key();
	if (m.left == 2) {
		show_missile(m.pos, &b, 1, color_by_name("Blue"), 0.12, 2.5, 1.5, 120, 1, bb, 0.6);
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
	show_missile(m.pos, &b, 8, color_by_name("Red"), 0.16, -1.5, 1.2, 50, 1, bb, 0.5);
}

void show_circle(void* unuseful) {
	MovePen(b.x, b.y);
	set_color(color_by_name("Green"));
	DrawArc(0.1, 0, 360);
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