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