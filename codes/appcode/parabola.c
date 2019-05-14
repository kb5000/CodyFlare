#include "animes.h"


static Color default_color_fun(DrawFuncHolder* dfh) {
	return color_by_name("Black");
}

static Pos pa, pb;
static Color(*color_fun)(DrawFuncHolder* dfh) = default_color_fun;


Pos parabola_drawer(DrawFuncHolder* dfh) {
	color_fun(dfh);
	return new_pos(pa.x * dfh->tNow + pb.x, pa.y * dfh->tNow + pb.y);
}

void draw_one_parabola(ParabolaHolder* ph) {
	if (ph->color_fun) color_fun = ph->color_fun;
	pa = ph->a;
	pb = ph->b;
	draw_function(&ph->dfh);
}

ParabolaHolder create_parabola(int id, Pos p1, Pos p2, Pos p3, Color color_fun(DrawFuncHolder* dfh), int penSize) {
	ParabolaHolder ph = {
		id,
		create_function_holder(parabola_drawer, p1, new_pos(0, 0),
			1, 0, 1, 0.02, 0, color_by_name("Black"), penSize, 0),
		color_fun,
		add_pos(add_pos(pos_mut(p1, 4), pos_mut(p2, -8)), pos_mut(p3, 4)),
		add_pos(add_pos(pos_mut(p1, -3), pos_mut(p2, 4)), pos_mut(p3, -1)),
		p1, p2, p3,
	};
	return ph;
}

void draw_parabola(ParabolaHolder ph, int existInteval) {
	//hnew(ParabolaHolder, php);
	//*php = ph;
	//add_func_to_timer(draw_one_parabola, php, 1, ph.id, existInteval);
	draw_one_parabola(&ph);
}