#pragma once
#include "utility.h"
#include "color.h"

///name: show_missile
///func: display a missile that can trace target
///para: start expects the start point, target expects the pointer contains the position of target
///      num expects the number of missiles, color expects the color of missiles
///      speed expects the speed of missiles, maxAngle expects the max angle when the missiles launch, 
///      negative angle means launch on the back, flexibility expects the speed missiles turn,
///      life expects the max life of missiles, isDirectAttack is not using,
///      explode_anime expects the anime when it explodes, explodeSize expects the size of anime,
///      hit_handler expects what will call if a missile hit target
void show_missile(Pos start, Pos* b, int num, Color color, double speed, double maxAngle, 
					double flexibility, int life, int isDirectAttack, 
					void explode_anime(int id, Pos position, double size), double explodeSize, 
					void hit_handler(Pos position), double explodeRadius);
