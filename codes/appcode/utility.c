#include "utility.h"
#include <math.h>
#include "graphics.h"
#include <stdlib.h>

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

Pos pos_mut(Pos p, double num) {
	return new_pos(p.x * num, p.y * num);
}

double pos_dot(Pos a, Pos b) {
	return a.x * b.x + a.y * b.y;
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

void show_now(void* unuseful) {
	show_all_now();
}

double evaluate_polynomia(double* coeff, int n, double x) {
	double res = coeff[0];
	for (int i = 1; i <= n; i++) {
		res = res * x + coeff[i];
	}
	return res;
}

int crash_now(const char* info) {
	exit(-1);
	return -1; //Never return
}

int my_bit_map_get(BitMap* self, int n);
void my_bit_map_set(BitMap* self, int n, int bit);
void my_bit_map_flip(BitMap* self, int n);

BitMap new_bit_map() {
	BitMap res = {
		0,
		my_bit_map_get,
		my_bit_map_set,
		my_bit_map_flip,
	};
	return res;
}

int my_bit_map_get(BitMap* self, int n) {
	return !!(self->bits & (1 << n)); //find the nth bit and turn it into 0 or 1
}

void my_bit_map_set(BitMap* self, int n, int bit) {
	bit = !!bit;				//make bit be 0 or 1
	self->bits &= ~(1 << n);	//set nth bit to 0
	self->bits |= bit << n;		//set nth bit to the value of bit
}

void my_bit_map_flip(BitMap* self, int n) {
	self->bits ^= 1 << n;	//flip nth bit
}
