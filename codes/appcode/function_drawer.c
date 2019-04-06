#include "function_drawer.h"
#include "graphics.h"
#include <math.h>
#include <string.h>

void SetPenColor(const char* color);
void SetPenSize(int size);

void draw_function(DrawFuncHolder* drawHd) {
	SetPenColor(drawHd->color);
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
	for (drawHd->tNow = 0; drawHd->tNow < drawHd->tMax; drawHd->tNow += drawHd->tStep) {
		Pos delta = drawHd->func(drawHd);
		if (drawHd->rotate != 0) {
			Pos temp = delta;
			delta.x = cos(drawHd->rotate) * temp.x - sin(drawHd->rotate) * temp.y;
			delta.y = sin(drawHd->rotate) * temp.x + cos(drawHd->rotate) * temp.y;
		}
		DrawLine(delta.x * drawHd->size, delta.y * drawHd->size);
	}
	MovePen(drawHd->originPosition.x, drawHd->originPosition.y);
}

void draw_function_one_step(void* drawFuncHolder) {
	DrawFuncHolder* drawHd = (DrawFuncHolder*)drawFuncHolder;
	if (drawHd->tNow > drawHd->tMax) return;
	SetPenColor(drawHd->color);
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
	delta.x *= drawHd->size;
	delta.y *= drawHd->size;
	Pos temp = delta;
	if (drawHd->rotate != 0) {
		delta.x = cos(drawHd->rotate) * temp.x - sin(drawHd->rotate) * temp.y;
		delta.y = sin(drawHd->rotate) * temp.x + cos(drawHd->rotate) * temp.y;
	}
	DrawLine(delta.x, delta.y);
	drawHd->tNow += drawHd->tStep;
	drawHd->drawPositionBias.x += temp.x;
	drawHd->drawPositionBias.y += temp.y;
	MovePen(drawHd->originPosition.x, drawHd->originPosition.y);
}

DrawFuncHolder create_function_holder(Pos(*func)(DrawFuncHolder* para), Pos originPosition, Pos drawPositionBias, double size, double tNow, double tMax, double tStep, double rotate, const char* color, int penSize) {
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
