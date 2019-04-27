#include "anime_test.h"
#include "animes.h"

void test_of_anime_shield() {
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	draw_anime_shield(2, new_pos(5, 3.5), 0.6, -1);
	start_global_timer();
}

void test_of_anime_explode() {
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	draw_anime_explode(12, new_pos(5, 3.5), 0.5);
	start_global_timer();
}

void draw_bx(void* pos) {
	Pos x = cast(Pos, pos);
	MovePen(1, 1);
	DrawLine(x.x, x.y);
}

void test_of_anime_accelerate() {
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	start_global_timer();
	Pos* u = (Pos*)malloc(sizeof(Pos));
	u->x = 0;
	u->y = 0;
	add_func_to_timer(draw_bx, u, 1, 123, -1);
	draw_anime_accelerate(u, new_pos(8, 5), 0.002);
}