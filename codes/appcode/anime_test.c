#include "anime_test.h"
#include "animes.h"
#include "input.h"


void common_anime_test_init() {
	InitGraphics();
	init_input();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	add_func_to_timer(remove_invalid_funcs, NULL, 30, 0, -1);
	start_global_timer();
}

void test_of_anime_shield() {
	common_anime_test_init();
	draw_anime_shield(2, new_pos(5, 3.5), 0.6, -1);
}

void test_of_anime_explode() {
	common_anime_test_init();
	draw_anime_explode(12, new_pos(5, 3.5), 1, 3);
}

void test_of_anime_boss() {
	common_anime_test_init();
	draw_anime_enemy_boss(2, new_pos(5, 3.5), 1, -1);
}

void draw_bx(void* pos) {
	Pos x = cast(Pos, pos);
	MovePen(1, 1);
	DrawLine(x.x, x.y);
}

void test_of_anime_accelerate() {
	common_anime_test_init();
	Pos* u = (Pos*)malloc(sizeof(Pos));
	u->x = 0;
	u->y = 0;
	add_func_to_timer(draw_bx, u, 1, 123, -1);
	draw_anime_accelerate(u, new_pos(8, 5), 0.002);
}

void test_of_anime_bomb() {
	common_anime_test_init();
	draw_anime_bomb(12, new_pos(5, 3.5), 1, 1, color_by_name("Black"), NULL);
}

Color color_changing(DrawFuncHolder* dfh) {
	double t = dfh->tNow;
	return color_by_rgb(t * 128, t * 96 + 100, 205 - 10 * t);
}

void show_parabola(Pos* pos) {
	move_by_dir_key(pos, new_pos(0.1, 0.1));
	ParabolaHolder ph = create_parabola(12, new_pos(1, 6), *pos, new_pos(1, 1), color_changing, 1);
	draw_parabola(ph, 1);
}

void test_of_parabola() {
	common_anime_test_init();
	hnew(Pos, spos);
	*spos = new_pos(2, 3.5);
	add_func_to_timer(show_parabola, spos, 1, 12, -1);
}