#include "slide_bar.h"
#include "ui_test.h"
#include "anime_test.h"
#include "imgui.h"
#include <stdio.h>
#include "timer.h"
#include "input.h"
#include "save.h"
#include <stdlib.h>
#include "listbox.h"

static char labelText[64];

void slide_bar_test_call(double* num) {
	slide_bar(new_pos(1, 1), new_pos(1.6, 0.5), num);
	MouseKeys m = get_mouse_key();
	sprintf(labelText, "num is %f, on %f, %f, ed %d", *num, m.pos.x, m.pos.y, mouse_at_edge());
	drawLabel(0.1, 0.1, labelText);
	move_by_dir_key((Pos*)num, new_pos(0.02, 0));
	if (*num > 1) *num = 1;
	if (*num < 0) *num = 0;
}

void test_of_slide_bar() {
	common_anime_test_init();
	hnew(double, n);
	*n = 0.2;
	add_func_to_timer(slide_bar_test_call, n, 1, 1, -1);
}

void test_of_list_box() {
	common_anime_test_init();
	ListHandler lh = explore_files();
	show_list_box(1, lh, new_pos(1, 1), 0);
}