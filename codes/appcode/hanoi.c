#include "honoi.h"
#include "graphics.h"
#include "imgui.h"

void display();
void draw();

const int delay = 16;

void shit(int a) {
	display();
}

void fuck() {
	MovePen(1, 1);
	DrawLine(2.2, 2.22);
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUIªÒ»° Û±Í
}

void hanoi() {
	InitGraphics();
	InitGUI();
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(shit);
	startTimer(10, delay);
}

void draw() {
	
	if (button(GenUIID(0), 0, 0, 1, 1, "klw")) {
		DrawLine(1, 10);
		MovePen(0, 0);
	}
}


void display() {
	DisplayClear();
	draw();
}