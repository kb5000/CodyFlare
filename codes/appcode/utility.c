#include "utility.h"

Pos new_pos(double x, double y)
{
	Pos res = { x, y };
	return res;
}

void set_pos(Pos* target, double x, double y) {
	target->x = x;
	target->y = y;
}
