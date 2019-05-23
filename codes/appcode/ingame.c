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
#include "stat_line.h"
#include <stdio.h>
#include "save_plane.h"
#include "font.h"
#include "random.h"
#include "game_particle.h"

static char r[64];
static int timerStack = 3;
static int gameStack = 0;
static int pauseLoded = 0;

void show_stat(void* unuseful) {
	Plane* p = find_plane_by_id(0);
	if (!p) {
		sprintf(r, "Your final score is %d", current_score());
		drawLabel(0.1, 0.1, r);
		end_game();
	} else {
		//sprintf(r, "Score: %d Health: %d Bomb: %d", current_score(), p->health, p->numOfBombs);
		show_status_line(current_score(), p->health, p->numOfBombs, current_hit_plane(), get_game_mode());
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
	add_plane(create_plane(Player_Plane, new_pos(5, 1), 3000, 5));
	//add_plane(create_plane(Boss_Plane, new_pos(5, 4), 2000, 5));
	start_display_planes();
	start_update_ammo();
	add_func_to_timer(generate_plane, NULL, 1, 1213, -1);
	start_col_dets();
	start_detection(1);
	start_control();
	show_long_particle();
	add_func_to_timer(show_stat, NULL, 1, 12, -1);
}

void load_game() {
	InitGraphics();
	Randomize();
	init_input();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
}


void butt(void* unuseful) {
	if (button(12314, 1, 1, 0.8, 0.25, "RELOAD")) {
		reload_game();
		start_game();
	}
	if (button(99, 4, 1, 0.8, 0.25, "MODE")) {
		set_game_mode(!get_game_mode());
	}
	if (button(12, 2, 1, 0.8, 0.25, "SAVE")) {
		save_plane();
	}
	if (button(13, 3, 1, 0.8, 0.25, "LOAD")) {
		select_saves();
	}
	if (button(14, 5, 1, 0.8, 0.25, "PAUSE")) {
		pause_game();
	}
	if (button(15, 6, 1, 0.8, 0.25, "FAST")) {
		speed_up();
	}
	if (button(16, 7, 1, 0.8, 0.25, "SLOW")) {
		speed_down();
	}
}

void butt_b(void* unuseful) {
	if (button(123, 1, 1, 0.8, 0.25, "CONTINUE")) {
		continue_game();
	}
}

void load_from_file() {
	init_col_detector();
	init_ammo_system();
	init_plane_list();
	init_fix_obj_system();
	start_show_fix_obj();
	//add_plane(create_plane(Boss_Plane, new_pos(5, 4), 2000, 5));
	start_update_ammo();
	add_func_to_timer(generate_plane, NULL, 1, 1213, -1);
	start_col_dets();
	start_detection(1);
	start_control();
	show_long_particle();
	add_func_to_timer(show_stat, NULL, 1, 12, -1);
}

void reload_game() {
	//destroy_timer_stack(timerStack);
	change_timer_stack(timerStack);
	timerStack++;
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	add_func_to_timer(butt, NULL, 1, 124444, -1);
}

void end_game() {
	change_timer_stack(timerStack);
	timerStack++;
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(butt, NULL, 1, 124444, -1);
	show_font("GAME OVER");
}

void tst() {
	load_game();
	show_font("TO THE SPACE");
	add_func_to_timer(butt, NULL, 1, 124444, -1);
}

void pause_game() {
	gameStack = get_timer_stack();
	change_timer_stack(99999);
	if (!pauseLoded) {
		pauseLoded = 1;
		add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
		add_func_to_timer(butt_b, NULL, 1, 124444, -1);
	}
}

void continue_game() {
	change_timer_stack(gameStack);
}

void speed_up() {
	int t = get_timer_interval();
	if (t > 8) t -= 8;
	restart_global_timer(t);
}

void speed_down() {
	int t = get_timer_interval();
	if (t < 64) t += 8;
	restart_global_timer(t);
}

void god_mode() {
	Plane* player = find_plane_by_id(0);
	if (player) {
		player->health += 10000;
	}
}


