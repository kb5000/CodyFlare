#include "spline_test.h"
#include "spline_interpolation.h"
#include "timer.h"
#include "utility.h"
#include "vector.h"

void test_of_spline() {
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
	//Below is the code for generate curves
	Vector v = gen_empty_vector(Pos);
	//This is because vector only receive pointers
	Pos temp;
	calls(v, push, (temp = new_pos(2, 6), &temp));
	calls(v, push, (temp = new_pos(3.3, 1.8), &temp));
	calls(v, push, (temp = new_pos(4, 1), &temp));
	calls(v, push, (temp = new_pos(4.7, 1.8), &temp));
	calls(v, push, (temp = new_pos(6, 6), &temp));
	//create a spline, you may want to customize you color function
	Spline* sp = create_spline(&v, NULL, 1);
	add_func_to_timer(draw_spline, sp, 1, 1, -1);
}