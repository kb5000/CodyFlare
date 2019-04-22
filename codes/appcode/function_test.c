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

///中文翻译版：
///这是一个修改库的demo文件，里面展示了FunctionDrawer, Timer, Color, Point这些组件的用法
///要画一个函数，我们首先需要编写一个函数用于根据参数t计算出dx和dy，这里也就是calc_det函数
///当然，除了t以外，你也可以用其他的参数，比如这里用到了旋转角和全局tick（时钟滴答数）。
///之后，我们就可以调用draw_function或者draw_function_one_step来画一个函数了。
///为了画多个函数图像，又编写了一个函数tts，它是由定时器调用，它接受的是void*型，实际上是DrawFuncHolder*，
///但是为了让定时器使用，就必须改为void*
///只要把这个函数用add_func_to_timer添加即可

static double para = 62.8;
static int flag = 1;
static int n = 0;

Pos calc_det(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	int r = (int)(dfh->rotate * 360 / 6.283);
	//you can comment the below line to see another color mode
	set_color(color_by_hsl(r, (int)(t / 6.28 * 256), 160 - (int)(t / 6.28 * 32)));
	//you can change the formula as your wish to see what it will draw
	return new_pos(-sin(3 * t) * cos(4 * dfh->rotate + 3.1416 * 1.5 * 3),
					0.5 - 0.5 * sin(3 * t) * cos(para * t));
}

void tts(void* dds) {
	DrawFuncHolder* dfh = (DrawFuncHolder*)dds;
	Color c;
	//expand
	dfh->tMax = (dfh->tMax > 6 ? 6 : dfh->tMax + 0.1);
	//rotate a circle, drawing 90 times
	//remember to clear the rotate after drawing
	for (dfh->rotate = 0.02; dfh->rotate < 3.1416 * 2; dfh->rotate += 3.1416 / 45) {
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
	} else {
		flag = -flag;
		para += 0.1 * flag;
	}
	//We can use either of them to disable the function, recommand to use disable_me_in_timer()
	//If you just want to count like this, just pass to the timer
	if (n++ > 500) {
		remove_funcs_from_timer(1);
		//disable_me_in_timer();
	}
}

void test_of_function() {
	InitGraphics();
	//We must use malloc to create parameters if it will be passed by the timer
	DrawFuncHolder* dfh = (DrawFuncHolder*)malloc(sizeof(DrawFuncHolder));
	//paras: func to call, origin, bias, size, t start, t max, t step, rotate radius, color, pen size
	*dfh = create_function_holder(calc_det, new_pos(5, 3.5), new_pos(-0.0, -0), 0.9, 0, 1, 0.1, 0, color_by_name("Black"), 1, 0);
	//this should be called only once, best in the main function
	init_global_timer();
	//recommand to add this as the first function to call in the timer
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	//paras: func, para(must be malloced or NULL), tick between called(if this draws something, it should be 1),
	//       funcid, max call time(-1 means infinity)
	add_func_to_timer(tts, dfh, 1, 1, -1);
	//clear it in a long time interval, this can increase the performance
	//In fact, it is a GC(garbage collection) function
	add_func_to_timer(remove_invalid_funcs, NULL, 10, 3, -1);
	start_global_timer();
	//drawRectangle(5, 3.5, 2, 1.993, 0);
}

