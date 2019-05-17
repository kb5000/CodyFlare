#pragma once

#include "function_drawer.h"
#include "timer.h"
#include "utility.h"
#include "color.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "tortoise.h"

void draw_anime_shield(int id, Pos position, double size, int existTicks);
void draw_anime_bomb(int id, Pos position, double size, double speed, Color color, void explode_handler(Pos bombPos));
void draw_anime_player(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_base(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_advanced(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_boss(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_bonus(int id, Pos position, double size, int existTicks);
void draw_anime_victory(int id, Pos position, double size, int existTicks);
void draw_anime_explode(int id, Pos position, double size, int explodeComp);
void draw_anime_accelerate(Pos* start, Pos end, double accu);
void draw_anime_move_down(Pos* start, Pos end, double speed);

void draw_front_sight(Pos* posp);
void draw_player_plane(Pos* position);
void draw_basic_enemy(Pos* position);
void draw_bonus_enemy(Pos* pos);

void draw_missile(Pos pos, Pos dirt, Color color);

typedef enum {
	Player_Ammo = 0, 
	Basic_Enemy_Ammo = 1, 
	Boss_Ammo = 2
} AmmoType;

void draw_anime_ammo_once(AmmoType ammoType, Pos position, Pos direction);

typedef struct {
	int id;
	DrawFuncHolder dfh;
	Color (*color_fun)(DrawFuncHolder* dfh);
	Pos a, b;
	Pos p1, p2, p3;
} ParabolaHolder;

ParabolaHolder create_parabola(int id, Pos p1, Pos p2, Pos p3, Color color_fun(DrawFuncHolder* dfh), int penSize);
void draw_parabola(ParabolaHolder ph, int existInteval);
