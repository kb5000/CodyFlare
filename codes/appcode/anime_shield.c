#include "animes.h"

#define PI 3.1415926
static const double rotateRate = 0.01;
static const int ticksBetweenDraw = 1;

Pos draw_curve_sin(DrawFuncHolder* dfh);
Pos draw_curve_circle(DrawFuncHolder* dfh);

void sins_drawer(void* dfhv) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dfhv;
	draw_function(dfh);
	dfh->rotate += rotateRate;
}

void draw_anime_shield(int id, Pos position, double size, int existTicks) {
	DrawFuncHolder* dfh[6];
	for (int i = 0; i < 6; i++) {
		dfh[i] = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	}
	for (int i = 0; i < 3; i++) {
		*dfh[i] = create_function_holder(draw_curve_sin, position, new_pos(size * 1, 0), size * 0.5, 0, 2 * PI, 0.02, 0, color_by_name("Red"), 2);
	}
	for (int i = 3; i < 6; i++) {
		*dfh[i] = create_function_holder(draw_curve_circle, position, new_pos(size * 1.26, size * -0.06), size * 1.26, 0, 2 * PI, 0.1, 0, color_by_name("Black"), 2);
	}
	dfh[1]->rotate = 2 * PI / 9;
	dfh[2]->rotate = 4 * PI / 9;
	dfh[1]->color = color_by_name("Green");
	dfh[2]->color = color_by_name("Blue");
	dfh[4]->color = color_by_name("Blue");
	dfh[5]->color = color_by_name("Red");
	dfh[4]->drawPositionBias = new_pos(size * 0.747, size * -0.04);
	dfh[5]->drawPositionBias = new_pos(size * 1.04, size * -0.06);
	dfh[4]->size = size * 0.75;
	dfh[5]->size = size * 1.03;
	add_func_to_timer(sins_drawer, dfh[0], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(sins_drawer, dfh[1], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(sins_drawer, dfh[2], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(draw_function, dfh[3], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(draw_function, dfh[4], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(draw_function, dfh[5], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
}

Pos draw_curve_sin(DrawFuncHolder* dfh) {
	Pos res;
	double t1 = cos(dfh->tNow);
	double t2 = cos(6 * dfh->tNow);
	double t3 = sin(dfh->tNow);
	double t4 = sin(6 * dfh->tNow);
	res.x = -3 * t2 * t1 + (0.5 * t4 - 2) * t3;
	res.y = -3 * t2 * t3 + (2 - 0.5 * t4) * t1;
	return res;
}

Pos draw_curve_circle(DrawFuncHolder* dfh) {
	return new_pos(-sin(dfh->tNow), cos(dfh->tNow));
}


