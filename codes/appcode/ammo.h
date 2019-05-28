#pragma once
#include "utility.h"

//my plane ammo collision group id
#define PLR_AMMO_COL_ID 173
//enemy plane ammo collision group id 
#define ENM_AMMO_COL_ID 174

///name: init_ammo_system
///func: init the ammo system
///visb: public
void init_ammo_system();

///name: add_ammo
///func: add an ammo to ammo list
///para: isEnemy expects the ammo type, position expects the shoot pos, 
///      direction expects the dir and speed
///visb: public
void add_ammo(int isEnemy, Pos position, Pos direction);

///name: set_ammo_invalid
///func: delete an ammo
///para: id expects the ammo id
///visb: public
void set_ammo_invalid(int id);

///name: start_update_ammo
///func: start to show and update all ammos
///visb: public
void start_update_ammo();

///name: stop_update_ammo
///func: stop to show and update ammos
///visb: public
void stop_update_ammo();

