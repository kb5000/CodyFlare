#include "vector.h"
#include <stdio.h>
#include "sheet.h"
#include <stdlib.h>
#include "extgraph.h"
#include "stat_line.h"

void show_status_line(int score, int hp, int bombs, int hitPlane, int gameMode) {
	hnew(Vector, vec);
	*vec = gen_empty_vector(Vector);
	Vector v = gen_empty_vector(char[24]); //This is a bug? Whatever, we must use its true size when using static array
	char chrs[5][24] = {""};
	sprintf(chrs[0], "Ѫ��: %d", hp);
	sprintf(chrs[1], "ը��: %d", bombs);
	sprintf(chrs[2], "����: %d", score);
	sprintf(chrs[3], "����ɻ�: %d", hitPlane);
	sprintf(chrs[4], gameMode ? "����ģʽ" : "����ģʽ");
	for (int j = 0; j < 5; j++) {
		calls(v, push, chrs[j]);
	}
	pcalls(vec, push, &v);
	show_sheet(vec, new_pos(0, 0), new_pos(10, 0.2), 1, 5, 0, 1, 0.8, color_by_name("DarkGrey"), color_by_name("Black"),
 color_by_rgb(210, 205, 200), 
			   "����", 20, "Default", 14, 'L');
	calls(v, destroy);
	pcalls(vec, destroy);
	free(vec);
}
