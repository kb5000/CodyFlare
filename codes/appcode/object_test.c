
#include "graphics.h"
#include "timer.h"
#include "utility.h"
#include "vector.h"
#include "object_test.h"
#include <math.h>
#include <stdlib.h>
#include "animes.h"
#include "spline_interpolation.h"

void draw_bonus_enemy(Pos* t);

Pos dc(double x, double y, double k, double b)
{
	return new_pos(((1 - k * k)*x + 2 * k*y - 2 * k*b) / (1 + k * k), (k*k - 1)*y + 2 * k*x + 2 * b / (k*k + 1));
}

void test_of_object()
{
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
	//enemy1_drawer();
	hnew(Pos, pos);
	set_pos(pos, 5, 3.5);
	//add_func_to_timer(draw_player_plane, pos, 1, 1221, -1);
	//*pos = add_pos(*pos, new_pos(0.5, 0));
	//draw_basic_enemy(pos);
	//hnew(double, t);
	//*t = -PI / 4;
	//*pos = add_pos(*pos, new_pos(0.5, 0));
	add_func_to_timer(big_plane, pos, 1, 1221, -1);
	
}

void big_plane()
{
	double x0 = 4.0, y0 =5.0;
	double e = 0.6;
	Pos temp;

	Vector v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0+0.03*e, y0+0.2*e), &temp));
	calls(v, push, (temp = new_pos(x0+1.1*e, y0+3.6*e), &temp));
	Spline* sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0 + 1.1*e, y0 + 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x0+1.4*e, y0+3.55*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0 + 1.4*e, y0 + 3.55*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 1.1*e, y0 + 0.1*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	double x1 = x0 + 1.1*e, y1 = y0 + 0.1*e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x1, y1), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.2*e, y1 - 0.15*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.4*e, y1 - 0.35*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.6*e, y1 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.8*e, y1 - 1.0*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.7*e, y1 - 1.3*e), &temp));
	calls(v, push, (temp = new_pos(x1 + 0.3*e, y1 - 1.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.3*e, y1 - 1.8*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.9*e, y1 - 1.8*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.05*e, y1 - 1.78*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.2*e, y1 - 1.72*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.7*e, y1 - 1.32*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.9*e, y1 - 1.07*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 2.1*e, y1 - 0.5*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.8*e, y1 - 0.1*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 0.03*e, y0 + 0.2*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x0 + 1.2*e, y0 + 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 1.1*e, y1 - 1.7*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 1.25*e, y0 + 3.55*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.9*e, y1 - 1.8*e), &temp));
	calls(v, push, (temp = new_pos(x0 + 1.3*e, y0 + 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x1 - 0.7*e, y1 - 1.85*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	double x2 = x0 + 0.33*e, y2 = y0 - 0.15*e  ;

	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x2, y2), &temp));
	calls(v, push, (temp = new_pos(x2 - 0.8*e, y2 - 0.2*e), &temp));
	calls(v, push, (temp = new_pos(x2 - 0.8*e, y2 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x2 - 0.1*e, y2 - 1.1*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.3*e, y2 - 1.1*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.3*e, y2 - 1.1*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.99*e, y2 - 0.9*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.92*e, y2 - 0.5*e), &temp));
	calls(v, push, (temp = new_pos(x2 + 0.33*e, y2 - 0.02*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	

	double x3 = x0 - 0.52 * e, y3 = y0 - 0.42 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x3, y3), &temp));
	calls(v, push, (temp = new_pos(x3 - 3 * e, y3 - 1.6*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 3 * e, y3 - 2.6*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 0.7 * e, y3 - 3.52*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	double x4 = x0 + 1.36 * e, y4 = y0 - 1.0 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x4, y4), &temp));
	calls(v, push, (temp = new_pos(x4 + 2.3 * e, y4 - 2.2*e), &temp));
	calls(v, push, (temp = new_pos(x4 + 2.3 * e, y4 - 3.6*e), &temp));
	calls(v, push, (temp = new_pos(x4 - 1.2 * e, y4 - 3.1*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	double x5 = x0 + 1.1 * e, y5 = y0 - 1.6 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x5, y5), &temp));
	calls(v, push, (temp = new_pos(x5 + 1.0 * e, y5 - 1.7*e), &temp));
	calls(v, push, (temp = new_pos(x5 - .55 * e, y5 - 1.75 * e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	double x52 = x0 - 0.6 * e,y52 = y0 - 1.2 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x52, y52), &temp));
	calls(v, push, (temp = new_pos(x52 - 1.3 * e, y52 - 1.2*e), &temp));
	calls(v, push, (temp = new_pos(x52 - 0.33 * e, y52 - 1.9*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	double x6 = x0 - 0.3 * e, y6 = y0 - 1.45 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x6, y6), &temp));
	calls(v, push, (temp = new_pos(x6 - 0.5 * e, y6 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x52 - 0.38 * e, y52 - 1.9*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 0.7 * e, y3 - 3.52*e), &temp));
	calls(v, push, (temp = new_pos(x3 - 0.8 * e, y3 - 4.32*e), &temp));
	calls(v, push, (temp = new_pos(x6+0.16*e, y6), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	double x7 = x0 + 0.8 * e, y7 = y0 - 1.7 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x7, y7), &temp));
	calls(v, push, (temp = new_pos(x7 + 0.15 * e, y7 - 0.8*e), &temp));
	calls(v, push, (temp = new_pos(x5 - 0.5 * e, y5 - 1.7 * e), &temp));
	calls(v, push, (temp = new_pos(x4 - 1.1 * e, y4 - 3.1*e), &temp));
	calls(v, push, (temp = new_pos(x4 - 1.5 * e, y4 - 4.0*e), &temp));
	calls(v, push, (temp = new_pos(x7-0.2*e, y7+0.1*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);

	MovePen(x7-1.64*e, y7-1.8*e);
	DrawLine(0.4*e, -0.35*e);
	DrawLine(0.55*e, 0.05*e);
	MovePen(x7 - 0.5*e, y7 - 0*e);
	DrawLine(-0.5*e, -2.15*e);
	MovePen(x7 - 0.73*e, y7 + 0.02 * e);
	DrawLine(-0.66*e, -2.03*e);

	double x8 = x0 - 3.87 * e, y8 = y0 - 2.5 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x8+0.08*e, y8+.22*e), &temp));
	calls(v, push, (temp = new_pos(x8 - 0.35 * e, y8 - 0.6*e), &temp));
	calls(v, push, (temp = new_pos(x8-0.5*e, y8-2.8*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	DrawLine(e*0.7, e * 2.36);

	double x9 = x0 + 4.06 * e, y9 = y0 - 4.26 * e;
	v = gen_empty_vector(Pos);
	calls(v, push, (temp = new_pos(x9-0.02*e , y9+0.28*e ), &temp));
	calls(v, push, (temp = new_pos(x9 + 0.05 * e, y9 - 0.8*e), &temp));
	calls(v, push, (temp = new_pos(x9 - 0.9 * e, y9 - 2.7*e), &temp));
	sp = create_spline(&v, NULL, 0);
	draw_spline(sp);
	DrawLine(e*0.5, e * 2.34);

	destroy_spline(sp);
	free(sp);

}

