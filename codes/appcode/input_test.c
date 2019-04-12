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

void key_process(void* n, int event) {
	if (event) spaceNum++;
}

void draw_and_update(void* unuseful) {
	MouseKeys ms = get_mouse_key();
	sprintf(buffer, "%d, M(%lf, %lf)", spaceNum, ms.pos.x, ms.pos.y);
	set_color(color_by_rgb(30, 34, 81));
	drawLabel(0.2, 0.2, buffer);
	//if (ms.middle == )
	if (button(Unique_ID("mybut"), 2, 2, 0.8, 0.3, "Click")) {
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