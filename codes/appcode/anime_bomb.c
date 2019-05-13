#include "animes.h"

typedef struct {
	DrawFuncHolder* dfh;
	double tickPara;
	double speed;
	int runTime;
	void (*explode_handler)(Pos bombPos);
} BombAnimePack;

static double tickPara = 0.2;

Pos anime_bomb_drawer(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	Pos res = {
		-dfh->extraPara * sin(t) * sin(10 * t) * (0.5 * tickPara),
		dfh->extraPara * cos(t) * cos(10 * t) * (0.5 * tickPara)
	};
	return res;
}

void anime_bomb_booster(BombAnimePack* bap) {
	DrawFuncHolder* dfh = bap->dfh;
	//This program is not parallel, so it wont cause data race
	tickPara = bap->tickPara;
	for (int t = 0; t < 6; t++) {
		for (double s = tickPara; s < 2.4; s += 0.2) {
			dfh->extraPara = 2 * s;
			dfh->drawPositionBias = add_pos(dfh->drawPositionBias, new_pos(dfh->size * 0.1, 0));
			draw_function(dfh);
		}
		dfh->rotate += PI / 3;
		dfh->drawPositionBias = new_pos(0.1, 0);
	}
	dfh->rotate = PI / 6;
	if (bap->explode_handler && tickPara < -0.62 && tickPara > -1.2) {
		bap->explode_handler(dfh->originPosition);
		bap->explode_handler = NULL; //only call once
	}
	if (tickPara < 0.4 && tickPara > -0.2) {
		bap->tickPara -= 0.02 * bap->speed;
	} else if (tickPara > -2.4) {
		bap->tickPara -= 0.3 * bap->speed;
	}
	if (bap->runTime++ > 200 / bap->speed) {
		free(dfh);
		disable_me_in_timer();
	}
}

void draw_anime_bomb(int id, Pos position, double size, double speed, Color color, void explode_handler(Pos bombPos)) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	*dfh = create_function_holder(anime_bomb_drawer, position, new_pos(0, 0), size, 0, PI / 4, 0.02,
								  PI / 6, color, 1, 0);
	//tickPara = 0.2;
	BombAnimePack* bap = (BombAnimePack*)malloc(sizeof(BombAnimePack));
	bap->dfh = dfh;
	bap->tickPara = 2.4;
	bap->runTime = 0;
	bap->speed = speed;
	bap->explode_handler = explode_handler;
	add_func_to_timer(anime_bomb_booster, bap, 1, id, 50);
}