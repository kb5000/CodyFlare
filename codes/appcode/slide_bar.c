#include "slide_bar.h"
#include "graphics.h"
#include "color.h"

int slide_bar(int id, Pos position, Pos size, double* num) {
	set_color(color_by_name("LightGrey"));
	MovePen(position.x + size.x * 0.09, position.y + size.y * 0.2);
	DrawLine(size.x * 0.81, 0);

}
