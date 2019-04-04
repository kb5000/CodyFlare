#pragma once

#include "graphics.h"
#include "point.h"

typedef struct _My_Function_Holder {
	Pos (*func)(struct _My_Function_Holder* para);
	Pos originPosition, drawPositionBias;
	double size;
	double tNow, tStep, tMax;
	double rotate;
} DrawFuncHolder;

///name: draw_function
///func: draw a function using the infomation
///para: drawFuncHolder expects a pointer refers to a DrawFuncHolder, which contains right info
///visb: public
void draw_function(DrawFuncHolder* drawFuncHolder);

///name: draw_function_one_step
///func: draw a piece of the function
///para: drawFuncHolder expects a pointer refers to a DrawFuncHolder, which contains right info
///visb: public
///warn: it should be called by the timer so the drawFuncHolder should be malloced, not a global variable
void draw_function_one_step(void* drawFuncHolder);
