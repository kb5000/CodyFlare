#include "status_line.h"
#include "vector.h"
#include <stdio.h>
#include "sheet.h"
#include <stdlib.h>

void show_status_line(int score, int hp, int bombs) {
	char* t[3] = {malloc(24), malloc(24), malloc(24)};
	sprintf(t[0], "score: %d", score);
	sprintf(t[1], "health: %d", hp);
	sprintf(t[2], "bombs: %d", bombs);
	hnew(Vector, v);
	*v = gen_empty_vector(char*);
	pcalls(v, push, t[0]);
	pcalls(v, push, t[1]);
	pcalls(v, push, t[2]);
	//Vector v = 
	show_sheet(v, new_pos(0, 0), new_pos(10, 0.15), 1, 3, 0, 1, 0, color_by_name("DarkGrey"),
			   color_by_name("Red"), color_by_rgb(210, 210, 210), "ËÎÌå", 1, "Î¢ÈíÑÅºÚ", 14);
}