#include "function_drawer.h"
#include "graphics.h"

void draw_function(DrawFuncHolder* drawHd) {
	Pos startPos = { drawHd->originPosition.x + drawHd->drawPositionBias.x,
					 drawHd->originPosition.y + drawHd->drawPositionBias.y };
	MovePen(startPos.x, startPos.y);
	for (drawHd->tNow = 0; drawHd->tNow < drawHd->tMax; drawHd->tNow += drawHd->tStep) {
		Pos delta = drawHd->func(drawHd);
		DrawLine(delta.x, delta.y);
	}
	MovePen(drawHd->originPosition.x, drawHd->originPosition.y);
}

void draw_function_one_step(void* drawFuncHolder) {
	DrawFuncHolder* drawHd = (DrawFuncHolder*)drawFuncHolder;
	if (drawHd->tNow >= drawHd->tMax) return;
	Pos startPos = { drawHd->originPosition.x + drawHd->drawPositionBias.x,
					 drawHd->originPosition.y + drawHd->drawPositionBias.y };
	MovePen(startPos.x, startPos.y);
	Pos delta = drawHd->func(drawHd);
	DrawLine(delta.x, delta.y);
	drawHd->tNow += drawHd->tStep;
	drawHd->drawPositionBias.x += delta.x;
	drawHd->drawPositionBias.y += delta.y;
	MovePen(drawHd->originPosition.x, drawHd->originPosition.y);
}
