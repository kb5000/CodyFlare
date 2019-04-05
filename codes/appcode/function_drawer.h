#pragma once

#include "graphics.h"
#include "point.h"

typedef struct _My_Function_Holder {
	Pos (*func)(struct _My_Function_Holder* para);
	Pos originPosition, drawPositionBias;
	double size;
	double tNow, tMax, tStep;
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

///name: create_function_holder
///func: return a DrawFuncHolder
///para: func expects to return a Pos contains x and y using the data provided in its para, 
///      originPosition can be seen as the origin, drawPositionBias is the init position away from the origin,
///      size expects a positive number,
///      tNow expects the initial para t and it will be updated while drawing,
///      tMax expects the max para t, and tStep expects how much will the para t increase each time,
///      rotate expects the angle rotated
///visb: public
///warn: the para func dont need to consider the value of size and rotate, as it will be automatically caculated
DrawFuncHolder create_function_holder(
	Pos(*func)(DrawFuncHolder* para),
	Pos originPosition, Pos drawPositionBias,
	double size,
	double tNow, double tMax, double tStep,
	double rotate);
