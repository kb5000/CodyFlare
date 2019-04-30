#pragma once
#include "utility.h"
#include "function_drawer.h"
#include "color.h"
#include "vector.h"

typedef struct {
	Vector points;
	Vector parameters;
	Color (*color_fun)(DrawFuncHolder* dfh);
	double t;
} Spline;

///name: create_spline
///func: return a spline drawer by points provided, you can customize your color
///para: points expects a Vector contains Pos, and the order of points matters, 
///      color_fun expects a function, if you want to just black, you can pass NULL
Spline* create_spline(Vector* points, Color color_fun(DrawFuncHolder* dfh));

///name: draw_spline
///func: draw a curve by points provided, you can add it into the timer
///para: spline expects a Spline created by create_spline
void draw_spline(Spline* spline);


