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
#include "extgraph.h"
#include "imgui.h"
#include "stat_line.h"
#include <stdio.h>
#include "save_plane.h"
#include "font.h"
#include "random.h"
#include "game_particle.h"
#include "menu.h"
#include "start_page.h"
#include "end_page.h"
#include "rank.h"
#include "listbox.h"
#include "help_page.h"

//static char r[64];
static int timerStack = 5;
static int gameStack = 0;
static int pauseLoded = 0;
static int inPause = 0;
static int inVictory = 0;
static int inGame = 0;
//static int showBackGround = 1;

void show_stat(void* unuseful) {
	Plane* p = find_plane_by_id(0);
	if (!p) {
		future_do(30, end_game, NULL);
		show_status_line(current_score(), 0, 0, current_hit_plane(), get_game_mode());
	} else {
		//sprintf(r, "Score: %d Health: %d Bomb: %d", current_score(), p->health, p->numOfBombs);
		show_status_line(current_score(), p->health, p->numOfBombs, current_hit_plane(), get_game_mode());
	}
	Plane* boss = get_boss_plane();
	if (boss) {
		show_health_bar(boss->health, 2000);
	}
}

void end_show(void* unuseful) {
	char r[64];
	sprintf(r, "Your final score is %d", current_score());
	drawLabel(0.1, 0.1, r);
}

void start_game() {
	init_col_detector();
	init_ammo_system();
	init_plane_list();
	init_fix_obj_system();
	start_show_fix_obj();
	add_plane(create_plane(Player_Plane, new_pos(5, 1), 60, 5));
	//add_plane(create_plane(Boss_Plane, new_pos(5, 4), 2000, 5));
	start_display_planes();
	start_update_ammo();
	add_func_to_timer(generate_plane, NULL, 1, 1213, -1);
	start_col_dets();
	start_detection(1);
	start_control();
	destroy_long_particle();
	if (is_show_particle()) show_long_particle();
	add_func_to_timer(show_stat, NULL, 1, 12, -1);
	inVictory = 0;
	inGame = 1;
}

void load_game() {
	InitGraphics();
	SetWindowTitle("TO THE SPACE");
	Randomize();
	init_input();
	init_global_timer();
	init_help();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
}


void butt(void* unuseful) {
	show_menu(unuseful);
	//if (button(12314, 1, 1, 0.8, 0.25, "RELOAD")) {
	//	reload_game();
	//	start_game();
	//}
	//if (button(99, 4, 1, 0.8, 0.25, "MODE")) {
	//	set_game_mode(!get_game_mode());
	//}
	//if (button(12, 2, 1, 0.8, 0.25, "SAVE")) {
	//	save_plane();
	//}
	//if (button(13, 3, 1, 0.8, 0.25, "LOAD")) {
	//	select_saves();
	//}
	//if (button(14, 5, 1, 0.8, 0.25, "PAUSE")) {
	//	pause_game();
	//}
	//if (button(15, 6, 1, 0.8, 0.25, "FAST")) {
	//	speed_up();
	//}
	//if (button(16, 7, 1, 0.8, 0.25, "SLOW")) {
	//	speed_down();
	//}
	//if (button(17, 8, 1, 0.8, 0.25, "BKGRND")) {
	//	toggle_long_particle();
	//}
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
	if (is_show_particle()) show_long_particle();
	add_func_to_timer(show_stat, NULL, 1, 12, -1);
	inVictory = 0;
	inGame = 1;
}

void destroy_last_stack(int* lastStack) {
	destroy_timer_stack(*lastStack);
}

void reload_game() {
	//destroy_timer_stack(timerStack);
	hnew(int, lastStack);
	*lastStack = get_timer_stack();
	change_timer_stack(timerStack);
	future_do(3, destroy_last_stack, lastStack);
	timerStack++;
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	add_func_to_timer(butt, NULL, 1, 124444, -1);
}

void end_game(void* unuseful) {
	//change_timer_stack(timerStack);
	//timerStack++;
	//add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	//add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	//add_func_to_timer(butt, NULL, 1, 124444, -1);
	destroy_long_particle();
	reload_game();
	show_font("GAME OVER");
	update_rank(current_score());
	add_func_to_timer(end_show, NULL, 1, 12, -1);
	inGame = 0;
}

void start_page(void* unuseful) {
	//load_game();
	change_timer_stack(1);
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	show_font("TO THE SPACE");
	add_func_to_timer(butt, NULL, 1, 124444, -1);
	draw_game_page_anime();
	reset_mouse_key(1);
}

void pause_game() {
	gameStack = get_timer_stack();
	change_timer_stack(99999);
	if (!pauseLoded) {
		//pauseLoded = 1;
		add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
		show_font("PAUSE");
		add_func_to_timer(butt, NULL, 1, 124444, -1);
	} else {
		close_list_box(0, NULL, 0);
		remove_rank();
	}
	inPause = 1;
}

static void future_destroy_tms(int* stk) {
	destroy_timer_stack(*stk);
}

void continue_game() {
	change_timer_stack(gameStack);
	//destroy_timer_stack(gameStack);
	//hnew(int, pauseStack);
	//*pauseStack = 99999;
	//future_do(1, future_destroy_tms, pauseStack);
	inPause = 0;
}

void speed_up() {
	int t = get_timer_interval();
	if (t > 8) t /= 2;
	restart_global_timer(t);
}

void speed_down() {
	int t = get_timer_interval();
	if (t < 128) t *= 2;
	restart_global_timer(t);
}

void god_mode() {
	Plane* player = find_plane_by_id(0);
	if (player) {
		player->health += 2000;
	}
}

void god_bomb_mode() {
	Plane* player = find_plane_by_id(0);
	if (player) {
		player->numOfBombs += 100;
	}
}

int is_pause() {
	return inPause;
}

int is_vic() {
	return inVictory;
}

int is_game() {
	return inGame;
}

void open_game() {
	load_game();
	show_start_page();
	future_do(83, start_page, NULL);
}

void game_victory(void* unuseful) {
	destroy_long_particle();
	inVictory = 1;
	reload_game();
	show_end_page();
	update_rank(current_score());
	inGame = 0;
}
