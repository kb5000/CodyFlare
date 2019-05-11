#include "weapon.h"
#include "ammo.h"
#include "missile.h"
#include "animes.h"

void shoot_gun(int isEnemy, Pos startPos, Pos direction) {
	add_ammo(isEnemy, startPos, direction);
}


void anime_explode_pack(int id, Pos pos, double size) {
	draw_anime_explode(id, pos, size, 3);
}

void shoot_missile(int isEnemy, Pos startPos, Pos* target, int targetID, void hitHandler(Pos pos, int hitID)) {
	switch (isEnemy) {
	case Player_Ammo:
		show_missile(startPos, target, 1, color_by_rgb(225, 158, 68),
					 0.1, PI / 3, 1.4, 60, 1, anime_explode_pack, 0.6, hitHandler, 0.1, targetID);
		break;
	case Basic_Enemy_Ammo:
		show_missile(startPos, target, 1, color_by_rgb(128, 88, 68),
					 0.1, PI / 3, 1.4, 80, 1, anime_explode_pack, 0.6, hitHandler, 0.1, targetID);
		break;
	case Boss_Ammo:
		show_missile(startPos, target, 6, color_by_rgb(64, 128, 128),
					 0.2, -PI / 3, 1.8, 40, 1, anime_explode_pack, 0.6, hitHandler, 0.1, targetID);
		break;
	default:
		break;
	}
}
