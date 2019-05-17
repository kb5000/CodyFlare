#include "animes.h"

void draw_missile(Pos pos, Pos dirt, Color color) {
	set_color(color);
	move_tortoise(pos);
	tts_turn(pos_arc(dirt) * 180 / PI - 90);
	tts_set_home();
	tts_pd();
	tts_bk(0.015);	tts_fd(0.03);	tts_lt(90);		tts_fd(0.06);
	tts_lt(30);		tts_fd(0.03);	tts_lt(120);	tts_fd(0.03);
	tts_lt(30);		tts_fd(0.06);
	tts_pu();		tts_home();		
	tts_pd();		tts_lt(180);	tts_fd(0.08);
	tts_pu();
}