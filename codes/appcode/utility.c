#include "utility.h"
#include <math.h>
#include "graphics.h"

Pos new_pos(double x, double y)
{
	Pos res = { x, y };
	return res;
}

void set_pos(Pos* target, double x, double y) {
	target->x = x;
	target->y = y;
}

Pos add_pos(Pos a, Pos b) {
	return new_pos(a.x + b.x, a.y + b.y);
}

Pos sub_pos(Pos a, Pos b) {
	return new_pos(a.x - b.x, a.y - b.y);
}

double pos_length(Pos pos) {
	return sqrt(pos.x * pos.x + pos.y * pos.y);
}

double pos_arc(Pos pos) {
	return atan2(pos.y, pos.x);
}

Pos rect_to_polar(Pos pos) {
	return new_pos(pos_length(pos), pos_arc(pos));
}

Pos polar_to_rect(Pos pos) {
	return new_pos(pos.x * cos(pos.y), pos.x * sin(pos.y));
}

void show_now() {
	show_all_now();
}
