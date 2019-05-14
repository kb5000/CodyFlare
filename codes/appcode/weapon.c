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
					 0.25, PI / 3, 1.9, 80, 1, anime_explode_pack, 0.6, hitHandler, 0.1, targetID);
		break;
	case Basic_Enemy_Ammo:
		show_missile(startPos, target, 1, color_by_rgb(128, 88, 68),
					 0.1, PI / 3, 1.2, 80, 1, anime_explode_pack, 0.6, hitHandler, 0.1, targetID);
		break;
	case Boss_Ammo:
		show_missile(startPos, target, 6, color_by_rgb(64, 128, 128),
					 0.2, -PI / 3, 1.8, 40, 1, anime_explode_pack, 0.6, hitHandler, 0.1, targetID);
		break;
	default:
		break;
	}
}

ListHandler planes();


void bomb_explode_handler(Pos bombPos) {
	ListHandler pls = planes();
	for (Node* node = pls.head; node; node = node->next) {
		Plane* pln = (Plane*)node->data;
		if (!pln) return;
		double len = pos_length(sub_pos(pln->position, bombPos));
		if (len < 1.4) {
			if (pln->type == Player_Plane) {
				if (len < 0.7)
					pln->health -= (int)(30 / (2 + 2 * len));
			}
			else pln->health -= (int)(35 / (1 + 2 * len));
			if (pln->health <= 0) {
				add_score(pln->type);
				draw_anime_explode(17896, pln->position, 0.8, 6);
				pln->position = new_pos(-1, -1); //set invalid
			}
		}
	}
}

void shoot_bomb(int isEnemy, Pos startPos) {
	switch (isEnemy) {
	case Player_Ammo:
		draw_anime_bomb(922337, startPos, 0.35, 1, color_by_rgb(200, 190, 68), bomb_explode_handler);
		break;
	case Basic_Enemy_Ammo:
		draw_anime_bomb(922338, startPos, 0.35, 1, color_by_rgb(180, 200, 88), bomb_explode_handler);
		break;
	case Boss_Ammo:
		break;
	default:
		break;
	}
}
