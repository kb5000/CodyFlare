#include "function_test.h"
#include "function_drawer.h"
#include <math.h>
#include "graphics.h"
#include "imgui.h"
#include "timer.h"
#include <stdlib.h>

///This file is also a demo to display how the function_drawer works.
///We use the new color system to show it.
///First, we need a function "Pos calc_det(DrawFuncHolder* dfh)", which calculates 
///the dx and dy by the parameter. We often use dfh->tNow, but you can use other infomation 
///such as rotate to generate a more complex function. If this is still not enough, 
///you should use global variable or static variable (not recommand for it cant be 
///easily cleared to the initial status).
///Using this we can draw one function, this is enough in most cases, but if you want to draw
///more than one functions, you should use a handler function "void tts(void* tts)". The parameter
///is in the type of DrawFuncHolder, but we will call it by the timer, so we must use void* type.
///You can update the infomation either in tts or in calc_det. We recommand to update in tts unless
///it is ralated to the parameter tNow, for it will reduce the time to process.
///At last, you can simply add it to the timer list.


static double para = 62.8;
static int flag = 1;
static int n = 0;

Pos calc_det(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	int r = (int)(dfh->rotate * 360 / 6.283);
	set_color(color_by_hsl(r, (int)(t / 6.28 * 256), 160 - (int)(t / 6.28 * 32)));
	//you can change the formula as your wish to see what will draw
	return new_pos(-1 * sin(3 * t) * cos(4 * dfh->rotate + 3.1416 * 1.5 * 3),
				   0.5 - 0.5 * sin(3 * t) * cos(para * t));
}

void tts(void* dds) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dds;
	Color c;
	//rotate a circle, drawing 90 times
	//remember to clear the rotate after drawing
	for (dfh->rotate = 0.02; dfh->rotate < 3.1416 * 2 ; dfh->rotate += 3.1416 / 45) {
		draw_function(dfh);
		//need to clear the t and the bias to redraw it
		dfh->tNow = 0;
		dfh->drawPositionBias = new_pos(0, 0);
	}
	//the para runs from 65.6 to 60.8
	if (para < 65.6 && para > 60.8) {
		para += 0.1 * flag;
		//uncomment set_color in calc_det to see the effect
		c = color_by_real(0.6 - (para - 60.7) / 4.8 * 0.2, sin(para), cos(para));
		dfh->color = c;
	}
	else {
		flag = -flag;
		para += 0.1 * flag;
	}
	//We recommand to use this to disable a function, dont use others like remove_funcs_from_timer
	if (n++ > 500) {
		disable_me_in_timer();
	}
}

void test_of_function() {
	InitGraphics();
	//We must use malloc to create parameters if it will be passed by the timer
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	//paras: func to call, origin, bias, size, t start, t max, t step, rotate radius, color, pen size
	*dfh = create_function_holder(calc_det, new_pos(5, 3.5), new_pos(-0.0, -0), 0.9, 0, 6, 0.1, 0, color_by_name("Black"), 1);
	//this should be called only once, best in the main function
	init_global_timer();
	//recommand to add this as the first function to call in the timer
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	//paras: func, para(must be malloced or NULL), tick between called(if this draws something, it should be 1),
	//       funcid, max call time(-1 means infinity)
	add_func_to_timer(tts, dfh, 1, 1, -1);
	//clear it in a long time interval, this can increase the performance
	//In fact, it is a GC(garbage collection) function
	add_func_to_timer(remove_invalid_funcs, NULL, 100, 3, -1);
	start_global_timer();
	//drawRectangle(5, 3.5, 2, 1.993, 0);
}

