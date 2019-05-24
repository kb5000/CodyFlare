#include "function_drawer.h"
#include <math.h>
#include "graphics.h"
#include "imgui.h"
#include "timer.h"
#include <stdlib.h>
#include "start_page.h"
#include "ingame.h"
#include "extgraph.h"

static int flag = 1;
static int n = 0;
Pos org;

Pos calc_det_s(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	//int r = (int)(dfh->rotate * 360 / 6.283);
	double para = dfh->extraPara;
	Pos pos = {GetCurrentX(), GetCurrentY()};
	Pos p = rect_to_polar(sub_pos(org, pos));
	int colrh = (int)(p.y * 0.2 * p.x * 180 / PI);
	int colrs = (int)((p.x - 5) * (p.x - 5) * 256);
	set_color(color_by_hsl(colrh < 0 ? 360 - colrh : colrh, colrs < 90 ? 90 : colrs, 128));
	return new_pos(-sin(3 * t) * cos(4 * dfh->rotate + PI / 3),
					0.5 - 0.5 * sin(3 * t) * cos(para * t));
}

void tts_s(void* dds) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dds;
	Color c;
	double para = dfh->extraPara;
	org = new_pos(6 * cos((para - 55.9) / 6.9 * PI) + 6, 4.2 * sin((para - 55.9) / 6.9 * PI) + 4.2);

	for (dfh->rotate = 0.02; dfh->rotate < 3.1416 * 2; dfh->rotate += 3.1416 / 45) {
		draw_function(dfh);
		//need to clear the t and the bias to redraw it
		dfh->tNow = 0;
		dfh->drawPositionBias = new_pos(0, 0);
	}
	//the para runs from 65.6 to 60.8
	//dfh->extraPara += 0.1;
	//char par[32];
	//sprintf(par, "ex: %f", para);
	//drawLabel(1, 1, par);

	if (para < 62.8) {
		dfh->extraPara += 0.1 * flag;
		//uncomment set_color in calc_det to see the effect
		c = color_by_real(0.6 - (para - 60.7) / 4.8 * 0.2, sin(para), cos(para));
		dfh->color = c;
	} /*else {
		flag = -flag;
		dfh->extraPara += 0.1 * flag;
	}*/
	//We can use either of them to disable the function, recommand to use disable_me_in_timer()
	//If you just want to count like this, just pass to the timer
	if (n++ > 90) {
		//remove_funcs_from_timer(1);
		//disable_me_in_timer();
	}
}

void show_start_page() {
	//We must use malloc to create parameters if it will be passed by the timer
	//DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	hnew(DrawFuncHolder, dfh);
	//paras: func to call, origin, bias, size, t start, t max, t step, rotate radius, color, pen size, extra para
	*dfh = create_function_holder(calc_det_s, new_pos(5, 3.5), new_pos(0, 0), 0.9, 0, 13, 0.1, 0, color_by_name("Black"), 1, 55.9);
	add_func_to_timer(tts_s, dfh, 1, Unique_ID("BossAnime"), 900);
	//clear it in a long time interval, this can increase the performance
}
