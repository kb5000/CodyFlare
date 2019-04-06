#pragma once

#include "function_drawer.h"
#include "timer.h"
#include "point.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

void draw_anime_shield(int id, Pos position, double size, int existTicks);
void draw_anime_bomb(int id, Pos position, double size, int existTicks);
void draw_anime_ammo(int id, Pos position, double length, int existTicks);
void draw_anime_player(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_base(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_advanced(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_boss(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_bonus(int id, Pos position, double size, int existTicks);
void draw_anime_victory(int id, Pos position, double size, int existTicks);
