#pragma once
#include "utility.h"

/// messages: KEY_DOWN == 0, KEY_UP == 1
/// mouse: BUTTON_DOWN 0, BUTTON_UP 2, BUTTON_DOUBLECLICK 1, ROLL_UP 3, ROLL_DOWN 4, MOUSEMOVE 5
/// 			CLICK 6


typedef struct {
	int up, down, left, right;
} DirKeys;

typedef struct {
	int left, middle, right;
	Pos pos, dpos;
} MouseKeys;

/// name: init_input
/// func: initialize the input recevier
/// visb: public
void init_input();

/// name: add_to_key_process
/// func: add a function that will be called when the certain key has an event
/// para: key expects a number from 0 to 255 (or 127?), func expects a handle function, the paras of which
///       is the para passed by and the event number, para expects the pointer which will be passed
///       to the func
/// visb: public
/// warn: you cant pass a stack memory(not malloced) to the para, or it will cause CRASH
void add_to_key_process(char key, void(*func)(int, void*, int), void* para);

void clear_key_process(char key);

/// name: get_dir_key
/// func: get the status of four direction keys
/// visb: public
DirKeys get_dir_key();

/// name: get_mouse_key
/// func: get the status of the mouse
/// visb: public
MouseKeys get_mouse_key();

/// name: reset_mouse_key
/// func: reset the state of middle button
/// visb: public
/// warn: always call it after the roll handle
void reset_mouse_key(int key);

/// name: move_by_dir_key
/// func: move target on speed by dir keys
/// func: target expects Pos to change, speed expects the x and y speed
/// visb: public
void move_by_dir_key(Pos* target, Pos speed);

/// name: destroy_input_process
/// func: terminate the input system
/// visb: public
void destroy_input_process();

/// name: get_last_key
/// func: get last key which have event
/// visb: public
int get_last_key();

/// name: mouse_at_edge
/// func: return whether the mouse is at the edge of the window
/// visb: public
int mouse_at_edge();

/// name: last_mouse_up_pos
/// func: return the last pos when moues left button was up
/// visb: public
Pos last_mouse_up_pos();
