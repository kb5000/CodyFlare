#include "status_line.h"
#include "vector.h"
#include <stdio.h>
#include "sheet.h"
#include <stdlib.h>

void show_status_line(int score, int hp, int bombs, int hitPlane, int missPlane) {
 //   hnew(Vector, vec);
 //   *vec = gen_empty_vector(Vector);
 //   Vector v = gen_empty_vector(24);
	//char empty[24];
	//calls(v, push, empty);
	//calls(v, push, empty);
	//calls(v, push, empty);
	//sprintf(calls(v, at, 0) , "score: %d", score);
	//sprintf(calls(v, at, 1), "health: %d", hp);
	//sprintf(calls(v, at, 2), "bombs: %d", bombs);
 //   pcalls(vec, push, &v);

	////Vector v = 
	//show_sheet(vec, new_pos(0, 0), new_pos(10, 0.15), 1, 3, 0, 1, 0, color_by_name("DarkGrey"),
	//		   color_by_name("Red"), color_by_rgb(210, 210, 210), "宋体", 1, "微软雅黑", 14);
	////free(vec);
	hnew(Vector, vec);
	*vec = gen_empty_vector(Vector);
	Vector v = gen_empty_vector(char[24]); //This is a bug? Whatever, we must use its true size when using static array
	char chrs[5][24] = {""};
	sprintf(chrs[0], "health: %d", hp);
	sprintf(chrs[1], "bombs: %d", bombs);
	sprintf(chrs[2], "score: %d", score);
	sprintf(chrs[3], "hit plane: %d", hitPlane);
	//sprintf(chrs[4], "miss plane: %d", missPlane);
	for (int j = 0; j < 5; j++) {
		calls(v, push, chrs[j]);
	}
	pcalls(vec, push, &v);
	show_sheet(vec, new_pos(0, 0), new_pos(10, 0.2), 1, 4, 0, 1, 0.8, color_by_name("DarkGrey"), color_by_name("Black"),
 color_by_rgb(210, 205, 200), 
			   "黑体", 20, "微软雅黑", 18, 'L');
	calls(v, destroy);
	pcalls(vec, destroy);
	free(vec);
}
