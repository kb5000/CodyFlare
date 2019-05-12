#pragma once
#include "utility.h"

//my plane ammo collision group id
#define PLR_AMMO_COL_ID 173
//enemy plane ammo collision group id 
#define ENM_AMMO_COL_ID 174

void init_ammo_system();

void add_ammo(int isEnemy, Pos position, Pos direction);

void set_ammo_invalid(int id);

void start_update_ammo();

void stop_update_ammo();

