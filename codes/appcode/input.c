#include "input.h"
#include "graphics.h"
#include "imgui.h"
#include <Windows.h>
//#include <WinUser.h>
#include "extgraph.h"

static void (*keyToCallFunc[256])(void* para, int keyEvent);
static void* keyFuncDatas[256];
static DirKeys dirKeys;
static MouseKeys mouseKeys;

void CharEventProcess(char ch) {
	uiGetChar(ch);
}

void KeyboardEventProcess(int key, int event) {
	uiGetKeyboard(key,event);
	if (key == VK_LEFT) dirKeys.left = event;
	else if (key == VK_RIGHT) dirKeys.right = event;
	else if (key == VK_UP) dirKeys.up = event;
	else if (key == VK_DOWN) dirKeys.down = event;
	if (keyToCallFunc[key]) {
		keyToCallFunc[key](keyFuncDatas[key], event);
	}
}

void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x, y, button, event);
	if (button == VK_LBUTTON) mouseKeys.left = event;
	else if (button == VK_MBUTTON) mouseKeys.middle = event;
	else if (button == VK_RBUTTON) mouseKeys.right = event;
	set_pos(&mouseKeys.pos, ScaleXInches(x), ScaleYInches(y));
}

void init_input() {
	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
}

void add_to_key_process(char key, void (*func)(void*, int), void* para) {
	keyToCallFunc[key] = func;
	keyFuncDatas[key] = para;
}

DirKeys get_dir_key() {
	return dirKeys;
}

MouseKeys get_mouse_key() {
	return mouseKeys;
}

void destroy_input_process() {
	cancelCharEvent();
	cancelKeyboardEvent();
	cancelMouseEvent();
	for (int i = 0; i < 256; i++) {
		if (keyFuncDatas[i]) free(keyFuncDatas[i]);
	}
}
