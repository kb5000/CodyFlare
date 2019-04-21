#include "missile_test.h"
#include "missile.h"
#include "timer.h"
#include "graphics.h"
#include "input.h"
#include "imgui.h"

void bb(int id, Pos pos) {

}

static Pos b = {5, 2};

void lanunch_missile(void* unuseful) {
	MouseKeys m = get_mouse_key();
	if (m.left == 2) {
		show_missile(m.pos, b, 100, color_by_name("Red"), 0.2, -2.5, 70, bb);
		reset_mouse_key(1);
	}
	if (m.right == 2) {
		b = m.pos;
		reset_mouse_key(3);
	}
}

void test_of_missile() {
	InitGraphics();
	init_global_timer();
	init_input();
	add_func_to_timer(auto_clear_display, 0, 1, 76760, -1);
	add_func_to_timer(lanunch_missile, 0, 1, -1564, -1);
	//show_missile(new_pos(5, 3.5), new_pos(5, 2), 10, color_by_name("Red"), 0.1, -1.5, 100, bb);
	add_func_to_timer(remove_invalid_funcs, 0, 30, 12, -1);
	start_global_timer();
}