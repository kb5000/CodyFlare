#include "status_line.h"
#include "vector.h"
#include <stdio.h>
#include "sheet.h"
#include <stdlib.h>

void show_status_line(int score, int hp, int bombs) {
    hnew(Vector, vec);
    *vec = gen_empty_vector(Vector);
    Vector v = gen_empty_vector(24);
	char empty[24];
	calls(v, push, empty);
	calls(v, push, empty);
	calls(v, push, empty);
	sprintf(calls(v, at, 0) , "score: %d", score);
	sprintf(calls(v, at, 1), "health: %d", hp);
	sprintf(calls(v, at, 2), "bombs: %d", bombs);
    pcalls(vec, push, &v);
	//Vector v = 
	show_sheet(vec, new_pos(0, 0), new_pos(10, 0.15), 1, 3, 0, 1, 0, color_by_name("DarkGrey"),
			   color_by_name("Red"), color_by_rgb(210, 210, 210), "宋体", 1, "微软雅黑", 14);
	calls(v, destroy);
	pcalls(vec, destroy);
	//free(vec);
}
