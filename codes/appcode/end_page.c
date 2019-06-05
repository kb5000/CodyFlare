#include "end_page.h"
#include "ingame.h"
#include "game_particle.h"
#include "font.h"
#include "timer.h"
#include "random.h"
#include "utility.h"
#include "vector.h"
#include "sheet.h"
#include "color.h"
#include "timer.h"
#include <stdlib.h>

void draw_firework(void* unuseful) {
	Pos pos = new_pos(RandomReal(1, 9), RandomReal(1, 6));
	show_bonus_particle(pos);
}

void show_end_page() {
	show_font("VICTORY", 3);
	add_func_to_timer(draw_firework, NULL, 90, 123400, -1);
	draw_vic_play();
}

static char vicPlay[6][80] = {
	"摧毁了克里人的指挥母舰后，克里人军队阵脚大乱，但",
	"庞大的数量仍然让冷锋倍感压力。就在这时一道亮光闪",
	"过，秒杀了众多克里人战舰--是美国复仇者联盟派出营",
	"救史塔克的惊奇队长卡罗尔！克里人的阻截反而戏剧性",
	"地促使中美两位队长胜利会师，他们一起向着泰坦星进",
	"发，继续这场拯救托尼的漫漫长旅..."
};

void vic_play_drawer(Vector* vec) {
	show_sheet(vec, new_pos(2.9, 3), new_pos(4.2, 1.8), 6, 1, 0, 0, 0.3, color_by_name("DarkGrey"), color_by_name("Black"),
			   color_by_rgb(216, 192, 180), "Default", 16, "宋体", 16, 'L');
}

void draw_vic_play() {
	hnew(Vector, info);
	*info = gen_empty_vector(Vector);
	for (int i = 0; i < 6; i++) {
		Vector vec = gen_empty_vector(char[80]);
		calls(vec, push, vicPlay[i]);
		pcalls(info, push, &vec);
	}
	add_func_to_timer(vic_play_drawer, info, 1, 3999, -1);
}