#include "function_drawer.h"
#include "graphics.h"
#include <math.h>
#include <string.h>
#include <color.h>
#include "extgraph.h"

///For people who want to pasteling it, never do it. The lib cant support it

//#define PAR_FUN_ACCU
//
//#ifdef PAR_FUN_ACCU
//#include <omp.h>
//#endif


void draw_function(DrawFuncHolder* drawHd) {
#ifdef NEW_COLOR_SYSTEM
	set_color(drawHd->color);
#else
	SetPenColor(drawHd->color);
#endif //end of NEW_COLOR_SYSTEM
	SetPenSize(drawHd->penSize);
	Pos newBias = drawHd->drawPositionBias;
	if (drawHd->rotate != 0) {
		newBias.x = cos(drawHd->rotate) * drawHd->drawPositionBias.x - sin(drawHd->rotate) * drawHd->drawPositionBias.y;
		newBias.y = sin(drawHd->rotate) * drawHd->drawPositionBias.x + cos(drawHd->rotate) * drawHd->drawPositionBias.y;
	}
	Pos startPos = {drawHd->originPosition.x + newBias.x,
					 drawHd->originPosition.y + newBias.y};
	MovePen(startPos.x, startPos.y);
	//the step should be as big as possible, as the window could only hold 7000 lines or it will be slow
	//but if you enabled PERFORMANCE_DRAWING, it can hold almost 50000 lines!
	for (drawHd->tNow = 0; drawHd->tNow < drawHd->tMax; drawHd->tNow += drawHd->tStep) {
		Pos delta = drawHd->func(drawHd);
		if (drawHd->rotate != 0) {
			Pos temp = delta;
			delta.x = cos(drawHd->rotate) * temp.x - sin(drawHd->rotate) * temp.y;
			delta.y = sin(drawHd->rotate) * temp.x + cos(drawHd->rotate) * temp.y;
		}
		DrawLine(delta.x * drawHd->size * drawHd->tStep, delta.y * drawHd->size * drawHd->tStep);
	}
	//MovePen(drawHd->originPosition.x, drawHd->originPosition.y);
}

void draw_function_one_step(void* drawFuncHolder) {
	DrawFuncHolder* drawHd = (DrawFuncHolder*)drawFuncHolder;
	if (drawHd->tNow > drawHd->tMax) return;
#ifdef NEW_COLOR_SYSTEM
	set_color(drawHd->color);
#else
	SetPenColor(drawHd->color);
#endif //end of NEW_COLOR_SYSTEM
	SetPenSize(drawHd->penSize);
	Pos newBias = drawHd->drawPositionBias;
	if (drawHd->rotate != 0) {
		newBias.x = cos(drawHd->rotate) * drawHd->drawPositionBias.x - sin(drawHd->rotate) * drawHd->drawPositionBias.y;
		newBias.y = sin(drawHd->rotate) * drawHd->drawPositionBias.x + cos(drawHd->rotate) * drawHd->drawPositionBias.y;
	}
	Pos startPos = {drawHd->originPosition.x + newBias.x,
					 drawHd->originPosition.y + newBias.y};
	MovePen(startPos.x, startPos.y);
	Pos delta = drawHd->func(drawHd);
	delta.x *= drawHd->size * drawHd->tStep;
	delta.y *= drawHd->size * drawHd->tStep;
	Pos temp = delta;
	if (drawHd->rotate != 0) {
		delta.x = cos(drawHd->rotate) * temp.x - sin(drawHd->rotate) * temp.y;
		delta.y = sin(drawHd->rotate) * temp.x + cos(drawHd->rotate) * temp.y;
	}
	DrawLine(delta.x, delta.y);
	drawHd->tNow += drawHd->tStep;
	drawHd->drawPositionBias.x += temp.x;
	drawHd->drawPositionBias.y += temp.y;
	//MovePen(drawHd->originPosition.x, drawHd->originPosition.y);
}


#ifdef NEW_COLOR_SYSTEM
DrawFuncHolder create_function_holder(Pos(*func)(DrawFuncHolder* para), Pos originPosition, Pos drawPositionBias, double size, double tNow, double tMax, double tStep, double rotate, Color color, int penSize, double extraPara) {
	DrawFuncHolder res = {
		func,
		originPosition,
		drawPositionBias,
		size,
		tNow,
		tMax,
		tStep,
		rotate,
		color,
		penSize,
		extraPara,
	};
	return res;
}
#else
DrawFuncHolder create_function_holder, 0(Pos(*func)(DrawFuncHolder* para), Pos originPosition, Pos drawPositionBias, double size, double tNow, double tMax, double tStep, double rotate, const char* color, int penSize) {
	DrawFuncHolder res = {
		func,
		originPosition,
		drawPositionBias,
		size,
		tNow,
		tMax,
		tStep,
		rotate,
	};
	strcpy(res.color, color);
	res.penSize = penSize;
	return res;
}
#endif // NEW_COLOR_SYSTEM

void draw_plain_lines(Vector* lines) {
	for (unsigned i = 0; i < pcall0(lines, len); i++) {
		RectPos* rp = (RectPos*)pcalls(lines, at, i);
		if (!rp) continue;
		MovePen(rp->start.x, rp->start.y);
		DrawLine(rp->end.x - rp->start.x, rp->end.y - rp->start.y);
	}
}
