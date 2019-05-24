#include "animes.h"
#include "extgraph.h"

void draw_anime_ammo_once(AmmoType ammoType, Pos position, Pos direction) {
	switch (ammoType) {
	case Player_Ammo:
		set_color(color_by_rgb(63, 72, 204));
		break;
	case Basic_Enemy_Ammo:
		set_color(color_by_rgb(255, 127, 39));
		break;
	case Boss_Ammo:
		set_color(color_by_rgb(136, 0, 21));
		break;
	default:
		break;
	}
	Pos normal = add_pos(position, polar_to_rect(new_pos(0.02, PI / 2 + pos_arc(direction))));
	MovePen(position.x, position.y);
	DrawLine(direction.x, direction.y);
	MovePen(normal.x, normal.y);
	DrawLine(direction.x, direction.y);
}

void anime_ammo_hit_drawer(Pos* pos) {
	set_color(color_by_rgb(214, 10, 250));
	move_tortoise(*pos);
	tts_turn(225);	tts_set_home();	
	tts_pd();		tts_fd(0.08);	tts_home();	
	tts_lt(70);		tts_fd(0.06);	tts_home();
	tts_lt(50);		tts_fd(0.05);	tts_home();
	tts_lt(100);	tts_fd(0.07);	tts_home();
	tts_lt(90);		tts_fd(0.03);	tts_home();
	tts_pu();
}

void draw_anime_ammo_hit(Pos position) {
	hnew(Pos, pos);
	*pos = position;
	add_func_to_timer(anime_ammo_hit_drawer, pos, 1, 832467, 5);
}