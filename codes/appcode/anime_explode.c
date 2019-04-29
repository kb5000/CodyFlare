#include "animes.h"

typedef struct {
	DrawFuncHolder* dfh;
	int runTime;
	int expComp;
} ExplodeAnimePack;

Pos explode_lines(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	double para = dfh->extraPara;
	return new_pos(dfh->size * (cos(6 * t) - sin(2 * t)) * cos(8 * t + para), dfh->size * (sin(2 * t) + cos(4 * t)) * sin(6 * t + para));
}

void draw_explode(ExplodeAnimePack* eap) {
	DrawFuncHolder* dfh = eap->dfh;
	for (double r = 0; r < 2 * PI; r += PI / eap->expComp) {
		draw_function(dfh);
		dfh->rotate = r;
	}
	dfh->extraPara += 0.5;
	if (eap->runTime++ > 8) {
		free(eap->dfh);
		disable_me_in_timer();
	}
}


void draw_anime_explode(int id, Pos position, double size, int explodeComp) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	//double size = 0.5;
	*dfh = create_function_holder(explode_lines, position, new_pos(0.32 * size, 0.02 * size), size, 0, PI, 0.3, 0, color_by_name("Black"), 1, PI / 2);
	ExplodeAnimePack* eap = (ExplodeAnimePack*)malloc(sizeof(ExplodeAnimePack));
	eap->dfh = dfh;
	eap->runTime = 0;
	eap->expComp = explodeComp;
	add_func_to_timer(draw_explode, eap, 1, id, 10);
}