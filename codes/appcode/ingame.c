#include "ingame.h"
#include "plane.h"
#include "collision.h"
#include <stdlib.h>
#include "timer.h"
#include "input.h"
#include "health_bar.h"
#include "ammo.h"
#include "col_updater.h"
#include "fix_obj.h"
#include "player_control.h"
#include "graphics.h"
#include "imgui.h"
#include "status_line.h"
#include <stdio.h>

static char r[64];
static int timerStack = 3;

void show_stat(void* unuseful) {
	Plane* p = find_plane_by_id(0);
	if (!p) {
		sprintf(r, "Your final score is %d", current_score());
		drawLabel(0.1, 0.1, r);
	} else {
		//sprintf(r, "Score: %d Health: %d Bomb: %d", current_score(), p->health, p->numOfBombs);
		//show_status_line(current_score(), p->health, p->numOfBombs, current_hit_plane(), 0);
	}
	Plane* boss = get_boss_plane();
	if (boss) {
		show_health_bar(boss->health, 2000);
	}
}

void start_game() {
	init_col_detector();
	init_ammo_system();
	init_plane_list();
	init_fix_obj_system();
	start_show_fix_obj();
	add_plane(create_plane(Player_Plane, new_pos(5, 1), 6000, 5));
	add_plane(create_plane(Boss_Plane, new_pos(5, 4), 2000, 5));
	start_display_planes();
	start_update_ammo();
	add_func_to_timer(generate_plane, NULL, 1, 1213, -1);
	start_col_dets();
	start_detection(1);
	start_control();
	add_func_to_timer(show_stat, NULL, 1, 12, -1);
}

void load_game() {
	InitGraphics();
	init_input();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
}

void reload_game();

void butt(void* unuseful) {
	if (button(12314, 1, 1, 0.8, 0.25, "RELOAD")) {
		reload_game();
		start_game();
	}
}

void reload_game() {
	//destroy_timer_stack(timerStack);
	change_timer_stack(timerStack);
	timerStack++;
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	add_func_to_timer(butt, NULL, 1, 124444, -1);
}


void tst() {
	load_game();
	start_game();
	add_func_to_timer(butt, NULL, 1, 124444, -1);
}