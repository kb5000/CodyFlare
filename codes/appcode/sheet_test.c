#include "sheet_test.h"
#include "sheet.h"
#include "anime_test.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include "stat_line.h"
#include "imgui.h"
#include "extgraph.h"

static char chrs[5][3][10] = {{"标题", "no", "at"}, {"b", "kalos", "np"}, {"rp"}, {"", "内容", ""}, {"", "", "YSL1"}};

static char chb[8][40] = {
	"游戏帮助",
	//"",
	"这款游戏采用键盘交互",
	"上下左右移动",
	"空格发导弹",
	"（长按）F键发炸弹",
};

Pos pos = {1, 2};

void show_sheets(Vector* vec) {
	if (show_sheet(vec, pos, new_pos(3, 3), 5, 3, 1, 1, 0.4, color_by_name("DarkGrey"), color_by_name("Black"),
				   color_by_rgb(216, 192, 180),
				   "黑体", 20, "楷体", 18, 'C')) pos.x += 0.05;;
}

void show_sheetb(Vector* vec) {
	show_sheet(vec, new_pos(6, 2), new_pos(3, 3), 7, 1, 1, 0, 0.8, color_by_name("DarkGrey"), color_by_name("Black"),
 color_by_rgb(216, 192, 180), 
			   "黑体", 20, "楷体", 18, 'C');
}

void show_moving_sheet(void* unuseful) {
	hnew(Vector, vec);
	*vec = gen_empty_vector(Vector);
	Vector v = gen_empty_vector(char[3]); //This is a bug? Whatever, we must use its true size when using static array
	char sdsd[6];
	sprintf(sdsd, "22");
	for (int j = 0; j < 3; j++) {
		calls(v, push, sdsd);
	}
	pcalls(vec, push, &v);
	show_sheet(vec, new_pos(1, 1), new_pos(3, 0.2), 1, 3, 0, 0, 0.8, color_by_name("DarkGrey"), color_by_name("Black"),
 color_by_rgb(216, 192, 180), 
			   "黑体", 20, "楷体", 18, 'C');
	calls(v, destroy);
	pcalls(vec, destroy);
	free(vec);
}

void test_of_sheet() {
	common_anime_test_init();
	//Vector hold = gen_empty_vector(char*);
	hnew(Vector, vec);
	*vec = gen_empty_vector(Vector);
	for (int i = 0; i < 5; i++) {
		Vector v = gen_empty_vector(char[10]); //This is a bug? Whatever, we must use its true size when using static array
		for (int j = 0; j < 3; j++) {
			calls(v, push, chrs[i][j]);
		}
		pcalls(vec, push, &v);
	}
	add_func_to_timer(show_sheets, vec, 1, 9423, -1);

	hnew(Vector, vect);
	*vect = gen_empty_vector(Vector);
	for (int i = 0; i < 8; i++) {
		Vector v = gen_empty_vector(char[40]); //This is a bug? Whatever, we must use its true size when using static array
		calls(v, push, chb[i]);
		pcalls(vect, push, &v);
	}
	add_func_to_timer(show_sheetb, vect, 1, 9423, -1);

	add_func_to_timer(show_moving_sheet, vect, 1, 9423, -1);
}

static int n = 0;

void ss(char* t) {
}

void show_status_liner(int score, int hp, int bombs, int hitPlane, int missPlane) {
	SetFont((char*)"宋体");
}

void show_stats(void* u) {
	button(0, 1, 1, 0.8, 0.3, "E");
	for (int i = 0; i < 1000; i++) //ss("宋体");
	show_status_line(1, 1, 1, i, 0);
}

void test_of_stat() {
	common_anime_test_init();
	add_func_to_timer(show_stats, NULL, 1, 12, -1);
}