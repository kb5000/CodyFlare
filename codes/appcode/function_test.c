
#include "function_test.h"
#include "function_drawer.h"
#include <math.h>
#include "graphics.h"
#include "imgui.h"
#include "timer.h"
#include <stdlib.h>


static double para = 62.8;
static int flag = 1;
static int flagb = 1;

Pos funcCircle(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	return new_pos(-1 * sin(3 * t) * cos(4 * dfh->rotate + 3.1416 * 1.5 * 3),
				   0.5 - 0.5 * sin(3 * t) * cos(para * t));
}

void tts(void* dds) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dds;
	for (; dfh->rotate < 3.1416 * 2 ; dfh->rotate += 3.1416 / 45) {
		draw_function(dfh);
		//if (dfh->tNow >= dfh->tMax && dfh->rotate < 3.1416 * 2) {
		dfh->tNow = 0;
			//dfh->rotate += 3.1415926 / 45;
		dfh->drawPositionBias = new_pos(0, 0);
		//}
	}
	dfh->rotate = 0.02;
	//if (count % )
	if (para < 65.6 && para >= 60.8) para += 0.1 * flag;
	else {
		flag = -flag;
		para += 0.1 * flag;
	}
	//para = 31.4;
	//if (dfh->tMax < 6 && dfh->tMax >= 1.3) dfh->tMax += 0.2 * flag;
	//else {
	//	flag = -flag;
	//	dfh->tMax += 0.2 * flag;
	//}

}

void test_of_function() {
	InitGraphics();
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	*dfh = create_function_holder(funcCircle, new_pos(5, 3.5), new_pos(-0.0, -0), 0.9, 0, 6, 0.1, 0, "Black", 1);
	//draw_function(dfh);
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(tts, dfh, 1, 1, -1);
	start_global_timer();
	//drawRectangle(5, 3.5, 2, 1.993, 0);

}

