#include "input_test.h"
#include "graphics.h"
#include "input.h"
#include "imgui.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

static char buffer[20];

void key_process(void* n, int event) {
	int* num = (int*)n;
	if (event) {
		(*num)++;
		sprintf(buffer, "%d", *num);
	}
}

void draw_and_update(void* unuseful) {
	//sprintf(buffer, "%d", k);
	drawLabel(0.2, 0.2, buffer);
	button(12, 2, 2, 0.8, 0.3, "Click");
	
}

void test_of_input() {
	InitGraphics();
	init_input();
	int* nums = (int*)malloc(sizeof(int));
	*nums = 0;
	add_to_key_process(' ', key_process, nums);
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 1, -1);
	add_func_to_timer(draw_and_update, NULL, 1, 1, -1);
	start_global_timer();
}