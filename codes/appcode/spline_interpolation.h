#pragma once
#include "utility.h"
#include "function_drawer.h"
#include "color.h"
#include "vector.h"

typedef struct {
	Vector points;
	Vector parameters;
	Color (*color_fun)(DrawFuncHolder* dfh);
	int isClosed;
} Spline;

/// name: create_spline
/// func: return a spline drawer by points provided, you can customize your color
/// para: points expects a Vector contains Pos, and the order of points matters, 
///       color_fun expects a function, if you want to just black, you can pass NULL
///       isClosed means if it is a closed curve
/// visb: public
Spline* create_spline(Vector* points, Color color_fun(DrawFuncHolder* dfh), int isClosed);

/// name: destroy_spline
/// func: destroy a spline and release memory
/// para: spline expects a valid Spline*
/// visb: public
void destroy_spline(Spline* spline);

/// name: draw_spline
/// func: draw a curve by points provided, you can add it into the timer
/// para: spline expects a Spline created by create_spline
/// visb: public
void draw_spline(Spline* spline);


