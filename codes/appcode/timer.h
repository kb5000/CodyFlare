#pragma once

#include "linked_list.h"

//extern ListHandler globalTimerFunctionList;
//extern int globalTimerInterval;

typedef struct {
	void (*func)(void*); //call every tickInterval ticks and pass paras to it
	void* paras; //it must be a pointer malloced or NULL, or it will cause CRASH
	int tickInterval; 
	int id; //some functions can share the same id to be removed together
	int callCount, maxCallCount; //func can be called maxCallCount times, -1 means infinity
} TimerFunc;


/// these are functions to control the timer

/// name: init_global_timer
/// func: init the global timer
/// visb: public
/// warn: must be called before the timer was started
void init_global_timer();
/// name: start_global_timer
/// func: start the timer and start to call function registered
/// visb: public
void start_global_timer();
/// name: restart_global_timer
/// func: reset the timer and can change the timer interval
/// para: timeInterval expects the new timeInterval
/// visb: public
/// warn: when you changed the interval, you must call this to apply the change
void restart_global_timer(int timeInterval);
/// name: stop_global_timer
/// func: stop the timer
/// visb: public
void stop_global_timer();
/// name: get_timer_interval
/// func: get current time interval
/// visb: public
int get_timer_interval();

/// these are functions to control the timer stack

/// name: change_timer_stack
/// func: switch the timer to another stack
/// para: id expects the timer stack id
/// visb: public
/// warn: you need to add all timer functions in the new stack
/// note: in fact, this is a simple version of coroutine
void change_timer_stack(int id);
/// name: destroy_timer_stack
/// func: destroy certain timer stack
/// para: id expects the timer stack id
/// visb: public
void destroy_timer_stack(int id);
/// name: get_timer_stack
/// func: get current timer stack id
/// visb: public
int get_timer_stack();


/// these are functions to control the funcs to be called by the timer

/// name: add_func_to_timer
/// func: register a func to the timer
/// para: func expects the function to be called, paras expects paras passed to the function, 
///       tickInterval expects how many ticks between 2 calls, 1 means each tick will call it,
///       id expects a unique id to identify it, if you dont want to remove it, you can share the same id,
///       maxCallCount expects how many times will the function be called, -1 means infinity
/// visb: public
/// warn: paras must be a pointer refers to a malloced memory or NULL, or it will cause CRASH
void add_func_to_timer(void func(void*), void* paras, int tickInterval, int id, int maxCallCount);
/// name: remove_funcs_from_timer
/// func: remove all funcs have the id
/// para: id expects a valid id in the func list
/// visb: public
/// warn: never call it by the timer or it will cause CRASH
void remove_funcs_from_timer(int id);
/// name: remove_invalid_funcs
/// func: remove all funcs whose call time equals the maxCallCount, which means it wont be called later
/// para: just pass NULL
/// visb: public
void remove_invalid_funcs(void* unuseful);

/// these are useful functions to call in timer

/// name: auto_clear_display
/// func: perform a full display clear, can be called by the global timer
/// para: just pass NULL
/// visb: public
/// warn: best to make it be the first function in the timer function list
void auto_clear_display(void* unuseful);
/// name: disable_me_in_timer
/// func: to disable a function in the timer, stop call it later
/// visb: public
/// warn: you may want to call remove_invalid_funcs(NULL) to delete the invalid function
void disable_me_in_timer();
/// name: get_tick
/// func: get the ticks since the timer was started
/// visb: public
int get_tick();
/// name: future_do
/// func: call func after time ticks
/// para: time expects the ticks, fun expects a function, para expects the para passed to fun
/// visb: public
/// warn: if timer stack was changed, it wont call at that time
void future_do(int time, void fun(void *), void* para);
/// name: gc_activer
/// func: free the pointer passed, usually call it with future_do to free something after a while
/// para: any expects a pointer malloced
/// visb: public
void gc_activer(void* any);
