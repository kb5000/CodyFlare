#pragma once

typedef struct {
	double x, y;
} Pos;

///name: new_pos
///func: construct a new Pos by x and y
///para: x and y expects to be double
///visb: public
Pos new_pos(double x, double y);