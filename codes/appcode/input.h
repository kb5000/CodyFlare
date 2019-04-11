#pragma once
#include "utility.h"

typedef struct {
	int up, down, left, right;
} DirKeys;

typedef struct {
	int left, middle, right;
	Pos pos;
} MouseKeys;

void init_input();

void add_to_key_process(char key, void(*func)(void*, int), void* para);

DirKeys get_dir_key();

MouseKeys get_mouse_key();