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

void draw_function(DrawFuncHolder* drawFuncHolder);

void draw_function_one_step(void* drawFuncHolder);
