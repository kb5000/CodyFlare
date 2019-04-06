#include "anime_test.h"
#include "animes.h"

void test_of_anime_shield() {
	InitGraphics();
	init_global_timer();
	add_func_to_timer(auto_clear_display, NULL, 1, 0, -1);
	draw_anime_shield(2, new_pos(5, 3.5), 0.6, -1);
	start_global_timer();
}