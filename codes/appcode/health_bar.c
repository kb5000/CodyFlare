#include "health_bar.h"
#include "imgui.h"
#include "graphics.h"
#include "timer.h"
#include "color.h"
#include <stdlib.h>

//double maxNum;
//double* num;
//
//static void show_health_bar_tick(void* unuseful) {
//	set_color(color_by_name("Black"));
//	drawRectangle(0.5, 6, 9, 0.2, 0);
//	set_color(color_by_name("Red"));
//	drawRectangle(0.5, 6, (1.0 - *num / maxNum) * 9, 0.2, 1);
//}
//
//void show_health_bar(double* hp, double maxHp) {
//	add_func_to_timer(show_health_bar_tick, NULL, 1, 4299887, -1);
//	num = hp;
//	maxNum = maxHp;
//}
//
//void remove_health_bar() {
//	remove_funcs_from_timer(4299887);
//}

void show_health_bar(double num, double maxNum) {
	set_color(color_by_name("Black"));
	drawRectangle(0.5, 6, 9, 0.2, 0);
	set_color(color_by_name("Red"));
	drawRectangle(0.5, 6, (num / maxNum) * 9, 0.2, 1);
}
