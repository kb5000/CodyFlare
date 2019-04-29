#include "animes.h"

Pos anime_bomb_drawer(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	Pos res = {
		0.2 * (cos(t) - sin(t)) * exp(t / PI / 16),
		0.2 * (sin(t) + cos(t)) * exp(t / PI / 16)
	};
	return res;
}

void draw_anime_bomb(int id, Pos position, double size, int existTicks) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	*dfh = create_function_holder(anime_bomb_drawer, position, new_pos(0, 0), size, 0, 18 * PI, 0.1, 
								  0, color_by_name("Black"), 1, 0);
	add_func_to_timer(draw_function, dfh, 1, id, existTicks);
}