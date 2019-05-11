#include "animes.h"

void draw_anime_ammo_once(AmmoType ammoType, Pos position, Pos direction) {
	MovePen(position.x, position.y);
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
	DrawLine(direction.x, direction.y);
	Pos normal = add_pos(position, polar_to_rect(new_pos(0.02, PI / 2 + pos_arc(direction))));
	MovePen(normal.x, normal.y);
	DrawLine(direction.x, direction.y);
}