#include "spline_test.h"
#include "graphics.h"
#include "timer.h"
#include "utility.h"
#include "vector.h"
#include "object_test.h"
#include <math.h>
#include <stdlib.h>

void draw_enemy_t(double* t);
void test_of_object()
{
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
	//enemy1_drawer();
	Myplane();
	enemy2_drawer();
	hnew(double, t);
	*t = -PI / 4;
	add_func_to_timer(draw_enemy_t, t, 1, 1221, -1);
}

