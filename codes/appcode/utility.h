#pragma once

typedef struct {
	double x, y;
} Pos;

///name: new_pos
///func: construct a new Pos by x and y
///para: x and y expects to be double
///visb: public
Pos new_pos(double x, double y);

///name: set_pos
///func: assign target from source
///para: x and y expects to be double
///visb: public
void set_pos(Pos* target, double x, double y);

Pos add_pos(Pos a, Pos b);

Pos sub_pos(Pos a, Pos b);

double pos_length(Pos pos);

double pos_arc(Pos pos);

Pos rect_to_polar(Pos pos);

Pos polar_to_rect(Pos pos);

///func: generate a unique id, inspired by the Gen_UIID(n)
///usage: just pass a char*, like Unique_ID("name1")
///explanation: there is a unique pointer for any string literals, which cant have
///             repetation with others
#define Unique_ID(n) ((int)n)

#define PI 3.1415926
