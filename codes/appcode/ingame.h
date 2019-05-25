#pragma once

void start_game();

void load_game();

void start_page(void*);

void pause_game();

void continue_game();

void speed_up();

void speed_down();

void god_mode();

void god_bomb_mode();

int is_pause();

int is_vic();

void open_game();

void game_victory(void* unuseful);

void update_in_game(void* data);

void end_game(void* unuseful);

void load_from_file();

void reload_game();
