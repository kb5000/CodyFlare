#pragma once

#include "function_drawer.h"
#include "timer.h"
#include "utility.h"
#include "color.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

void draw_anime_shield(int id, Pos position, double size, int existTicks);
void draw_anime_bomb(int id, Pos position, double size, double speed);
void draw_anime_ammo(int id, Pos position, double length, int existTicks);
void draw_anime_player(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_base(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_advanced(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_boss(int id, Pos position, double size, int existTicks);
void draw_anime_enemy_bonus(int id, Pos position, double size, int existTicks);
void draw_anime_victory(int id, Pos position, double size, int existTicks);
void draw_anime_explode(int id, Pos position, double size, int explodeComp);
void draw_anime_accelerate(Pos* start, Pos end, double accu);

typedef struct {
	int id;
	DrawFuncHolder dfh;
	Color (*color_fun)(DrawFuncHolder* dfh);
	Pos a, b;
	Pos p1, p2, p3;
} ParabolaHolder;

ParabolaHolder create_parabola(int id, Pos p1, Pos p2, Pos p3, Color color_fun(DrawFuncHolder* dfh), int penSize);
void draw_parabola(ParabolaHolder ph, int existInteval);
