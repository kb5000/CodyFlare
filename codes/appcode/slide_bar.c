#include "slide_bar.h"
#include "graphics.h"
#include "color.h"
#include "input.h"
#include <math.h>

static int activeMove = 0;

void draw_vernier(Pos position) {
	MovePen(position.x, position.y + 0.06);
	DrawLine(0.05, 0.03);
	DrawLine(0, 0.1);
	DrawLine(-0.1, 0);
	DrawLine(0, -0.1);
	DrawLine(0.05, -0.03);
}

void slide_bar(Pos position, Pos size, double* num) {
	set_color(color_by_name("LightGrey"));
	MovePen(position.x + size.x * 0.09, position.y + size.y * 0.2);
	DrawLine(size.x * 0.81, 0);
	set_color(color_by_name("Blue"));
	draw_vernier(add_pos(position, new_pos(size.x * 0.09 + size.x * 0.81 * (*num), 0)));
	MouseKeys mouse = get_mouse_key();
	if (mouse.left == 0 && fabs(mouse.pos.x - position.x - size.x * 0.09 - size.x * 0.81 * (*num)) <= 0.08 &&
		(mouse.pos.y >= position.y + 0.02) && (mouse.pos.y <= position.y + 0.16)) {
		activeMove = 1;
	}
	if (activeMove) {
		*num = (mouse.pos.x - position.x - size.x * 0.09) / (size.x * 0.81);
		if (*num < 0) *num = 0;
		if (*num > 1) *num = 1;
	}
	if (mouse.left == 2 || mouse_at_edge()) {
		activeMove = 0;
		reset_mouse_key(1);
	}
}
