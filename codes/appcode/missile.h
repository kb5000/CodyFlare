#pragma once
#include "utility.h"
#include "color.h"

void show_missile(Pos a, Pos* b, int num, Color color, double speed,
 double maxAngle, 
				  double flexibility, int life, int isDirectAttack, void explode_anime(int id, Pos position, double size), double explodeSize, void hit_handler(Pos position));
