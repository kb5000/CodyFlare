#pragma once
#include "utility.h"
#include "plane.h"

typedef enum {
	Weapon_Gun, Weapon_Missile, Weapon_Bomb
} WeaponType;

void shoot_gun(int isEnemy, Pos startPos, Pos direction);

void shoot_missile(int isEnemy, Pos startPos, Pos * target, int targetID, void hitHandler(Pos pos, int hitID));

void shoot_bomb(int isEnemy, Pos startPos);

