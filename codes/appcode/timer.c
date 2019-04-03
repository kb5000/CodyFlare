#include <stdlib.h>
#include "timer.h"
#include "graphics.h"

ListHandler* globalTimerFunctionList = NULL;
int globalTimerInterval = 16;

static int globalTimerID = 1;
static int globalTickCount = 0;

void startTimer(int id, int timeinterval);
void cancelTimer(int id);

void timer_func_caller_helper(void* data) {
	TimerFunc* tmf = (TimerFunc*)data;
	if (globalTickCount % tmf->tickInterval == 0 && tmf->func && tmf->callCount != tmf->maxCallCount) {
		tmf->func(tmf->paras);
		tmf->callCount++;
	}
}

void timer_func_caller(int id) {
	globalTimerFunctionList->for_each(globalTimerFunctionList, timer_func_caller_helper);
	globalTickCount++;
}

void init_global_timer() {
	TimerFunc* timerFunc = (TimerFunc*)malloc(sizeof(TimerFunc));
	timerFunc->func = NULL;
	timerFunc->paras = NULL;
	timerFunc->tickInterval = 2147483647;
	timerFunc->id = -1;
	timerFunc->callCount = 0;
	timerFunc->maxCallCount = 1;
	new_list((void*)timerFunc);
	registerTimerEvent(timer_func_caller);
}

void start_global_timer() {
	startTimer(globalTimerID, globalTimerInterval);
}

void restart_global_timer() {
	cancelTimer(globalTimerID);
	startTimer(globalTimerID, globalTimerInterval);
}

void stop_global_timer() {
	cancelTimer(globalTimerID);
}

void add_func_to_timer(void func(void*), void* paras, int tickInterval, int id, int maxCallCount) {
	TimerFunc* timerFunc = (TimerFunc*)malloc(sizeof(TimerFunc));
	timerFunc->func = func;
	timerFunc->paras = paras;
	timerFunc->tickInterval = tickInterval;
	timerFunc->id = id;
	timerFunc->callCount = 0;
	timerFunc->maxCallCount = maxCallCount;
	globalTimerFunctionList->push_back(globalTimerFunctionList, (void*)timerFunc);
}

void remove_funcs_from_timer(int id) {
	ListHandler* gFL = globalTimerFunctionList;
	while (gFL->head && ((TimerFunc*)gFL->head->data)->id == id) {
		if (((TimerFunc*)gFL->head->data)->paras)
			free(((TimerFunc*)gFL->head->data)->paras);
		gFL->pop_front(gFL);
	}
	while (gFL->nowpos) {
		if (gFL->nowpos->next && ((TimerFunc*)gFL->nowpos->next->data)->id == id) {
			if (((TimerFunc*)gFL->nowpos->next->data)->paras)
				free(((TimerFunc*)gFL->nowpos->next->data)->paras);
			gFL->remove_after(gFL);
			continue;
		}
		gFL->nowpos = gFL->nowpos->next;
	}
}

void remove_invalid_funcs() {
	ListHandler* gFL = globalTimerFunctionList;
	while (gFL->head && ((TimerFunc*)gFL->head->data)->callCount == ((TimerFunc*)gFL->head->data)->maxCallCount) {
		if (((TimerFunc*)gFL->head->data)->paras)
			free(((TimerFunc*)gFL->head->data)->paras);
		gFL->pop_front(gFL);
	}
	while (gFL->nowpos) {
		if (gFL->nowpos->next && ((TimerFunc*)gFL->head->data)->callCount == ((TimerFunc*)gFL->head->data)->maxCallCount) {
			if (((TimerFunc*)gFL->nowpos->next->data)->paras)
				free(((TimerFunc*)gFL->nowpos->next->data)->paras);
			gFL->remove_after(gFL);
			continue;
		}
		gFL->nowpos = gFL->nowpos->next;
	}

}
