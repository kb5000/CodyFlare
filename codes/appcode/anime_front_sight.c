#include "animes.h"
#include "extgraph.h"

void draw_front_sight(Pos* posp) {
	Pos pos = *posp;
	if (pos.x == -1) disable_me_in_timer();
	set_color(color_by_rgb(60, 180, 60));
	double d = 0.04, la = 0.1, lb = 0.1;

	MovePen(pos.x - d, pos.y);
	SetPenSize(1);
	DrawLine(-la, 0);
	SetPenSize(2);
	DrawLine(-lb, 0);

	MovePen(pos.x + d, pos.y);
	SetPenSize(1);
	DrawLine(la, 0);
	SetPenSize(2);
	DrawLine(lb, 0);

	MovePen(pos.x, pos.y + d);
	SetPenSize(1);
	DrawLine(0, la);
	SetPenSize(2);
	DrawLine(0, lb);

	MovePen(pos.x, pos.y - d);
	SetPenSize(1);
	DrawLine(0, -la);
	SetPenSize(2);
	DrawLine(0, -lb);

	SetPenSize(1);

	if (pos.y < 6.5)
		posp->y += 0.2;
}

