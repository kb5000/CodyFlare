#pragma once
#include "animes.h"
#include "collision.h"

#define PLR_PLN_COL_ID 329
#define ENM_PLN_COL_ID 330

typedef enum {
	Player_Plane, Basic_Enemy_Plane, Advanced_Enemy_Plane, Swift_Enemy_Plane, Boss_Plane
} PlaneType;

typedef struct {
	int id;
	PlaneType type;
	Pos position;
	int health;
	int missileTime;
	int numOfBombs;
	int ammoTime;
} Plane;

void init_plane_list();

void set_game_mode(int mode);

int get_game_mode();

void set_plane_num(int refresh);

int get_plane_num();

ListHandler * plane_list();

void set_plane_list(ListHandler plane);

void set_score_info(int scr, int hit);

void set_accu_flag(int flag);

Plane create_plane(PlaneType type, Pos initPosition, int health, int numOfBombs);

void add_plane(Plane plane);

Plane* find_plane_by_id(int id);

Plane* find_dangerous_plane();

void remove_plane_by_id(int id);

Plane * get_boss_plane();

void generate_plane(void * unuseful);

void start_display_planes();

void stop_display_planes();

void plane_explode(Plane* plane, int health);

void clear_score();

void add_score(PlaneType plane);

int current_score();

void inc_hit_plane();

int current_hit_plane();
