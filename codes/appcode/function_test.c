#include "function_test.h"
#include "function_drawer.h"
#include <math.h>
#include "graphics.h"
#include "imgui.h"
#include "timer.h"
#include <stdlib.h>

Pos funcCircle(DrawFuncHolder* dfh) {
	return new_pos(2 * cos(dfh->tNow), sin(dfh->tNow));
}

void tts(void* dds) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dds;
	draw_function_one_step(dfh);
	if (dfh->tNow >= dfh->tMax && dfh->rotate < 3) {
		dfh->tNow = 0;
		dfh->rotate += 0.1;
		dfh->drawPositionBias = new_pos(-0.1, -1);
	}
}

void test_of_function() {
	InitGraphics();
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	*dfh = create_function_holder(funcCircle, new_pos(5, 3.5), new_pos(-0.1, -1), 0.1, 0, 6.28, 0.1, 0);
	draw_function(dfh);
	
	init_global_timer();
	add_func_to_timer(tts, dfh, 1, 1, -1);
	start_global_timer();
	//drawRectangle(5, 3.5, 2, 1.993, 0);
	
}

