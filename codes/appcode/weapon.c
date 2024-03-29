#include "weapon.h"
#include "ammo.h"
#include "missile.h"
#include "animes.h"
#include "fix_obj.h"
#include "ingame.h"

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
					 0.25, PI / 3, 2, 60, 1, anime_explode_pack, 0.6, hitHandler, 0.12, targetID);
		break;
	case Basic_Enemy_Ammo:
		show_missile(startPos, target, 1, color_by_rgb(128, 88, 68),
					 0.13, PI / 3, 1.2, 60, 1, anime_explode_pack, 0.6, hitHandler, 0.12, targetID);
		break;
	case Boss_Ammo:
		show_missile(startPos, target, 50, color_by_rgb(64, 128, 128),
					 0.2, -PI, 0.8, 17, 1, anime_explode_pack, 0.6, hitHandler, 0.12, targetID);
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
		if (len < 1.55) {
			if (pln->type == Player_Plane) {
				if (len < 0.9)
					pln->health -= (int)(30 / (2 + 2 * len));
			}
			else pln->health -= (int)(42 / (1 + 1.6 * len));
			if (pln->health <= 0) {
				if (pln->type == Swift_Enemy_Plane) {
					generate_fix_obj(pln->position);
				} else if (pln->type == Boss_Plane) {
					remove_funcs_from_timer(6666444);
					future_do(20, game_victory, NULL);
				} else {
					inc_hit_plane();
				}
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
		draw_anime_bomb(922339, startPos, 0.35, 1, color_by_rgb(64, 128, 128), bomb_explode_handler);
		break;
	default:
		break;
	}
}
