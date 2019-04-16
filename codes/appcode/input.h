#pragma once
#include "utility.h"

typedef struct {
	int up, down, left, right;
} DirKeys;

typedef struct {
	int left, middle, right;
	Pos pos;
} MouseKeys;

///name: init_input
///func: initialize the input recevier
///visb: public
void init_input();

///name: add_to_key_process
///func: add a function that will be called when the certain key has an event
///para: key expects a number from 0 to 255 (or 127?), func expects a handle function, the paras of which
///      is the para passed by and the event number, para expects the pointer which will be passed
///      to the func
///visb: public
///warn: you cant pass a stack memory(not malloced) to the para, or it will cause CRASH
void add_to_key_process(char key, void(*func)(void*, int), void* para);

///name: get_dir_key
///func: get the status of four direction keys
///visb: public
DirKeys get_dir_key();

///name: get_mouse_key
///func: get the status of the mouse
///visb: public
MouseKeys get_mouse_key();