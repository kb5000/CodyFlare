#include "animes.h"

#define PI 3.1415926

Pos draw_curve_sin(DrawFuncHolder* dfh);
Pos draw_curve_circle(DrawFuncHolder* dfh);

void sins_drawer(void* dfhv) {
	
}


void draw_anime_shield(int id, Pos position, double size) {

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
