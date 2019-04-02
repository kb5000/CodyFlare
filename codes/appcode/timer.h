#pragma once

#include "linked_list.h"

extern ListHandler* globalTimerFunctionList;
extern int globalTimerInterval;

typedef struct {
	void (*func)();
	int tickInterval;
	int id;
	int callCount, maxCallCount;
} TimerFunc;

void init_global_timer();
void start_global_timer();
void restart_global_timer();
void stop_global_timer();

void add_func_to_timer(void func(), int tickInterval, int id, int maxCallCount);
void remove_funcs_from_timer(int id);
void remove_invalid_funcs();
