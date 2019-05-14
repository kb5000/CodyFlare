#pragma once
#include "utility.h"

void start_col_dets();

void player_ammo_enemy_plane_col(int group1, int id1, int group2, int id2, void* unuseful);

void enemy_ammo_player_plane_col(int group1, int id1, int group2, int id2, void* unuseful);

void missile_target_enemy(Pos pos, int id);
