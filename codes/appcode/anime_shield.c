#include "animes.h"
#include "extgraph.h"
#include "imgui.h"
#include "random.h"
#include "input.h"

static double rotateRate = 0.0;
static const int ticksBetweenDraw = 1;

Pos draw_curve_sin(DrawFuncHolder* dfh);
Pos draw_curve_circle(DrawFuncHolder* dfh);

void sins_drawer(void* dfhv) {
	DrawFuncHolder dfh = *(DrawFuncHolder*)dfhv;
	if (dfh.extraPara > 0.5) {
		dfh.rotate += rotateRate;
	} else {
		dfh.rotate -= rotateRate;
	}
	draw_function(&dfh);
}

void font_shower(Pos* pos) {
	if (pos->x < 0) {
		drawLabel(-pos->x, pos->y, "生存模式");
	} else {
		drawLabel(pos->x, pos->y, "开始游戏");
	}
}

void draw_sins(DrawFuncHolder dfh[3]) {
	sins_drawer(&dfh[0]);
	sins_drawer(&dfh[1]);
	sins_drawer(&dfh[2]);
	//rotateRate += RandomReal(-0.015, 0.015);
	MouseKeys mk = get_mouse_key();
	rotateRate = mk.pos.x / 3;
}

void draw_anime_shield(int id, Pos position, double size, int existTicks, int mode) {
	DrawFuncHolder* dfh[6];
	for (int i = 0; i < 6; i++) {
		dfh[i] = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	}
	for (int i = 0; i < 3; i++) {
		*dfh[i] = create_function_holder(draw_curve_sin, position, new_pos(size * 1, 0), size * 0.5, 0, 2 * PI, 0.02, 0, color_by_name("Red"), 2, mode);
	}
	for (int i = 3; i < 6; i++) {
		*dfh[i] = create_function_holder(draw_curve_circle, position, new_pos(size * 1.26, size * -0.06), size * 1.26, 0, 2 * PI, 0.1, 0, color_by_name("Black"), 2, 0);
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
	DrawFuncHolder* sins = (DrawFuncHolder*)malloc(3 * sizeof(DrawFuncHolder));
	sins[0] = *dfh[0];
	sins[1] = *dfh[1];
	sins[2] = *dfh[2];
	add_func_to_timer(draw_sins, sins, ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	//add_func_to_timer(sins_drawer, dfh[0], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	//add_func_to_timer(sins_drawer, dfh[1], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	//add_func_to_timer(sins_drawer, dfh[2], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(draw_function, dfh[3], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(draw_function, dfh[4], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	add_func_to_timer(draw_function, dfh[5], ticksBetweenDraw, id, existTicks / ticksBetweenDraw);
	hnew(Pos, pos);
	*pos = sub_pos(position, new_pos(0.33, 0.05));
	if (mode) pos->x = -pos->x;
	add_func_to_timer(font_shower, pos, 1, 93939, -1);
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


