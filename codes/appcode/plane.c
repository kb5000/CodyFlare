#include "plane.h"
#include <stdlib.h>
#include "timer.h"
#include "collision.h"
#include "input.h"
#include "ai.h"
#include "weapon.h"
#include "random.h"
#include "col_updater.h"
#include "animes.h"
#include "fix_obj.h"
#include "ingame.h"
//#include "extgraph.h"

static ListHandler planeList;
static int planeID = 0;
static int planeRefreshTime = 0;
static int score = 0;
static int planeNum = 0;
static int hitPlane = 0;
static int gameMode = 0;
static int refreshTime = 80;
static int accuTime = 25;
static int accuFlag = 0;

void init_plane_list() {
	if (planeList.destroy) {
		calls(planeList, destroy);
	}
	planeID = 0;
	planeRefreshTime = 0;
	score = 0;
	planeNum = 0;
	hitPlane = 0;
	gameMode = 0;
	accuTime = 25;
	accuFlag = 0;
	planeList = new_empty_list();
	add_col_group(PLR_PLN_COL_ID);
	add_col_group(ENM_PLN_COL_ID);
}

void set_game_mode(int mode) {
	gameMode = mode;
	if (mode == 0) refreshTime = 80;
	else refreshTime = 90;
}

int get_game_mode() {
	return gameMode;
}

void set_plane_num(int refresh) {
	planeNum = refresh;
}

int get_plane_num() {
	return planeNum;
}

ListHandler* plane_list() {
	return &planeList;
}

void set_plane_list(ListHandler plane) {
	if (planeList.destroy) {
		calls(planeList, destroy);
	}
	planeList = plane;
}

void set_score_info(int scr, int hit) {
	score = scr;
	hitPlane = hit;
}

void set_accu_flag(int flag) {
	accuFlag = flag;
}

Plane create_plane(PlaneType type, Pos initPosition, int health, int numOfBombs) {
	Plane res = {
		0,
		type,
		initPosition,
		health,
		0,
		numOfBombs,
		0,
	};
	return res;
}

void add_plane(Plane plane) {
	hnew(Plane, pln);
	*pln = plane;
	pln->id = planeID++;
	calls(planeList, push_back, pln);
	switch (plane.type) {
	case Player_Plane:
		add_col_obj_to_group(PLR_PLN_COL_ID, create_col_obj(Col_Triangle,
															add_pos(pln->position, new_pos(-0.2, -0.1)),
															add_pos(pln->position, new_pos(0.2, -0.1)), pln->id,
															add_pos(pln->position, new_pos(0, 0.4))));
		break;
	case Basic_Enemy_Plane:
		add_col_obj_to_group(ENM_PLN_COL_ID, create_col_obj(Col_Triangle,
															add_pos(pln->position, new_pos(-0.25, 0.1)),
															add_pos(pln->position, new_pos(0.25, 0.1)), pln->id, add_pos(pln->position, new_pos(0, -0.25))));
		break;
	case Advanced_Enemy_Plane:
		add_col_obj_to_group(ENM_PLN_COL_ID, create_col_obj(Col_Triangle,
															add_pos(pln->position, new_pos(-0.25, 0.18)),
															add_pos(pln->position, new_pos(0.25, 0.18)), pln->id, add_pos(pln->position, new_pos(0, -0.22))));
		break;
	case Swift_Enemy_Plane:
		add_col_obj_to_group(ENM_PLN_COL_ID, create_col_obj(Col_Triangle,
															add_pos(pln->position, new_pos(-0.2, 0.2)),
															add_pos(pln->position, new_pos(0.2, 0.2)), pln->id, add_pos(pln->position, new_pos(0, -0.3))));
		break;
	case Boss_Plane:
		draw_anime_enemy_boss(6666444, pln->position, 1, -1);
		add_col_obj_to_group(ENM_PLN_COL_ID, create_col_obj(Col_Triangle, add_pos(pln->position, new_pos(0, -0.05)), add_pos(pln->position, new_pos(-2, 2.35)),
															pln->id, add_pos(pln->position, new_pos(2, 2.35))));
		break;
	default:
		break;
	}
}

Plane* find_plane_by_id(int id) {
	for (Node* node = planeList.head; node; node = node->next) {
		Plane* plane = (Plane*)node->data;
		if (plane->id == id) return plane;
	}
	return NULL;
}

Plane* find_dangerous_plane() {
	if (!planeList.head || !planeList.head->next) return NULL;
	Plane* dangp = (Plane*)planeList.head->next->data;
	double maxScore = -1000;
	for (Node* node = planeList.head->next; node; node = node->next) {
		Plane* plane = (Plane*)node->data;
		double score = 50 - plane->position.y - 10 * (plane->position.y < 0.5) +
			15 * (plane->health <= 12) - 4 * (fabs(plane->position.x - player_plane_pos()->x) < 1) + 4 * (plane->type == Advanced_Enemy_Plane);
		if (score > maxScore) {
			dangp = plane;
			maxScore = score;
		}
	}
	return dangp;
}

int remove_plane_helper(Plane* plane, int* id) {
	if (plane->id == *id) {
		if (plane->type == Player_Plane) {
			remove_col_obj(PLR_PLN_COL_ID, *id);
		} else {
			if (plane->type == Boss_Plane) {
				remove_funcs_from_timer(6666444);
			}
			remove_col_obj(ENM_PLN_COL_ID, *id);
		}
		return 1;
	}
	return 0;
}

void remove_plane_by_id(int id) {
	calls(planeList, remove_if, remove_plane_helper, &id);
}

Pos* player_plane_pos() {
	//assume that the first plane is the player's plane
	return &((Plane*)(planeList.head->data))->position;
}

Plane* get_boss_plane() {
	for (Node* node = planeList.head; node; node = node->next) {
		Plane* plane = (Plane*)node->data;
		if (!plane) continue;
		if (plane->type == Boss_Plane) return plane;
	}
	return NULL;
}

void update_each_plane(Plane* plane) {
	switch (plane->type) {
	case Player_Plane:
		//Pos p = plane->position;
		if (plane->position.x < 0 && plane->position.y < 0) return;
		if (accuFlag && accuTime > 0) {
			move_by_dir_key(&plane->position, new_pos(0.32, 0.28));
			accuTime -= 6;
			if (accuTime < 0) accuTime = 0;
		} else {
			move_by_dir_key(&plane->position, new_pos(0.13, 0.1));
		}
		if (plane->position.x < 0.2) plane->position.x = 0.2;
		if (plane->position.x > 9.8) plane->position.x = 9.8;
		if (plane->position.y < 0.41) plane->position.y = 0.41;
		if (plane->position.y > 6.8) plane->position.y = 6.8;
		plane->missileTime++;
		if (plane->missileTime > 100) plane->missileTime = 100;
		if (plane->ammoTime++ == 3) {
			shoot_gun(Player_Ammo, add_pos(plane->position, new_pos(0.01, 0.2)), new_pos(0, 0.1));
			plane->ammoTime = 0;
		}
		if (accuTime < 25 && !accuFlag) accuTime++;
		MovePen(plane->position.x - 0.2, plane->position.y - 0.19);
		set_color(color_by_name("Blue"));
		DrawLine(accuTime / 25.0 * 0.4, 0);
		MovePen(plane->position.x - 0.2, plane->position.y - 0.16);
		set_color(color_by_rgb(196, 100, 40));
		DrawLine(plane->missileTime / 100.0 * 0.4, 0);
		draw_player_plane(&plane->position);
		update_tri_col_info(PLR_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.2, -0.1)),
							add_pos(plane->position, new_pos(0.2, -0.1)), add_pos(plane->position, new_pos(0, 0.35)));
		break;
	case Basic_Enemy_Plane:
	{
		Pos pos = *player_plane_pos();
		plane->position = basic_enemy_move(plane->position, pos);
		if (plane->ammoTime++ == 16) {
			shoot_gun(Basic_Enemy_Ammo, add_pos(plane->position, new_pos(-0.01, -0.1)), new_pos(0, -0.1));
			plane->ammoTime = 0;
		}
		draw_basic_enemy(&plane->position);
		update_tri_col_info(ENM_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.25, 0.1)),
							add_pos(plane->position, new_pos(0.25, 0.1)), add_pos(plane->position, new_pos(0, -0.25)));
		break;
	}
	case Advanced_Enemy_Plane:
	{
		//MovePen(plane->position.x, plane->position.y - 0.22);
		//DrawLine(-0.25, 0.40);
		//MovePen(plane->position.x, plane->position.y - 0.22);
		//DrawLine(0.25, 0.40);
		Pos pos = *player_plane_pos();
		plane->position = advanced_enemy_move(plane->position, pos);
		if (plane->position.y > pos.y + 2) {
			if (plane->missileTime++ == 60) {
				shoot_missile(Basic_Enemy_Ammo, add_pos(plane->position, new_pos(0, -0.1)), player_plane_pos(),
							  0, missile_target_enemy);
				plane->missileTime = 0;
			}
		} else {
			if (plane->ammoTime++ == 6) {
				Pos launchPos = add_pos(plane->position, new_pos(0, -0.2));
				shoot_gun(Basic_Enemy_Ammo, launchPos, sub_pos(pos, add_pos(launchPos, new_pos(0, 0.1))));
				plane->ammoTime = 0;
			}
		}
		draw_infernal_enemy(&plane->position);
		update_tri_col_info(ENM_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.25, 0.18)),
							add_pos(plane->position, new_pos(0.25, 0.18)), add_pos(plane->position, new_pos(0, -0.22)));
	}
	break;
	case Swift_Enemy_Plane:
	{
		Pos pos = *player_plane_pos();
		plane->position = swift_enemy_move(plane->position, pos);
		MovePen(plane->position.x - 0.2, plane->position.y);
		DrawLine(0.4, 0);
		draw_bonus_enemy(&plane->position);
		update_tri_col_info(ENM_PLN_COL_ID, plane->id, add_pos(plane->position, new_pos(-0.2, 0.2)),
							add_pos(plane->position, new_pos(0.2, 0.2)), add_pos(plane->position, new_pos(0, -0.3)));
		if (pos_length(sub_pos(pos, plane->position)) < 0.8) {
			shoot_bomb(Basic_Enemy_Ammo, plane->position);
			plane->position = new_pos(-1, -1);
		}
	}
	break;
	case Boss_Plane:
	{
		//MovePen(plane->position.x, plane->position.y - 0.05);
		//DrawLine(-2, 2.4);
		//MovePen(plane->position.x, plane->position.y - 0.05);
		//DrawLine(2, 2.4);
		//MovePen(plane->position.x - 2, plane->position.y + 2.35);
		//DrawLine(4, 0);
		//if (plane->ammoTime % 3 == 0)
		//shoot_gun(Boss_Ammo, plane->position, polar_to_rect(new_pos(0.1, RandomReal(0, 2 * PI))));
		if (plane->ammoTime++ % 2 == 0) {
			shoot_gun(Boss_Ammo, plane->position, polar_to_rect(new_pos(0.1, RandomReal(0, 2 * PI))));
		}
		if (plane->missileTime++ == 210) {
			plane->missileTime = 0;
			shoot_missile(Boss_Ammo, plane->position, player_plane_pos(), 0, missile_target_by_boss);
		}
		if (plane->numOfBombs++ == 300) {
			shoot_bomb(Boss_Ammo, add_pos(*player_plane_pos(), new_pos(0, 0.5)));
			plane->numOfBombs = 0;
		}
	}
	break;
	default:
		break;
	}
}

int remove_invalid_plane(Plane* plane, void* unuseful) {
	if (!pos_in_rect(plane->position, new_pos(0, 0), new_pos(10, 7.4))) {
		if (plane->type == Player_Plane) {
			remove_col_obj(PLR_PLN_COL_ID, plane->id);
		} else {
			remove_col_obj(ENM_PLN_COL_ID, plane->id);
		}
		return 1;
	}
	return 0;
}

void update_plane(void* unuseful) {
	calls(planeList, for_each, update_each_plane);
	calls(planeList, remove_if, remove_invalid_plane, NULL);
}

void generate_plane(void* unuseful) {
	int fresh = refreshTime;
	if (gameMode) fresh -= (int)(7 * sqrt(planeNum));
	if (fresh < 3) fresh = 3;
	if (planeRefreshTime++ >= fresh) {
		if (gameMode) add_score(-1);
		Plane plane;
		if (planeNum == 58 && !gameMode) {
			add_fix_obj(new_pos(2, 2), Fix_Obj_Health);
			add_fix_obj(new_pos(5, 2), Fix_Obj_Health);
			add_fix_obj(new_pos(8, 2), Fix_Obj_Health);
		} else if (planeNum == 59 && !gameMode) {
			;	//nothing
		} else if (planeNum == 60 && !gameMode) {
			plane = create_plane(Boss_Plane, new_pos(5, 4), 2000, 37);
			add_plane(plane);
		} else {
			plane = create_plane(Basic_Enemy_Plane, new_pos(RandomReal(0.2, 9.8), 7.2), 20, 0);
			int seed = RandomInteger(0, 9);
			if (seed < 5) {
				plane.type = Basic_Enemy_Plane;
			} else if (seed < 8) {
				plane.type = Advanced_Enemy_Plane;
				plane.health = 25;
			} else {
				plane.type = Swift_Enemy_Plane;
				plane.health = 15;
			}
			add_plane(plane);
		}
		planeRefreshTime = 0;
		planeNum++;
	}
}

void start_display_planes() {
	add_func_to_timer(update_plane, NULL, 1, 285744, -1);
}

void stop_display_planes() {
	remove_funcs_from_timer(6666444);
	remove_funcs_from_timer(285744);
}

void plane_explode(Plane* plane, int health) {
	plane->health -= health;
	if (plane->health <= 0) {
		hitPlane++;
		if (plane->type == Boss_Plane) {
			future_do(20, game_victory, NULL);
		}
		if (plane->type == Swift_Enemy_Plane) {
			generate_fix_obj(plane->position);
		}
		add_score(plane->type);
		draw_anime_explode(17896, plane->position, 0.8, 6);
		remove_plane_by_id(plane->id);
	}
}

ListHandler planes() {
	return planeList;
}

void clear_score() {
	score = 0;
}

void add_score(PlaneType plane) {
	switch (plane) {
	case Basic_Enemy_Plane:
		score += 50;
		break;
	case Advanced_Enemy_Plane:
		score += 100;
		break;
	case Swift_Enemy_Plane:
		score += 80;
		break;
	case Boss_Plane:
		score += 1000;
		break;
	case -1:
		score += 20;
	default:
		break;
	}
}

int current_score() {
	return score;
}

void inc_hit_plane() {
	hitPlane++;
}

int current_hit_plane() {
	return hitPlane;
}