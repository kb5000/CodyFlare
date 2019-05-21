#include "input.h"
#include "graphics.h"
#include "imgui.h"
#include <Windows.h>
//#include <WinUser.h>
#include "extgraph.h"

static void (*keyToCallFunc[256])(int key, void* para, int keyEvent);
static void* keyFuncDatas[256];
static DirKeys dirKeys = {-1, -1, -1, -1};
static MouseKeys mouseKeys = {-1, -1, -1};
static int lastKey;
static Pos lastMousePos;

void CharEventProcess(char ch) {
	uiGetChar(ch);
}

void KeyboardEventProcess(int key, int event) {
	uiGetKeyboard(key,event);
	lastKey = key;
	if (key == VK_LEFT) dirKeys.left = event;
	else if (key == VK_RIGHT) dirKeys.right = event;
	else if (key == VK_UP) dirKeys.up = event;
	else if (key == VK_DOWN) dirKeys.down = event;
	if (keyToCallFunc[key]) {
		keyToCallFunc[key](key, keyFuncDatas[key], event);
	}
}

void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x, y, button, event);
	if (button == 1) {
		mouseKeys.left = event;
	}
	else if (button == 2) {
		mouseKeys.middle = event;
	}
	else if (button == 3) {
		mouseKeys.right = event;
	}
	lastMousePos = mouseKeys.pos;
	set_pos(&mouseKeys.pos, ScaleXInches(x), ScaleYInches(y));
	mouseKeys.dpos = sub_pos(mouseKeys.pos, lastMousePos);
}

void init_input() {
	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
}

void add_to_key_process(char key, void (*func)(int, void*, int), void* para) {
	keyToCallFunc[key] = func;
	keyFuncDatas[key] = para;
}

void clear_key_process(char key) {
	keyToCallFunc[key] = NULL;
	keyFuncDatas[key] = NULL;
}

DirKeys get_dir_key() {
	return dirKeys;
}

MouseKeys get_mouse_key() {
	return mouseKeys;
}

void reset_mouse_key(int key) {
	switch (key) {
	case 1:
		mouseKeys.left = -1;
		break;
	case 2:
		mouseKeys.middle = -1;
		break;
	case 3:
		mouseKeys.right = -1;
		break;
	default:
		break;
	}
}

void move_by_dir_key(Pos* target, Pos speed) {
	DirKeys key = get_dir_key();
	if (key.left == 0) target->x -= speed.x;
	if (key.right == 0) target->x += speed.x;
	if (key.up == 0) target->y += speed.y;
	if (key.down == 0) target->y -= speed.y;
}

void destroy_input_process() {
	cancelCharEvent();
	cancelKeyboardEvent();
	cancelMouseEvent();
	for (int i = 0; i < 256; i++) {
		if (keyFuncDatas[i]) free(keyFuncDatas[i]);
	}
}

int get_last_key() {
	return lastKey;
}

int mouse_at_edge() {
	Pos pos = get_mouse_key().pos;
	if (pos.x >= 9.83 || pos.x <= 0.04 || pos.y >= 6.95 || pos.y <= 0.14) return 1;
	return 0;
}
