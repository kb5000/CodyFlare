#include <stdlib.h>
#include "timer.h"
#include "graphics.h"
#include "utility.h"

ListHandler globalTimerFunctionList;
int globalTimerInterval = 32;		//can change

static int globalTimerID = 1;		//only one timer
static int globalTickCount = 1;		//every tick it will add 1
static int functionDisableFlag = 0;	//used by disable_me_from_timer
//static int functionRemoveFlag = 0;

typedef struct {
	int id;
	ListHandler timerFuncs;
} TimerStack;

static ListHandler timerStacks;
static int currentTimerStack = 0;
static int isRunning = 0;

void startTimer(int id, int timeinterval);
void cancelTimer(int id);

void DisplayClear();

void timer_func_caller_helper(void* data) {
	TimerFunc* tmf = (TimerFunc*)data;
	//every tickInterval ticks it will call
	if (!isRunning) return;
	if (globalTickCount % tmf->tickInterval == 0 && tmf->callCount != tmf->maxCallCount && tmf->func) {
		tmf->func(tmf->paras);
		tmf->callCount++;
		//disable_me_from_timer
		if (functionDisableFlag) {
			tmf->callCount = tmf->maxCallCount;
			functionDisableFlag = 0;
		}
		if (!isRunning) return;
	}
}

void timer_func_caller(int id) {
	globalTimerFunctionList.for_each(&globalTimerFunctionList, timer_func_caller_helper);
	//for (Node* n = globalTimerFunctionList.head; n; n && (n = n->next)) {
	//	timer_func_caller_helper(n->data);
	//	if (functionRemoveFlag) {
	//		functionRemoveFlag = 0;
	//		//n && (n = n->next);
	//	}
	//}
	globalTickCount++;
}

int get_tick() {
	return globalTickCount;
}

void init_global_timer() {
	globalTimerFunctionList = new_empty_list();
	registerTimerEvent(timer_func_caller);
	hnew(TimerStack, timerStk);
	timerStk->id = 0;
	timerStk->timerFuncs = globalTimerFunctionList;
	timerStacks = new_empty_list();
	calls(timerStacks, push_back, timerStk);
}

void start_global_timer() {
	startTimer(globalTimerID, globalTimerInterval);
	isRunning = 1;
}

void restart_global_timer(int timeInterval) {
	cancelTimer(globalTimerID);
	globalTimerInterval = timeInterval;
	startTimer(globalTimerID, globalTimerInterval);
}

void stop_global_timer() {
	cancelTimer(globalTimerID);
	isRunning = 0;
}

int get_timer_interval() {
	return globalTimerInterval;
}

void add_func_to_timer(void func(void*), void* paras, int tickInterval, int id, int maxCallCount) {
	TimerFunc* timerFunc = (TimerFunc*)malloc(sizeof(TimerFunc));
	timerFunc->func = func;
	timerFunc->paras = paras;
	timerFunc->tickInterval = tickInterval;
	timerFunc->id = id;
	timerFunc->callCount = 0;
	timerFunc->maxCallCount = maxCallCount;
	globalTimerFunctionList.push_back(&globalTimerFunctionList, (void*)timerFunc);
}

void remove_funcs_from_timer(int id) {
	ListHandler* gFL = &globalTimerFunctionList;
	//remove heads
	while (gFL->head && ((TimerFunc*)gFL->head->data)->id == id) {
		if (((TimerFunc*)gFL->head->data)->paras)
			free(((TimerFunc*)gFL->head->data)->paras);
		gFL->pop_front(gFL);
		//functionRemoveFlag = 1;
	}
	gFL->nowpos = gFL->head;
	//remove others
	while (gFL->nowpos) {
		if (gFL->nowpos->next && ((TimerFunc*)gFL->nowpos->next->data)->id == id) {
			if (((TimerFunc*)gFL->nowpos->next->data)->paras)
				free(((TimerFunc*)gFL->nowpos->next->data)->paras);
			gFL->remove_after(gFL);
			//functionRemoveFlag = 1;
			continue;
		}
		gFL->nowpos = gFL->nowpos->next;
	}
}

void remove_invalid_funcs(void* unuseful) {
	ListHandler* gFL = &globalTimerFunctionList;
	//remove heads
	while (gFL->head && ((TimerFunc*)gFL->head->data)->callCount == ((TimerFunc*)gFL->head->data)->maxCallCount) {
		if (((TimerFunc*)gFL->head->data)->paras)
			free(((TimerFunc*)gFL->head->data)->paras);
		gFL->pop_front(gFL);
		//functionRemoveFlag = 1;
	}
	gFL->nowpos = gFL->head;
	//remove others
	while (gFL->nowpos) {
		if (gFL->nowpos->next && ((TimerFunc*)gFL->nowpos->next->data)->callCount == ((TimerFunc*)gFL->nowpos->next->data)->maxCallCount) {
			if (((TimerFunc*)gFL->nowpos->next->data)->paras)
				free(((TimerFunc*)gFL->nowpos->next->data)->paras);
			gFL->remove_after(gFL);
			//functionRemoveFlag = 1;
			continue;
		}
		gFL->nowpos = gFL->nowpos->next;
	}
}

void auto_clear_display(void* unuseful) {
	DisplayClear();
}

void disable_me_in_timer() {
	functionDisableFlag = 1;
}

static int id_equal(const ListHandler* unuseful, TimerStack* a, int* id) {
	return a->id == *id;
}

void change_timer_stack(int id) {
	stop_global_timer();
	TimerStack* tnow = calls(timerStacks, find_if, id_equal, &currentTimerStack);
	TimerStack* tms = calls(timerStacks, find_if, id_equal, &id);
	if (tnow) tnow->timerFuncs = globalTimerFunctionList;
	if (tms) {
		globalTimerFunctionList = tms->timerFuncs;
		//currentTimerStack = id;
		currentTimerStack = id;
	} else {
		hnew(TimerStack, tmstk);
		tmstk->id = id;
		tmstk->timerFuncs = new_empty_list();
		calls(timerStacks, push_back, tmstk);
		globalTimerFunctionList = tmstk->timerFuncs;
		currentTimerStack = id;
	}
	start_global_timer();
}

static int id_requal(TimerStack* a, int* id) {
	return a->id == *id;
}

void destroy_timer_stack(int id) {
	TimerStack* tms = calls(timerStacks, find_if, id_equal, &id);
	if (!tms) return;
	for (Node* node = tms->timerFuncs.head; node; node = node->next) {
		TimerFunc* tmf = node->data;
		free(tmf->paras);
	}
	calls(tms->timerFuncs, destroy);
	calls(timerStacks, remove_if, id_requal, &id);
}

int get_timer_stack() {
	return currentTimerStack;
}

void future_do(int time, void fun(void*), void* para) {
	add_func_to_timer(fun, para, get_tick() + time, 1048575, 1);
}