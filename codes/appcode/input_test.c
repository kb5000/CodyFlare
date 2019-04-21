#include "input_test.h"
#include "graphics.h"
#include "input.h"
#include "imgui.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "color.h"

static char buffer[32];
static int spaceNum = 0;
static Pos pos = {2, 2};

void key_process(void* n, int event) {
	if (event) spaceNum++;
}

void draw_and_update(void* unuseful) {
	MouseKeys ms = get_mouse_key();
	sprintf(buffer, "%d, M(%lf, %lf), %d", spaceNum, ms.pos.x, ms.pos.y, ms.middle);
	set_color(color_by_rgb(30, 34, 81));
	drawLabel(0.2, 0.2, buffer);
	const double rate = 0.1;
	if (ms.middle == 3) {
		pos.y += 5 * rate;
		reset_mouse_key(2);
	}
	if (ms.middle == 4) {
		pos.y -= 5 * rate;
		reset_mouse_key(2);
	}
	DirKeys d = get_dir_key();
	if (d.down == 0) pos.y -= rate;
	if (d.up == 0) pos.y += rate;
	if (d.left == 0) pos.x -= rate;
	if (d.right == 0) pos.x += rate;
	if (button(Unique_ID("mybut"), pos.x, pos.y, 0.8, 0.3, "Click")) {
		drawLabel(0.2, 0.8, "clicked!");
	}
}

void test_of_input() {
	InitGraphics();
	init_input();
	init_global_timer();
	add_to_key_process(' ', key_process, NULL);
	add_func_to_timer(auto_clear_display, NULL, 1, 1, -1);
	add_func_to_timer(draw_and_update, NULL, 1, 1, -1);
	start_global_timer();
}