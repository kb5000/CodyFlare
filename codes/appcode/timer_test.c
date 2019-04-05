#include "timer_test.h"
#include "graphics.h"
#include "timer.h"
#include "point.h"
#include <stdlib.h>

void func(void* paras) {
	Pos* p = (Pos*)paras;
	MovePen(p->x, p->y);
	DrawLine(0.1, 0.2);
	p->y += 0.1;
	p->x += 0.1;
}

void test_of_timer() {
	InitGraphics();
	init_global_timer();
	Pos* p = (Pos*)malloc(sizeof(Pos));
	p->x = 1;
	p->y = 1;
	Pos* q = (Pos*)malloc(sizeof(Pos));
	q->x = 2;
	q->y = 1;
	add_func_to_timer(func, p, 10, 1, 10);
	add_func_to_timer(func, q, 10, 1, -1);
	start_global_timer();
	globalTimerInterval = 100;
	restart_global_timer();
}