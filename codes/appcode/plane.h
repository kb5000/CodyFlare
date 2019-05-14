#pragma once
#include "animes.h"
#include "collision.h"

#define PLR_PLN_COL_ID 329
#define ENM_PLN_COL_ID 330

typedef enum {
	Player_Plane, Basic_Enemy_Plane, Advanced_Enemy_Plane, Swift_Enemy_Plane, 
} PlaneType;

typedef struct {
	int id;
	PlaneType type;
	Pos position;
	int health;
	int missileTime;
	int numOfBombs;
	int ammoTime;
} Plane;

void init_plane_list();

Plane create_plane(PlaneType type, Pos initPosition, int health, int numOfBombs); 

void add_plane(Plane plane);

Plane* find_plane_by_id(int id);

Plane* find_dangerous_plane();

void remove_plane_by_id(int id);

void generate_plane(void * unuseful);

void start_display_planes();

void stop_display_planes();
