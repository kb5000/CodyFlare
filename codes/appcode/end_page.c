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
	"�ݻ��˿����˵�ָ��ĸ���󣬿����˾�����Ŵ��ң���",
	"�Ӵ��������Ȼ����汶��ѹ����������ʱһ��������",
	"������ɱ���ڶ������ս��--�����������������ɳ�Ӫ",
	"��ʷ���˵ľ���ӳ����޶��������˵���ط���Ϸ����",
	"�ش�ʹ������λ�ӳ�ʤ����ʦ������һ������̩̹�ǽ�",
	"���������ⳡ�����������������..."
};

void vic_play_drawer(Vector* vec) {
	show_sheet(vec, new_pos(2.9, 3), new_pos(4.2, 1.8), 6, 1, 0, 0, 0.3, color_by_name("DarkGrey"), color_by_name("Black"),
			   color_by_rgb(216, 192, 180), "Default", 16, "����", 16, 'L');
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