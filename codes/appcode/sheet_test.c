#include "sheet_test.h"
#include "sheet.h"
#include "anime_test.h"
#include "timer.h"
#include <stdlib.h>

static char chrs[5][3][10] = {{"标题", "no", "at"}, {"b", "kalos", "np"}, {"rp"}, {"", "内容", ""}, {"", "", "YSL1"}};

static char chb[8][40] = {
	"游戏帮助",
	//"",
	"这款游戏采用键盘交互",
	"上下左右移动",
	"空格发导弹",
	"（长按）F键发炸弹",
};

void show_sheets(Vector* vec) {
	if (show_sheet(vec, new_pos(1, 2), new_pos(3, 3), 5, 3, 1, 1, 0.4, color_by_name("DarkGrey"), color_by_name("Black"), color_by_rgb(216, 192, 180), 
			   "黑体", 20, "楷体", 18)) disable_me_in_timer();
}

void show_sheetb(Vector* vec) {
	show_sheet(vec, new_pos(6, 2), new_pos(3, 3), 7, 1, 1, 0, 0.8, color_by_name("DarkGrey"), color_by_name("Black"), color_by_rgb(216, 192, 180), 
			   "黑体", 20, "楷体", 18);
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
}