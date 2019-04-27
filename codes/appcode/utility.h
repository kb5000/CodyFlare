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

///name: pos_mut
///func: return a multiplyed by num
///para: a expects to be Pos, num expects a double
///visb: public
Pos pos_mut(Pos p, double num);

///name: pos_dot
///func: return a dot b, eg. a.x * b.x + a.y * b.y
///para: a and b expects to be Pos
///visb: public
double pos_dot(Pos a, Pos b);

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

///name: show_now
///func: update the screen
///visb: public
void show_now(void* unuseful);

///func: generate a unique id, inspired by the Gen_UIID(n)
///usage: just pass a const char*, like Unique_ID("name1")
///explanation: there is a unique pointer for any string literals, which cant have
///             repetation with others
#define Unique_ID(n) ((int)n)

#define PI 3.141592653589793

///name: cast
///func: cast var from void* to type
///para: type expects a typename, var expects void* data
#define cast(type, var) (*(type*)(var))

///name: call 0 to 3, pcall 0 to 3
///func: a simple way to call member function
///example: call0(vector, len); pcall2(map, insert, 1, NULL);
#define call0(obj, func) (obj).func(&(obj))
#define call1(obj, func, p1) (obj).func(&(obj), p1)
#define call2(obj, func, p1, p2) (obj).func(&(obj), p1, p2)
#define call3(obj, func, p1, p2, p3) (obj).func(&(obj), p1, p2, p3)
#define pcall0(obj, func) (obj)->func(obj)
#define pcall1(obj, func, p1) (obj)->func(obj, p1)
#define pcall2(obj, func, p1, p2) (obj)->func(obj, p1, p2)
#define pcall3(obj, func, p1, p2, p3) (obj)->func(obj, p1, p2, p3)

#define calls(obj, func, ...) (obj).func(&(obj), ##__VA_ARGS__)
#define pcalls(obj, func, ...) (obj)->func((obj), ##__VA_ARGS__)

