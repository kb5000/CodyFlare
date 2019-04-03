#pragma once

#include "linked_list.h"

extern ListHandler globalTimerFunctionList;
extern int globalTimerInterval;

typedef struct {
	void (*func)(void*); //call every tickInterval ticks and pass paras to it
	void* paras; //it must be a pointer malloced or NULL, or it will cause CRASH
	int tickInterval; 
	int id; //some functions can share the same id to be removed together
	int callCount, maxCallCount; //func can be called maxCallCount times, -1 means infinity
} TimerFunc;


void init_global_timer();
void start_global_timer();
void restart_global_timer();
void stop_global_timer();

void add_func_to_timer(void func(void*), void* paras, int tickInterval, int id, int maxCallCount);
void remove_funcs_from_timer(int id);
void remove_invalid_funcs();
