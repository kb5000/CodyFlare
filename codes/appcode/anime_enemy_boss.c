#include "animes.h"

static double para = 62.8;
static int flag = 1;
static int n = 0;

Pos boss_body_calculate(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	int r = (int)(t * para - 20);
	set_color(color_by_hsl(r, (int)(t / 6.28 * 256), 160 - (int)(t / 6.28 * 32)));
	//you can change the formula as your wish to see what will draw
	return new_pos(-1 * sin(3 * t) * cos(4 * dfh->rotate + PI * 1.5 * 3),
				   0.5 - 0.5 * sin(3 * t) * cos(para * t));
}

void boss_drawer(void* dds) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dds;
	Color c;
	//rotate a circle, drawing 90 times
	//remember to clear the rotate after drawing
	for (dfh->rotate = PI / 4 * 7 + 0.05; dfh->rotate < PI/  4 * 9 ; dfh->rotate += PI / 45) {
		draw_function(dfh);
		//need to clear the t and the bias to redraw it
		dfh->tNow = 0;
		dfh->drawPositionBias = new_pos(0, 0);
	}
	//the para runs from 65.6 to 60.8
	if (para < 65.6 && para > 60.8) {
		para += 0.1 * flag;
		//uncomment set_color in calc_det to see the effect
		c = color_by_real(0.6 - (para - 60.7) / 4.8 * 0.5, sin(para), cos(2 * para));
		dfh->color = c;
	}
	else {
		flag = -flag;
		para += 0.1 * flag;
	}
}

void draw_anime_enemy_boss(int id, Pos position, double size, int existTicks) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	*dfh = create_function_holder(boss_body_calculate, position, new_pos(0, 0), size, 0, 6, 0.2, 0, color_by_name("Black"), 1, 0);
	add_func_to_timer(boss_drawer, dfh, 1, id, existTicks);
}
