#pragma once
#include <stdlib.h>

///name: init_gc
///func: init the gc system
///visb: public
void init_gc();

///name: add_to_gc_data
///func: add a data to the gc system, but recommand to use gen_gc_data instead
///para: data expects memory malloced, size expects the size of the memory
///visb: public but not recommand
void* add_to_gc_data(void* data, unsigned short size);

///name: gen_gc_data
///func: create a memory handled by the system and defined a varible
///para: type expects a valid type like int, variable expects a variable name not used, value expects the initial value
///visb: public
///warn: never make it be part of expression
#define gen_gc_data(type, variable, value) \
	type* variable = (type*)malloc(sizeof(type)); \
	*variable = (value); \
	add_to_gc_data(variable, sizeof(type));

///name: gen_gc_raw
///func: create an uninitialized memory handled by the system and defined a varible
///para: type expects a valid type like int, variable expects a variable name not used
///visb: public
///warn: never make it be part of expression
#define gen_gc_raw(type, variable) \
	type* variable = (type*)malloc(sizeof(type)); \
	add_to_gc_data(variable, sizeof(type));

///name: can_destroy_data
///func: sign a variable that gc can collect it
///para: data expects data allocated by the gc system
///visb: public
void can_destroy_data(void* data);

///name: is_safe_to_use
///func: return whether the data handled was signed to destroy
///visb: public
///warn: always use it if you dont sure whether its valid
int is_safe_to_use(void* data);

///name: perform_gc
///func: free all data signed to destroy
///visb: public
///warn: best to call every 32 ticks or more
void perform_gc(void* unuseful);

///name: gc_all_clear
///func: free all data
///visb: public
void gc_all_clear();
