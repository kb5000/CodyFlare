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

///name: add_pos
///func: add 2 poses
///para: a and b expects to be Pos
///visb: public
Pos add_pos(Pos a, Pos b);

///name: sub_pos
///func: return a minus b
///para: a and b expects to be Pos
///visb: public
Pos sub_pos(Pos a, Pos b);

///name: pos_length
///func: return sqrt(x^2 + y^2)
///para: pos expects to be Pos
///visb: public
double pos_length(Pos pos);

///name: pos_arc
///func: return atan2(y, x)
///para: pos expects to be Pos
///visb: public
double pos_arc(Pos pos);

///name: rect_to_polar
///func: convert pos from rect to polar
///para: pos expects to be Pos
///visb: public
///warn: r will save to x, and theta will save to y
Pos rect_to_polar(Pos pos);

///name: polar_to_rect
///func: convert pos from polar to rect
///para: pos expects to be Pos
///visb: public
Pos polar_to_rect(Pos pos);

///func: generate a unique id, inspired by the Gen_UIID(n)
///usage: just pass a char*, like Unique_ID("name1")
///explanation: there is a unique pointer for any string literals, which cant have
///             repetation with others
#define Unique_ID(n) ((int)n)

#define PI 3.1415926

///name: cast
///func: cast var from void* to type
///para: type expects a typename, var expects void* data
///visb: public
#define cast(type, var) (*(type*)(var))
