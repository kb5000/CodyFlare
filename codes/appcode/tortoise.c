#include "tortoise.h"
#include "graphics.h"
#include <math.h>

static Pos tortoisePos = {5, 3.5}, homePos = {5, 3.5};
static double tortoiseDirt = 0;
static int isDrawing = 1;

void move_tortoise(Pos pos) {
	tortoisePos = pos;
}

void tts_fd(double len) {
	Pos det = {len * cos(tortoiseDirt), len * sin(tortoiseDirt)};
	if (isDrawing) {
		MovePen(tortoisePos.x, tortoisePos.y);
		DrawLine(det.x, det.y);
	}
	tortoisePos = add_pos(tortoisePos, det);
}

void tts_bk(double len) {
	tts_fd(-len);
}

void tts_lt(double deg) {
	tortoiseDirt += deg * PI / 180;
}

void tts_rt(double deg) {
	tortoiseDirt -= deg * PI / 180;
}

void tts_pu() {
	isDrawing = 0;
}

void tts_pd() {
	isDrawing = 1;
}

void tts_turn(double deg) {
	tortoiseDirt = deg * PI / 180;
}

void tts_home() {
	if (isDrawing) {
		MovePen(tortoisePos.x, tortoisePos.y);
		Pos det = sub_pos(homePos, tortoisePos);
		DrawLine(det.x, det.y);
	}
	tortoisePos = homePos;
}

void tts_set_home() {
	homePos = tortoisePos;
}
