#include "spline_interpolation.h"
#include <math.h>
#include <stdlib.h>

typedef struct {
	double coeffx[3], coeffy[3];
} PolyCoeff;

static Color default_color_fun(DrawFuncHolder* dfh) {
	return color_by_name("Black");
}

static Color(*current_color_func)(DrawFuncHolder* dfh) = default_color_fun;
static PolyCoeff currentPoly;

Pos spline_drawer(DrawFuncHolder* dfh) {
	//call color func to change color, you should use extraPara + tNow 
	set_color(current_color_func(dfh));
	double t = dfh->tNow;
	//Use t to generate a * t^2 + b * t + c
	return new_pos(currentPoly.coeffx[0] * t * t + currentPoly.coeffx[1] * t + currentPoly.coeffx[2],
				   currentPoly.coeffy[0] * t * t + currentPoly.coeffy[1] * t + currentPoly.coeffy[2]);
}

void draw_spline(Spline* spline) {
	hnew(DrawFuncHolder, dfh);
	*dfh = create_function_holder(spline_drawer, *(Pos*)calls(spline->points, at, 1), new_pos(0, 0),
								  1, 0, 0.5, 0.02, 0, color_by_name("Black"), 1, 0);
	if (spline->color_fun) current_color_func = spline->color_fun;
	for (unsigned i = 0; i < call0(spline->parameters, len); i++) {
		currentPoly = *(PolyCoeff*)calls(spline->parameters, at, i);
		draw_function(dfh);
		//dfh->originPosition = *(Pos*)calls(spline->points, at, i + 2);
		//change to the position of the last position it drawed
		dfh->originPosition = new_pos(GetCurrentX(), GetCurrentY());
		//extraPara means the i_th point
		dfh->extraPara++;
	}
	if (spline->isClosed) {
		Pos start = *(Pos*)calls(spline->points, at, 1);
		DrawLine(start.x - GetCurrentX(), start.y - GetCurrentY());
	}
	free(dfh);
}

Spline* create_spline(Vector* points, Color color_fun(DrawFuncHolder *dfh), int isClosed) {
	//wont draw if it is only 1 point
	if (pcall0(points, len) < 2) return NULL;
	//handle the bound
	if (isClosed) {
		pcalls(points, insert, 0, pcalls(points, at, pcall0(points, len) - 1));
		pcalls(points, push, pcalls(points, at, 1));
		pcalls(points, push, pcalls(points, at, 2));
	} else {
		pcalls(points, insert, 0, pcalls(points, at, 0));
		Pos* p = (Pos*)pcalls(points, at, pcall0(points, len) - 1);
		pcalls(points, push, p);
		pcalls(points, push, p);
	}
	unsigned n = pcall0(points, len);
	Vector parameters = new_zero_vector(sizeof(PolyCoeff), n - 3);
	int times = n - 3;
	//closed curve has one more spline
	if (isClosed) times++;
	for (int i = 1; i < times; i++) {
		//one spline is determined by 4 points
		Pos pots[4] = {
			*(Pos*)pcalls(points, at, i - 1),
			*(Pos*)pcalls(points, at, i),
			*(Pos*)pcalls(points, at, i + 1),
			*(Pos*)pcalls(points, at, i + 2),
		};
		//construct the coefficient
		PolyCoeff pc = {
			{
				-12 * pots[0].x + 36 * pots[1].x - 36 * pots[2].x + 12 * pots[3].x,
				8 * pots[0].x - 20 * pots[1].x + 16 * pots[2].x - 4 * pots[3].x,
				-pots[0].x + pots[2].x
			},
			{
				-12 * pots[0].y + 36 * pots[1].y - 36 * pots[2].y + 12 * pots[3].y,
				8 * pots[0].y - 20 * pots[1].y + 16 * pots[2].y - 4 * pots[3].y,
				-pots[0].y + pots[2].y
			}
		};
		//add to vector
		*(PolyCoeff*)calls(parameters, at, i - 1) = pc;
	}
	Spline spline = {
		*points,
		parameters,
		color_fun,
		isClosed
	};
	hnew(Spline, res);
	*res = spline;
	return res;
}

void destroy_spline(Spline* spline) {
	call0(spline->parameters, destroy);
	call0(spline->points, destroy);
}
