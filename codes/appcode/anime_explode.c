#include "animes.h"

Pos explode_lines(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	double para = dfh->extraPara;
	return new_pos(dfh->size * (cos(6 * t) - sin(2 * t)) * cos(8 * t + para), dfh->size * (sin(2 * t) + cos(4 * t)) * sin(6 * t + para));
}

void draw_explode(void* drawFunctionHolder) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)drawFunctionHolder;
	for (double r = 0; r < 2 * PI; r += PI / 3) {
		draw_function(dfh);
		dfh->rotate = r;
	}
	dfh->extraPara += 0.5;
}


void draw_anime_explode(int id, Pos position, double size) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	//double size = 0.5;
	*dfh = create_function_holder(explode_lines, position, new_pos(0.32 * size, 0.02 * size), size, 0, PI, 0.3, 0, color_by_name("Black"), 1, PI / 2);
	add_func_to_timer(draw_explode, dfh, 1, id, 9);
}